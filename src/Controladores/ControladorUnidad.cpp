


#include "../Coleccion/Iterador.h"
#include "ControladorUnidad.h"
#include "../Clases/Territorio.h"
#include "../Clases/Jugador.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

ControladorUnidad::ControladorUnidad(){
    tipos=new Lista();
    unidades=new Lista();
}

ControladorUnidad::~ControladorUnidad(){
    delete unidades;
    delete tipos;
}

Lista * ControladorUnidad::getUnidades(){
    return unidades;
}

Lista * ControladorUnidad::getTipos(){
    return tipos;
}

Unidad * ControladorUnidad::crearUnidad(const char* ident, TipoUnidad* tipo){
    Unidad *u=new Unidad(ident, tipo);
    unidades->add(u,ident);
    return u;
}

void ControladorUnidad::crearTipoUnidad(const char* nom, int a, int d, int c){
    TipoUnidad *t=new TipoUnidad(nom,a,d,c);
    tipos->add(t,nom);
}

TipoUnidad * ControladorUnidad::buscarTipoUnidad(const char* tipo){
    Coleccionable *c=tipos->find(tipo);
    if(!c)
        throw invalid_argument("Error, el tipo de unidad no es correcto");
    TipoUnidad *tu=dynamic_cast<TipoUnidad *>(c);
    return tu;
}

void ControladorUnidad::listarTiposUnidades(){
    Iterador *it=new Iterador(tipos->getPincipal()->getSig());
    Coleccionable *c;
    
    while(it->existeActual()){
        c=it->getActual();
        TipoUnidad * t=dynamic_cast<TipoUnidad *>(c);
        cout<<"*** "<<t->getNombre()<<" ***"<<endl;
        cout<<"* Ataque: "<<t->getAtaque()<<endl;
        cout<<"* Defensa: "<<t->getDefensa()<<endl;
        cout<<"* Costo: "<<t->getCosto()<<endl<<endl;
        it->sig();
    }
}

void ControladorUnidad::eliminarUnidad(const char* id){
    Coleccionable *c = unidades->find(id);
    Unidad *u = dynamic_cast<Unidad *>(c);
    Territorio *ubicacion = u->getUbicacion();
    Jugador *duenio = ubicacion->getOcupante();
    
    ubicacion->getUnidades()->remove(id,false);
    duenio->getUnidades()->remove(id,false);
    unidades->remove(id,true);
}

void ControladorUnidad::eliminarUnidadesNoUsadas(){
    Iterador *it = new Iterador(unidades->getPincipal()->getSig());
    Coleccionable *c;
    
    while(it->existeActual()){
        c = it->getActual();
        Unidad *u = dynamic_cast<Unidad *>(c);
        if(u->getUbicacion()->getOcupante() == NULL)
            this->eliminarUnidad(u->getId());
        
        it->sig();
    }
}