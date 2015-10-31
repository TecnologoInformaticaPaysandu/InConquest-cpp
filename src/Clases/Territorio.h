/* 
 * File:   Territorio.h
 * Author: Matias
 *
 * Created on 17 de mayo de 2012, 12:24
 */

#ifndef TERRITORIO_H
#define	TERRITORIO_H

#include "../Coleccion/Coleccionable.h"
#include "../Coleccion/Lista.h"
#include "Unidad.h"

class Jugador;// forward declaration

class Territorio : public Coleccionable {
private:
    char* nombre;
    int cant_ady;
    Lista * adyacentes;
    Lista * unidades;
    Unidad * defensora;
    Jugador * ocupante;
    
public:
    Territorio(const char*);
    char * getNombre();
    int getCantAdy();
    Unidad * getDefensora();
    Jugador * getOcupante();
    Lista * getAdyacentes();
    Lista * getUnidades();
    void setOcupante(Jugador *);
    void nuevaDefensora();
    void agregarAdyacente(Territorio *);
    void agregarUnidad(Unidad *);
    void mostrarInformacion();
    void limpiarTerritorio();
    ~Territorio();
};

#endif	/* TERRITORIO_H */

