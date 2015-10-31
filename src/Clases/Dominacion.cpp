

#include "Dominacion.h"
#include <cstdlib>
#include <string.h>
#include <iostream>

using namespace std;

/////////////////////////////////// CONSTRUCTOR ////////////////////////////////
Dominacion::Dominacion(){
    territorios=new Lista();
}
////////////////////////////////// GETS Y SETS /////////////////////////////////

Lista * Dominacion::getTerritorios(){
    return territorios;
}

void Dominacion::agregarTerritorio(Territorio* t){
    territorios->add(t,t->getNombre());
}

void Dominacion::imprimirDatos(){
    cout<<"Territorios a conquistar: "<<endl;
    territorios->listar();
}
////////////////////////////////// DESTRUCTOR //////////////////////////////////
Dominacion::~Dominacion(){
    delete territorios;
}

