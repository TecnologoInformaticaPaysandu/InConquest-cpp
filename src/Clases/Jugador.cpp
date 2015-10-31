


#include "Jugador.h"
#include "../Coleccion/Lista.h"
#include "Partida.h"
#include "Eliminacion.h"
#include "Dominacion.h"
#include "../Coleccion/Iterador.h"
#include <cstdlib>
#include <string.h>
#include <stdexcept>
#include <iostream>

using namespace std;

////////////////////////////////// CONSTRUCTOR //////////////////////////////////
Jugador::Jugador(const char* email, const char* nom, const char* nac, Fecha f, const char* s){
    int L1=strlen(email), L2=strlen(nom), L3=strlen(nac);
    this->email=new char[L1+1];
    this->nombre=new char[L2+1];
    this->nacionalidad=new char[L3+1];
    strcpy(this->email, email);
    strcpy(this->nombre, nom);
    strcpy(this->nacionalidad, nac);
    this->nacimiento=f;
    this->sexo=new char[10];
    if(strcmpi(s,"m")==0)
        strcpy(this->sexo,"Masculino");
    else if(strcmpi(s,"f")==0)
        strcpy(this->sexo,"Femenino");
    this->objetivo=NULL;
    this->terr_ocupados=new Lista();
    this->unidades=new Lista();
    this->partidas_jugadas=new Lista();
    this->infoPartida=NULL;
}
////////////////////////////// GETS Y SETS ///////////////////////////////////
char * Jugador::getEmail(){
    return email;
}
char * Jugador::getNombre(){
    return nombre;
}
char * Jugador::getNacionalidad(){
    return nacionalidad;
}
Fecha & Jugador::getNacimiento(){
    return nacimiento;
}
char * Jugador::getSexo(){
    return sexo;
}
Lista * Jugador::getTerritorios(){
    return terr_ocupados;
}
Lista * Jugador::getUnidades(){
    return unidades;
}

Lista * Jugador::getPartidas(){
    return partidas_jugadas;
}

Objetivo * Jugador::getObjetivo(){
    return objetivo;
}
DatosEnPartida * Jugador::getInfoPartida(){
    return infoPartida;
}
void Jugador::setObjetivo(Objetivo* obj){
    objetivo=obj;
}
void Jugador::setInfoPartida(int creditos, int turno){
    infoPartida=new DatosEnPartida(creditos,turno);
}
///////////////////////////////////////////////////////////////////////////

void Jugador::agregarTerritorio(Territorio* t){
    terr_ocupados->add(t, t->getNombre());
    t->setOcupante(this);
}
void Jugador::agregarUnidad(Unidad* u){
    unidades->add(u, u->getId());
}

Territorio * Jugador::buscarTerritorio(const char *nombre){
    Coleccionable *c=terr_ocupados->find(nombre);
    
    if(!c)
        throw invalid_argument("Error, el nombre del territorio no es correcto");
    Territorio *t=dynamic_cast<Territorio *>(c);
    return t;
}

Unidad * Jugador::buscarUnidad(const char *ident){
    Coleccionable *c=unidades->find(ident);
    if(!c)
        throw invalid_argument("Error, el id de la unidad no es correcto");
    Unidad *u=dynamic_cast<Unidad *>(c);
    return u;
}

void Jugador::agregarPartida(Partida* p){
    this->partidas_jugadas->add(p,p->getNombre());
}

bool Jugador::cumplioObjetivo(Partida *p){
    Iterador *it = new Iterador(p->getJugadores()->getPincipal()->getSig());
    Coleccionable *c;
    bool cumplido = true;
    int contador = 0;
    
    if(Eliminacion *obj = dynamic_cast<Eliminacion *>(objetivo)){
        Jugador *j_eliminar = obj->getJugador();
        
        if(j_eliminar->infoPartida->getQuienLoElimino() != this){
            cumplido = false;
        }
            
    }
    
    if(Dominacion *obj = dynamic_cast<Dominacion *>(objetivo)){
        Iterador *it = new Iterador(obj->getTerritorios()->getPincipal()->getSig());
        Coleccionable *c;
        
        while(it->existeActual() && cumplido){
            c = it->getActual();
            Territorio *t = dynamic_cast<Territorio *>(c);
            if(t->getOcupante() != this)
                cumplido = false;
            
            it->sig();
        }
    }
    
    while(it->existeActual()){
        c = it->getActual();
        Jugador *j = dynamic_cast<Jugador *>(c);
        if(j->infoPartida->getEliminado() == false)
            contador++;
        
        it->sig();
    }
    if(contador == 1 && this->infoPartida->getEliminado() == false)
        cumplido = true;
    
    return cumplido;
}

void Jugador::limpiarJugador(){
    delete unidades;
    delete terr_ocupados;
    unidades = new Lista();
    terr_ocupados = new Lista();
}
///////////////////////////// DESTRUCTOR ///////////////////////////
Jugador::~Jugador(){
}