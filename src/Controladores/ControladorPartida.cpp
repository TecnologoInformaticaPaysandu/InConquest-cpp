/* 
 * File:   ControladorPartida.cpp
 * Author: Matias
 * 
 * Created on 20 de junio de 2012, 11:04
 */

#include "ControladorPartida.h"
#include "../Coleccion/Iterador.h"
#include <stdexcept>
#include <iostream>

using namespace std;

ControladorPartida::ControladorPartida() {
    this->partidas=new Lista();
}

Lista * ControladorPartida::getPartidas(){
    return partidas;
}

Partida * ControladorPartida::crearPartida(const char* nombre, bool limite, int cant, Fecha fecha){
    Partida *p=new Partida(nombre,limite,cant,fecha);
    this->partidas->add(p,nombre);
    return p;
}

Partida * ControladorPartida::buscarPartida(const char* nombre){
    Coleccionable *c=partidas->find(nombre);
    if(!c)
        throw invalid_argument("Error, el nombre de la partida no es correcto");
    Partida *p=dynamic_cast<Partida *>(c);
    return p;
}

void ControladorPartida::listarPartidasEnCurso(){
    Iterador *it = new Iterador(partidas->getPincipal()->getSig());
    Coleccionable *c;
    
    while(it->existeActual()){
        c=it->getActual();
        Partida *p=dynamic_cast<Partida *>(c);
        if(!p->getFinalizada())
            cout<<p->getNombre()<<endl;
        it->sig();
    }
    cout<<endl;
}

ControladorPartida::~ControladorPartida() {
    delete partidas;
}

