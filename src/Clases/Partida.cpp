/* 
 * File:   Partida.cpp
 * Author: Matias
 * 
 * Created on 20 de junio de 2012, 11:08
 */

#include "Partida.h"
#include "../Coleccion/Iterador.h"
#include <string.h>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

Partida::Partida(const char* nom, bool limite, int cant, Fecha fecha){
    int largo=strlen(nom);
    nombre=new char[largo+1];
    strcpy(nombre, nom);
    tiene_limite_turnos=limite;
    cant_turnos=cant;
    fecha_jugada=fecha;
    turno_actual=1;
    finalizada=false;
    mapa=NULL;
    jugadores=new Lista();
    tipos_unidades=new Lista();
    ganadores=new Lista();
}
/////////////////////////////// GETS /////////////////////////////////////
char * Partida::getNombre(){
    return nombre;
}
int Partida::getCantTurnos(){
    return cant_turnos;
}
int Partida::getTurnoActual(){
    return turno_actual;
}
bool Partida::getTieneLimite(){
    return tiene_limite_turnos;
}
bool Partida::getFinalizada(){
    return finalizada;
}
Fecha & Partida::getFecha(){
    return fecha_jugada;
}
Mapa * Partida::getMapa(){
    return mapa;
}
Lista * Partida::getJugadores(){
    return jugadores;
}
Lista * Partida::getGanadores(){
    return ganadores;
}
Lista * Partida::getTiposUndades(){
    return tipos_unidades;
}
////////////////////////////////// SETS ////////////////////////////////////
void Partida::setMapa(Mapa* m){
    mapa=m;
    m->setUtilizado();
}
void Partida::finalizar(){
    finalizada=true;
}
void Partida::actualizarTurno(){
    turno_actual++;
}
void Partida::setTurnoActual(int num){
    turno_actual=num;
}

//////////////////////////////////////////////////////////////////////////////
void Partida::sumarCreditos(int creditos){
    Iterador *it = new Iterador(jugadores->getPincipal()->getSig());
    Coleccionable *aux;
    
    while(it->existeActual()){
        aux = it->getActual();
        Jugador *j = dynamic_cast<Jugador *>(aux);
        bool eliminado = j->getInfoPartida()->getEliminado();
        if(eliminado == false)
            j->getInfoPartida()->actualizarCreditos(creditos);
        
        it->sig();
    }
}

void Partida::agregarTipoUnidad(TipoUnidad* tu){
    this->tipos_unidades->add(tu, tu->getNombre());
}

void Partida::agregarJugador(Jugador* j){
    jugadores->add(j, j->getEmail());
    j->agregarPartida(this);
}

void Partida::agregarGanador(const char* nombre){
    Coleccionable *c=this->getJugadores()->find(nombre);
    if(!c)
        throw invalid_argument("No se agrego el jugador a la lista de ganadores");
    Jugador * j=dynamic_cast<Jugador *>(c);
    ganadores->add(j,nombre);
}
void Partida::colocarJugador(Jugador* jugador, Territorio* territorio, Unidad* unidad){
    
    territorio->agregarUnidad(unidad);
    jugador->agregarUnidad(unidad);
    jugador->agregarTerritorio(territorio);
    jugador->agregarPartida(this);
    this->agregarJugador(jugador);
}

void Partida::asignarObjetivo(Jugador *j, Objetivo *o){
    j->setObjetivo(o);
}

void Partida::verInfoPartida(){
    Iterador *it = new Iterador(jugadores->getPincipal()->getSig());
    Iterador *it2 = new Iterador(mapa->getTerritorios()->getPincipal()->getSig());
    Coleccionable *c, *c2, *c3;
    char opc;
    
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Turno actual: "<<turno_actual<<endl;
    if(tiene_limite_turnos)
        cout<<"Limite de turnos: "<<cant_turnos<<endl;
    
    cout<<"Mapa: "<<mapa->getNombre()<<endl;
    cout<<endl<<"*************** JUGADORES PARTICIPANTES ***************"<<endl;
    while(it->existeActual()){
        c = it->getActual();
        Jugador *j=dynamic_cast<Jugador *>(c);
        cout<<"E-mail: "<<j->getEmail()<<endl;
        DatosEnPartida *info=j->getInfoPartida();
        cout<<"Estado: ";
        if(info->getEliminado())
            cout<<"Eliminado"<<endl;
        else{
            cout<<"Sigue jugando"<<endl;
            if(info->getTurnoJugado() == this->turno_actual)
                cout<<"Ya jugo el turno "<<turno_actual<<endl;
            else
                cout<<"No ha jugado el turno "<<turno_actual<<endl;
        }
        cout<<endl;
        it->sig();
    }
    
    cout<<"Desea ver la informacion del mapa [s/n]: ";
    cin>>opc;
    
    if(opc=='s' || opc=='S'){
         cout<<endl<<"*************** INFORMACION DEL MAPA ***************"<<endl<<endl;
         while(it2->existeActual()){
             c2=it2->getActual();
             Territorio *t=dynamic_cast<Territorio *>(c2);
             cout<<"- "<<t->getNombre()<<endl;
             if(t->getOcupante()){
                 cout<<"Ocupante: "<<t->getOcupante()->getEmail()<<endl<<endl;
                 Iterador *it3 = new Iterador(t->getUnidades()->getPincipal()->getSig());
                 cout<<"***** UNIDADES *****"<<endl;
                 while(it3->existeActual()){
                     c3=it3->getActual();
                     Unidad *u=dynamic_cast<Unidad *>(c3);
                     cout<<"Tipo de unidad: "<<u->getTipo()->getNombre()<<endl;
                     cout<<"ID unidad: "<<u->getId()<<endl;
                     cout<<"Puntos de vida: "<<u->getVida()<<endl<<endl;
                     it3->sig();
                 }
             }
             else{
                 cout<<"OCUPANTE: vacio"<<endl;
                 cout<<"UNIDADES: no tiene"<<endl<<endl;
             }
             it2->sig();
         }
    }
}

Jugador * Partida::puedeJugar(const char* email){
    Coleccionable *c = jugadores->find(email);
    if(c==NULL)
        throw invalid_argument("Error, el email no es correcto");
    
    Jugador *j = dynamic_cast<Jugador *>(c);
    if(j->getInfoPartida()->getEliminado())
        throw invalid_argument("Error, este jugador esta eliminado");
    
    if(j->getInfoPartida()->getTurnoJugado() == turno_actual)
        throw invalid_argument("Error, este jugador ya jugo su turno");
    
    return j;
}

bool Partida::todosJugaronTurno(){
    Iterador *it = new Iterador(jugadores->getPincipal()->getSig());
    Coleccionable *c;
    bool jugaron_todos = true;
    
    while(it->existeActual() && jugaron_todos){
        c = it->getActual();
        Jugador *j = dynamic_cast<Jugador *>(c);
        if(j->getInfoPartida()->getEliminado() == false && j->getInfoPartida()->getTurnoJugado() < turno_actual)
            jugaron_todos = false;
        
        it->sig();
    }
    return jugaron_todos;
}
///////////////////////////////// DESTRUCTOR /////////////////////////////////
Partida::~Partida() {
}

