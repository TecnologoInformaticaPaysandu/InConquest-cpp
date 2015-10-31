/* 
 * File:   Eliminacion.cpp
 * Author: Matias
 * 
 * Created on 21 de junio de 2012, 1:00
 */

#include <cstdlib>
#include "Eliminacion.h"
#include "Jugador.h"
#include <iostream>

using namespace std;

Eliminacion::Eliminacion() {
    jugador=NULL;
}
Jugador * Eliminacion::getJugador(){
    return jugador;
}
void Eliminacion::setJugador(Jugador* j){
    jugador=j;
}

void Eliminacion::imprimirDatos(){
    cout<<"Eliminar a: "<<jugador->getEmail()<<endl;
}
Eliminacion::~Eliminacion() {
    jugador = NULL;
}

