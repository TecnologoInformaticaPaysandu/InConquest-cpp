/* 
 * File:   DatosEnPartida.h
 * Author: Persona
 *
 * Created on 23 de junio de 2012, 09:06 PM
 */

#ifndef DATOSENPARTIDA_H
#define	DATOSENPARTIDA_H

class Jugador; //forward declaration

class DatosEnPartida {
private:
    int creditos;
    int turnoJugado;
    bool eliminado;
    Jugador *quien_lo_elimino;
public:
    DatosEnPartida();
    DatosEnPartida(int, int);
    int getCreditos();
    int getTurnoJugado();
    bool getEliminado();
    Jugador * getQuienLoElimino();
    void setQuienLoElimino(Jugador *);
    void setTurnoJugado(int);
    void setEliminado();
    void actualizarCreditos(int);
    void actualizarTurno();
    ~DatosEnPartida();


};

#endif	/* DATOSENPARTIDA_H */

