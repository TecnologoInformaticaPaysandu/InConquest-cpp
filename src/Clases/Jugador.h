/* 
 * File:   Jugador.h
 * Author: Matias
 *
 * Created on 17 de junio de 2012, 17:27
 */

#ifndef JUGADOR_H
#define	JUGADOR_H

#include "../Coleccion/Coleccionable.h"
#include "../Coleccion/Lista.h"
#include "Territorio.h"
#include "Unidad.h"
#include "Objetivo.h"
#include "DatosEnPartida.h"
#include "Fecha.h"
#include <cstdlib>

class Partida; //forward declaration

class Jugador : public Coleccionable {
private:
    char * email;
    char * nombre;
    char * nacionalidad;
    char * sexo;
    Fecha nacimiento;
    Lista * terr_ocupados;
    Lista * unidades;
    Lista * partidas_jugadas;
    Objetivo * objetivo;
    DatosEnPartida * infoPartida;
    
public:
    Jugador(const char *, const char *, const char *, Fecha, const char *);
    char * getEmail();
    char * getNombre();
    char * getNacionalidad();
    char * getSexo();
    Fecha & getNacimiento();
    Lista * getTerritorios();
    Lista * getUnidades();
    Lista * getPartidas();
    Objetivo * getObjetivo();
    DatosEnPartida * getInfoPartida();
    void setObjetivo(Objetivo *);
    void setInfoPartida(int, int);
    bool cumplioObjetivo(Partida *);
    
    void agregarTerritorio(Territorio *);
    void agregarUnidad(Unidad *);
    Territorio * buscarTerritorio(const char *);
    Unidad * buscarUnidad(const char *);
    void agregarPartida(Partida *);
    void limpiarJugador();
    ~Jugador();
};

#endif	/* JUGADOR_H */

