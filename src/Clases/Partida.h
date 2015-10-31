/* 
 * File:   Partida.h
 * Author: Matias
 *
 * Created on 20 de junio de 2012, 11:08
 */

#ifndef PARTIDA_H
#define	PARTIDA_H

#include "../Coleccion/Coleccionable.h"
#include "Fecha.h"
#include "../Coleccion/Lista.h"
#include "Mapa.h"
#include "Jugador.h"
#include "Unidad.h"

class Partida : public Coleccionable {
private:
    char * nombre;
    bool tiene_limite_turnos;
    int cant_turnos;
    int turno_actual;
    bool finalizada;
    Fecha fecha_jugada;
    Mapa * mapa;
    Lista * jugadores;
    Lista * ganadores;
    Lista * tipos_unidades;
public:
    Partida(const char *, bool, int, Fecha);
    char * getNombre();
    int getCantTurnos();
    int getTurnoActual();
    bool getTieneLimite();
    bool getFinalizada();
    Fecha & getFecha();
    Mapa * getMapa();
    Lista * getJugadores();
    Lista * getGanadores();
    Lista * getTiposUndades();
    
    void setMapa(Mapa *);
    void finalizar();
    void actualizarTurno();
    void setTurnoActual(int);
    void agregarJugador(Jugador *);
    void agregarGanador(const char *);
    void agregarTipoUnidad(TipoUnidad *);
    
    void colocarJugador(Jugador *, Territorio *, Unidad *);
    void asignarObjetivo(Jugador *, Objetivo *);
    void verInfoPartida();
    bool todosJugaronTurno();
    void sumarCreditos(int);
    Jugador * puedeJugar(const char *);
    
    ~Partida();
};

#endif	/* PARTIDA_H */

