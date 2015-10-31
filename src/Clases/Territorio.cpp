/* 
 * File:   Territorio.cpp
 * Author: Matias
 * 
 * Created on 17 de mayo de 2012, 12:24
 */

#include "Territorio.h"
#include "../Coleccion/Iterador.h"
#include "Jugador.h"
#include <string.h>
#include <iostream>
#include <stdexcept>

using namespace std;

/////////////////////////////// CONSTRUCTOR //////////////////////////////////
Territorio::Territorio(const char* t){
    int largo = strlen(t);
    nombre = new char[largo+1];
    strcpy(nombre, t);
    cant_ady = 0;
    adyacentes = new Lista();
    ocupante=NULL;
    unidades=new Lista();
    defensora=NULL;
}
//////////////////////////////// GETS Y SETS //////////////////////////////////
char * Territorio::getNombre(){
    return nombre;
}
int Territorio::getCantAdy(){
    return cant_ady;
}
Lista * Territorio::getAdyacentes(){
    return adyacentes;
}
Jugador * Territorio::getOcupante(){
    return ocupante;
}
Lista * Territorio::getUnidades(){
    return unidades;
}
Unidad * Territorio::getDefensora(){
    return defensora;
}

void Territorio::setOcupante(Jugador* j){
    ocupante=j;
}

void Territorio::nuevaDefensora(){ 
    if(unidades->getCantNodos() == 0)
        defensora=NULL;
    else{
        Iterador *it = new Iterador(unidades->getPincipal()->getSig());
        Coleccionable *c = it->getActual();
        
        defensora = dynamic_cast<Unidad *>(c);
        it->sig();
        
        while(it->existeActual()){
            c = it->getActual();
            Unidad *u = dynamic_cast<Unidad *>(c);
            
            if(u->getTipo()->getDefensa() > defensora->getTipo()->getDefensa())
                defensora=u;
            else{
                if(u->getTipo()->getDefensa()==defensora->getTipo()->getDefensa() && u->getVida()<defensora->getVida())
                    defensora=u;
                else
                    if(u->getTipo()->getDefensa()==defensora->getTipo()->getDefensa()&&u->getVida()==defensora->getVida())
                        if(strcmp(u->getId(),defensora->getId())<0)
                            defensora=u;
            }
            it->sig();
        }
    }
}

void Territorio::agregarAdyacente(Territorio* t){
    adyacentes->add(t,t->nombre);
    cant_ady++;
}

void Territorio::agregarUnidad(Unidad* u){
    unidades->add(u, u->getId());
    u->setUbicacion(this);
    
    if(defensora!=NULL){
        if(u->getTipo()->getDefensa() > defensora->getTipo()->getDefensa())
            defensora=u;
        else{
            if(u->getTipo()->getDefensa()==defensora->getTipo()->getDefensa() && u->getVida()<defensora->getVida())
                defensora=u;
            else
                if(u->getTipo()->getDefensa()==defensora->getTipo()->getDefensa()&&u->getVida()==defensora->getVida())
                    if(strcmp(u->getId(),defensora->getId())<0)
                            defensora=u;
        }   
    }
    else
        defensora=u;
}

void Territorio::mostrarInformacion(){
    Iterador *it=new Iterador(adyacentes->getPincipal()->getSig());
    Coleccionable *c;
    cout<<this->nombre<<" limita con: "<<endl;
    
    while(it->existeActual()){
        c=it->getActual();
        Territorio *t=dynamic_cast<Territorio *>(c);
        cout<<"* "<<t->nombre<<endl;
        it->sig();
    }
}

void Territorio::limpiarTerritorio(){
    defensora = NULL;
    ocupante->limpiarJugador();
    ocupante = NULL;
    delete unidades;
    unidades = new Lista();
}

//////////////////////////////// DESTRUCTOR //////////////////////////////////
Territorio::~Territorio() {
    delete adyacentes;
    delete unidades;
}

