/* 
 * File:   Iterador.cpp
 * Author: Matias
 * 
 * Created on 19 de junio de 2012, 0:47
 */

#include "Iterador.h"
#include <cstdlib>

///////////////////////////// CONSTRUCTORES ///////////////////////////
Iterador::Iterador() {
    actual=NULL;
}
Iterador::Iterador(Nodo* nodo){
    actual=nodo;
}
/////////////////////////// OPERACIONES DE ITERADOR /////////////////////
void Iterador::sig(){
    actual=actual->getSig();
}
bool Iterador::existeActual(){
    return (actual!=NULL);
}
Coleccionable * Iterador::getActual(){
    return this->actual->getDato();
}

char * Iterador::getClave(){
    return actual->getClave();
}
///////////////////////////////// DESTRUCTOR /////////////////////////////////
Iterador::~Iterador() {
    actual=NULL;
}

