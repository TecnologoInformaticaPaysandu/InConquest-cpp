/* 
 * File:   TipoUnidad.cpp
 * Author: Matias
 * 
 * Created on 10 de junio de 2012, 0:29
 */

#include "TipoUnidad.h"
#include <string.h>

///////////////////////////////// CONSTRUCTOR /////////////////////////////////
TipoUnidad::TipoUnidad(const char* nom, int a, int d, int c) {
    int largo=strlen(nom);
    nombre=new char[largo+1];
    strcpy(nombre,nom);
    ataque=a;
    defensa=d;
    costo=c;
}
///////////////////////////////// GETS Y SETS //////////////////////////////////
char * TipoUnidad::getNombre(){
    return nombre;
}
int TipoUnidad::getAtaque(){
    return ataque;
}
int TipoUnidad::getDefensa(){
    return defensa;
}
int TipoUnidad::getCosto(){
    return costo;
}
///////////////////////////////// DESTRUCTOR //////////////////////////////////
TipoUnidad::~TipoUnidad() {
}

