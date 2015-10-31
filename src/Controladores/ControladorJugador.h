/* 
 * File:   ControladorJugador.h
 * Author: Matias
 *
 * Created on 19 de junio de 2012, 15:54
 */

#ifndef CONTROLADORJUGADOR_H
#define	CONTROLADORJUGADOR_H

#include "../Coleccion/Lista.h"
#include "../Clases/Jugador.h"

class ControladorJugador {
private:
    Lista * jugadores;
public:
    ControladorJugador();
    Lista * getJugadores();
    Jugador * buscarJugador(const char *);
    void crearJugador(const char *, const char *, const char *, Fecha, const char *);
    void listarJugadores();
    void verPerfil(const char *);
    ~ControladorJugador();
};

#endif	/* CONTROLADORJUGADOR_H */

