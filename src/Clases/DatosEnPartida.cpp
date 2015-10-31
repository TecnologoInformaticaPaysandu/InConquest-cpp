/* 
 * File:   DatosEnPartida.cpp
 * Author: Persona
 * 
 * Created on 23 de junio de 2012, 09:06 PM
 */

#include "DatosEnPartida.h"
#include <cstdlib>

DatosEnPartida::DatosEnPartida() {
    creditos=0;
    turnoJugado=0;
    eliminado=false;
    quien_lo_elimino=NULL;
}

DatosEnPartida::DatosEnPartida(int creditos, int turno){
    this->creditos=creditos;
    this->turnoJugado=turno;
    this->eliminado=false;
    quien_lo_elimino=NULL;
}
int DatosEnPartida::getCreditos(){
    return creditos;
}
int DatosEnPartida::getTurnoJugado(){
    return turnoJugado;
}
bool DatosEnPartida::getEliminado(){
    return eliminado;
}
Jugador * DatosEnPartida::getQuienLoElimino(){
    return quien_lo_elimino;
}
void DatosEnPartida::setQuienLoElimino(Jugador *j){
    quien_lo_elimino=j;
}
void DatosEnPartida::setTurnoJugado(int num){
    turnoJugado=num;
}
void DatosEnPartida::setEliminado(){
    eliminado=true;
}

void DatosEnPartida::actualizarCreditos(int cantidad){
    creditos = creditos + cantidad;
}

void DatosEnPartida::actualizarTurno(){
    turnoJugado++;
}

DatosEnPartida::~DatosEnPartida() {
    quien_lo_elimino = NULL;
}

