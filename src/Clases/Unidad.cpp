

#include <cstdlib>
#include "Unidad.h"
#include "Territorio.h"
#include "Jugador.h"
#include <string.h>
#include <iostream>

using namespace std;

///////////////////////////////// CONSTRUCTOR ////////////////////////////
Unidad::Unidad(const char* ident, TipoUnidad * t){
    int largo=strlen(ident);
    id=new char[largo+1];
    strcpy(id,ident);
    vida=10;
    tipo=t;
    ubicacion=NULL;
}
///////////////////////////////// GETS Y SETS ////////////////////////////
char * Unidad::getId(){
    return id;
}
int Unidad::getVida(){
    return vida;
}
void Unidad::setVida(int v){
    vida=v;
}
TipoUnidad * Unidad::getTipo(){
    return tipo;
}
Territorio * Unidad::getUbicacion(){
    return ubicacion;
}
void Unidad::setUbicacion(Territorio* t){
    ubicacion=t;
}

void Unidad::actualizarVida(int num){
    vida=vida-num;
    if(vida<0)
        vida=0;
}
bool Unidad::mover(Territorio* t){
    Jugador *duenio_unidad = this->getUbicacion()->getOcupante();
    Territorio *t_viejo = this->ubicacion;
    bool fue_ataque;
    
    if(t->getOcupante()==NULL){ //si no hay nadie
        duenio_unidad->agregarTerritorio(t);
        t->agregarUnidad(this);
        t_viejo->getUnidades()->remove(this->id, false);
        fue_ataque=false;
        cout<<"El territorio estaba vacio. Conquistaste el territorio"<<endl<<endl;
    }
    else{
        if(t->getOcupante()==duenio_unidad){ //si esta el mismo jugador
          t->agregarUnidad(this);
          t_viejo->getUnidades()->remove(this->id, false);
          fue_ataque=false;
          cout<<"El territorio ya te pertenecia, se agrego la unidad"<<endl<<endl;
        }   
        else{ //si esta otro jugador
            Unidad *def = t->getDefensora();
            cout<<"INFORMACION DE UNIDADES ANTES DEL ATAQUE"<<endl<<endl;
            cout<<"*** ATACANTE ***"<<endl;
            this->verInfo();
            cout<<"*** DEFENSORA ***"<<endl;
            def->verInfo();
            
            this->atacar(t);
            
            cout<<"INFORMACION DE UNIDADES DESPUES DEL ATAQUE"<<endl<<endl;
            cout<<"*** ATACANTE ***"<<endl;
            this->verInfo();
            cout<<"*** DEFENSORA ***"<<endl;
            def->verInfo();
            fue_ataque=true;
        }
    }
    return fue_ataque;
}

void Unidad::verInfo(){
    cout<<"ID: "<<this->id<<endl;
    cout<<"Vida: "<<this->vida<<endl;
    cout<<"Tipo: "<<this->getTipo()->getNombre()<<endl;
    cout<<"Ataque: "<<this->getTipo()->getAtaque()<<endl;
    cout<<"Defensa: "<<this->getTipo()->getDefensa()<<endl<<endl;
}
void Unidad::atacar(Territorio *t){
    Unidad *def = t->getDefensora();
    while(this->vida>0 && def->vida>0){
        
        this->actualizarVida(def->tipo->getDefensa());
        def->actualizarVida(this->tipo->getAtaque());
    }
}
///////////////////////////////// DESTRUCTOR /////////////////////////////////
Unidad::~Unidad(){
    tipo=NULL;
    ubicacion=NULL;
}