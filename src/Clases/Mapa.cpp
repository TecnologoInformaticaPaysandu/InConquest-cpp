/* 
 * File:   Mapa.cpp
 * Author: Matias
 * 
 * Created on 17 de mayo de 2012, 12:23
 */

#include "Mapa.h"
#include "../Coleccion/Iterador.h"
#include <iostream>
#include <string.h>
#include <stdexcept>

using namespace std;
///////////////////////////////// CONSTRUCTOR //////////////////////////////////
Mapa::Mapa(const char* m) {
    int largo = strlen(m);
    nombre = new char[largo+1];
    strcpy(nombre, m);
    terr = new Lista();
    cant_terr = 0;
    utilizado=false;
}
//////////////////////////////// GETS Y SETS //////////////////////////////////
char * Mapa::getNombre(){
    return nombre;
}
int Mapa::getCantTerr(){
    return cant_terr;
}
bool Mapa::getUtilizado(){
    return utilizado;
}
Lista * Mapa::getTerritorios(){
    return terr;
}
void Mapa::setUtilizado(){
    utilizado=true;
}
///////////////////////////////////// DESTRUCTOR //////////////////////////////
Mapa::~Mapa() {
    Iterador *it = new Iterador(terr->getPincipal()->getSig());
    Coleccionable *c;
    while(it->existeActual()){
        c = it->getActual();
        Territorio *t = dynamic_cast<Territorio *>(c);
        delete t;
        it->sig();
    }
    delete terr;
}
///////////////// BUSCAR TERITORIO, AGREGAR TERRITORIO Y ADYACENCIAS ///////////
Territorio * Mapa::buscarTerritorio(const char* nombre){
    Coleccionable *c=terr->find(nombre);
    if(!c)
        throw invalid_argument("Error, el nombre del territorio no es correcto");
    Territorio *t=dynamic_cast<Territorio *>(c);
    return t;
}

void Mapa::agregarTerritorio(const char* nombre){
    Territorio *t = new Territorio(nombre);
    terr->add(t,nombre);
    cant_terr++;
}

void Mapa::agregarAdyacencias(const char* terr1, const char* terr2){
    Coleccionable *c1=terr->find(terr1);
    Coleccionable *c2=terr->find(terr2);
    
    if(!c1 && !c2)
        throw invalid_argument("Error, los dos territorios son incorrectos");
    else if(!c1)
        throw invalid_argument("Error, el primer territorio no es correcto");
    else if(!c2)
        throw invalid_argument("Error, el segundo territorio no es correcto");
    
    
    Territorio *t1=dynamic_cast<Territorio *>(c1);
    Territorio *t2=dynamic_cast<Territorio *>(c2);
    t1->agregarAdyacente(t2);
    t2->agregarAdyacente(t1);
}

void Mapa::mostrarInformacion(){
    Iterador * it=new Iterador(terr->getPincipal()->getSig());
    Coleccionable *c;
    
    while(it->existeActual()){
        c=it->getActual();
        Territorio *t=dynamic_cast<Territorio *>(c);
        t->mostrarInformacion();
        cout<<endl;
        it->sig();
    }
}

void Mapa::listarTerritorios(){
    Iterador * it=new Iterador(terr->getPincipal()->getSig());
    Coleccionable *c;
    cout<<"Territorios del mapa:"<<endl<<endl;
    while(it->existeActual()){
        c=it->getActual();
        Territorio *t=dynamic_cast<Territorio *>(c);
        cout<<t->getNombre()<<endl;
        it->sig();
    }
    cout<<endl;
}

void Mapa::limpiarMapa(){
    Iterador *it = new Iterador(terr->getPincipal()->getSig());
    Coleccionable *c;
    
    while(it->existeActual()){
        c = it->getActual();
        Territorio *t = dynamic_cast<Territorio *>(c);
        t->limpiarTerritorio();
        it->sig();
    }
}