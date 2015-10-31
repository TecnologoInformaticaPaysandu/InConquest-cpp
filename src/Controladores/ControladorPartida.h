/* 
 * File:   ControladorPartida.h
 * Author: Matias
 *
 * Created on 20 de junio de 2012, 11:04
 */

#ifndef CONTROLADORPARTIDA_H
#define	CONTROLADORPARTIDA_H

#include "../Coleccion/Coleccionable.h"
#include "../Coleccion/Lista.h"
#include "../Coleccion/Iterador.h"
#include "../Clases/Partida.h"

class ControladorPartida {
private:
    Lista * partidas;
public:
    ControladorPartida();
    Lista * getPartidas();
    Partida * crearPartida(const char *, bool, int, Fecha);
    Partida * buscarPartida(const char *);
    void listarPartidasEnCurso();
    ~ControladorPartida();
};

#endif	/* CONTROLADORPARTIDA_H */

