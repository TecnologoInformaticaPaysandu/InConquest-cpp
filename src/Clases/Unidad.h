/* 
 * File:   Unidad.h
 * Author: Matias
 *
 * Created on 12 de junio de 2012, 0:22
 */

#ifndef UNIDAD_H
#define	UNIDAD_H

#include "../Coleccion/Coleccionable.h"
#include "TipoUnidad.h"
#include <cstdlib>

class Territorio; // forward declaration

class Unidad : public Coleccionable {
private:
    char* id;
    int vida;
    TipoUnidad * tipo;
    Territorio * ubicacion;
public:
    Unidad(const char*, TipoUnidad * = NULL);
    char * getId();
    int getVida();
    void setVida(int);
    void actualizarVida(int);
    TipoUnidad * getTipo();
    Territorio * getUbicacion();
    void setUbicacion(Territorio *);
    bool mover(Territorio *);
    void atacar(Territorio *);
    void verInfo();
    ~Unidad();
    
};

#endif	/* UNIDAD_H */

