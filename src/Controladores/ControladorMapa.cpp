/* 
 * File:   ControladorMapa.cpp
 * Author: Matias
 * 
 * Created on 13 de junio de 2012, 23:18
 */

#include "ControladorMapa.h"
#include "../Coleccion/Iterador.h"
#include <stdexcept>
#include <iostream>

using namespace std;

ControladorMapa::ControladorMapa() {
    mapas=new Lista();
}

Lista * ControladorMapa::getMapas(){
    return mapas;
}

Mapa * ControladorMapa::crearMapa(const char* nombre){
    Mapa *m=new Mapa(nombre);
    mapas->add(m, nombre);
    return m;
}

void ControladorMapa::eliminarMapa(const char* nombre){
    Coleccionable *c=mapas->find(nombre);
    if(!c)
        throw invalid_argument("Error, el nombre del mapa no es correcto");
    Mapa *m=dynamic_cast<Mapa *>(c);
    if(!m->getUtilizado()){
        mapas->remove(nombre,true);
        cout<<"El mapa se elimino correctamente"<<endl;
    }
    else
        cout<<"No se puede eliminar un mapa que ha sido utilizado en alguna partida"<<endl;
}

Mapa * ControladorMapa::buscarMapa(const char* nombre){
    Coleccionable *c=mapas->find(nombre);
    if(!c)
        throw invalid_argument("Error, el nombre del mapa no es correcto");
    Mapa *m=dynamic_cast<Mapa *>(c);
    return m;    
}

void ControladorMapa::listarMapas(){
    Iterador *it=new Iterador(mapas->getPincipal()->getSig());
    Coleccionable *c;
    cout<<"Mapas del Sistema:"<<endl<<endl;
    while(it->existeActual()){
        c=it->getActual();
        Mapa *m=dynamic_cast<Mapa *>(c);
        cout<<m->getNombre()<<endl;
        it->sig();
    }
}

ControladorMapa::~ControladorMapa() {
    delete mapas;
}

