/* 
 * File:   Eliminacion.h
 * Author: Matias
 *
 * Created on 21 de junio de 2012, 1:00
 */

#ifndef ELIMINACION_H
#define	ELIMINACION_H

#include "Objetivo.h"

class Jugador;  //forward declaration

class Eliminacion : public Objetivo{
private:
    Jugador * jugador;
public:
    Eliminacion();
    Jugador * getJugador();
    void setJugador(Jugador *);
    void imprimirDatos();
    ~Eliminacion();
};

#endif	/* ELIMINACION_H */

