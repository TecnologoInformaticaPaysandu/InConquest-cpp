/* 
 * File:   TipoUnidad.h
 * Author: Matias
 *
 * Created on 10 de junio de 2012, 0:29
 */

#ifndef TIPOUNIDAD_H
#define	TIPOUNIDAD_H

#include "../Coleccion/Coleccionable.h"

class TipoUnidad : public Coleccionable {
private:
    char* nombre;
    int ataque;
    int defensa;
    int costo;
public:
    TipoUnidad(const char*, int, int, int);
    char * getNombre();
    int getAtaque();
    int getDefensa();
    int getCosto();
    ~TipoUnidad();

};

#endif	/* TIPOUNIDAD_H */

