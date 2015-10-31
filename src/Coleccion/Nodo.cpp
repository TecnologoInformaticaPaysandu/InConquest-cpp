

#include <cstdlib>
#include <iostream>
#include <string.h>
#include "Nodo.h"
#include "../Clases/Territorio.h"


using std::cout;

/////////////////////////////// CONSTRUCTOR //////////////////////////////////
Nodo::Nodo(Coleccionable* c, const char* k){
    int largo=strlen(k);
    dato=c;
    sig=NULL;
    clave=new char[largo+1];
    strcpy(clave, k);
}
/////////////////////////////// GETS Y SETS ///////////////////////////////////
Coleccionable * Nodo::getDato(){
    return dato;
}
Nodo * Nodo::getSig(){
    return sig;
}
char * Nodo::getClave(){
    return clave;
}
/////////////////////////// ADD, REMOVE, MEMBER Y FIND ////////////////////////
void Nodo::add(Coleccionable* c, const char* k){
    Nodo *nuevo=new Nodo(c,k);
    
    nuevo->sig=this->sig;
    this->sig=nuevo;
}
void Nodo::remove(const char* k, bool borrar_dato){
    if(sig){
        if(strcmp(sig->clave,k)==0){
            Nodo *aux=sig;
            this->sig=aux->sig;
            aux->sig=NULL;
            if(borrar_dato)
                delete aux->dato;
            delete aux;
        }
        else{
            sig->remove(k,borrar_dato);
        }
    }
}
bool Nodo::member(const char* k){
    if(strcmp(clave,k)==0)
        return true;
    else{
        if(sig)
            sig->member(k);
        else
            return false;
    }
}
Coleccionable * Nodo::find(const char* k){
    if(strcmp(clave,k)==0)
        return dato;
    else{
        if(sig)
            sig->find(k);
        else
            return NULL;
    }
}
//////////////////////////////// DESTRUCTOR ///////////////////////////////////
Nodo::~Nodo(){
    dato = NULL;
    if(sig)
        delete sig;
}