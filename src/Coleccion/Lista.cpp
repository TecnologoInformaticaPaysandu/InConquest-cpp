


#include "Lista.h"
#include "Iterador.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Lista::Lista(){
    principal=new Nodo();
}

Nodo * Lista::getPincipal(){
    return principal;
}

void Lista::add(Coleccionable* objeto, const char* clave){
    principal->add(objeto,clave);
}

void Lista::remove(const char* clave, bool borrar_dato){
    principal->remove(clave,borrar_dato);
}

Coleccionable * Lista::find(const char* clave){
    principal->find(clave);
}

bool Lista::member(const char* clave){
    principal->member(clave);
}

void Lista::listar(){
    Iterador *it=new Iterador(principal->getSig());
    cout<<endl;
    
    while(it->existeActual()){
        cout<<it->getClave()<<endl;
        it->sig();
    }
}

int Lista::getCantNodos(){
    int cant=0;
    Iterador *it = new Iterador(principal->getSig());
    while(it->existeActual()){
        cant++;
        it->sig();
    }
    return cant;
}
Lista::~Lista(){
    delete principal;
}