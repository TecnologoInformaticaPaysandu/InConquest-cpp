/* 
 * File:   Dominacion.h
 * Author: Matias
 *
 * Created on 17 de junio de 2012, 0:34
 */

#ifndef DOMINACION_H
#define	DOMINACION_H

#include "Objetivo.h"
#include "../Coleccion/Lista.h"
#include "Territorio.h"

class Dominacion : public Objetivo {
private:
    Lista * territorios;
public:
    Dominacion();
    ~Dominacion();
    Lista * getTerritorios();
    void agregarTerritorio(Territorio *);
    void imprimirDatos();
};

#endif	/* DOMINACION_H */

