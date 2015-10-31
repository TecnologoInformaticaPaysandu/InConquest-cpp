/* 
 * File:   ControladorJugador.cpp
 * Author: Matias
 * 
 * Created on 19 de junio de 2012, 15:54
 */

#include "ControladorJugador.h"
#include "../Coleccion/Iterador.h"
#include "../Clases/Partida.h"
#include <stdexcept>
#include <iostream>

using namespace std;

ControladorJugador::ControladorJugador() {
    jugadores=new Lista();
}

Lista * ControladorJugador::getJugadores(){
    return jugadores;
}

Jugador * ControladorJugador::buscarJugador(const char* email){
    Coleccionable *c=jugadores->find(email);
    if(!c)
        throw invalid_argument("Error, el e-mail del jugador no es correcto");
    Jugador *j=dynamic_cast<Jugador *>(c);
    return j;
}

void ControladorJugador::listarJugadores(){
    Iterador *it=new Iterador(jugadores->getPincipal()->getSig());
    Coleccionable *c;
    cout<<"Listado de Jugadores del Sistema:"<<endl<<endl;
    while(it->existeActual()){
        c=it->getActual();
        Jugador *j=dynamic_cast<Jugador *>(c);
        cout<<j->getEmail()<<endl;
        it->sig();
    }
    cout<<endl;
}

void ControladorJugador::crearJugador(const char* email, const char* nom, const char* nac, Fecha f, const char *s){
    Jugador *j=new Jugador(email,nom,nac,f,s);
    jugadores->add(j,email);
}

void ControladorJugador::verPerfil(const char* email){
    Jugador *j=this->buscarJugador(email);
    Iterador *it = new Iterador(j->getPartidas()->getPincipal()->getSig());
    Coleccionable *c1, *c2;
    if(!j)
        throw invalid_argument("No se pudo mostrar el perfil del usuario");
    cout<<endl<<"Nombre: "<<j->getNombre()<<endl;
    cout<<"Nacionalidad: "<<j->getNacionalidad()<<endl;
    cout<<"Sexo: "<<j->getSexo()<<endl;
    cout<<"Fecha Nacimiento: ";
    j->getNacimiento().imprimir();
    cout<<endl;
    cout<<"INFORMACION DE PARTIDAS JUGADAS:"<<endl<<endl;
    
    while(it->existeActual()){
        c1=it->getActual();
        Partida *p = dynamic_cast<Partida *>(c1);
        if(p->getFinalizada()){
            Iterador *i2 = new Iterador(p->getGanadores()->getPincipal()->getSig());
            cout<<"Nombre: "<<p->getNombre()<<endl;
            cout<<"Mapa: "<<p->getMapa()->getNombre()<<endl;
            cout<<"Ganadores: ";
            while(i2->existeActual()){
                c2=i2->getActual();
                Jugador *g = dynamic_cast<Jugador *>(c2);
                cout<<g->getEmail();
                i2->sig();
                if(i2->existeActual())//si no es el ultimo pone un guion entre los nombres
                    cout<<" - ";
            }
            cout<<endl<<endl;
        }
        it->sig();
    }
}

ControladorJugador::~ControladorJugador() {
    delete jugadores;
}

