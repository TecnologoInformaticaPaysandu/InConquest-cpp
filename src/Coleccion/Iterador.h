/* 
 * File:   Iterador.h
 * Author: Matias
 *
 * Created on 19 de junio de 2012, 0:47
 */

#ifndef ITERADOR_H
#define	ITERADOR_H

#include "Coleccionable.h"
#include "Nodo.h"

class Iterador {
private:
    Nodo * actual;
public:
    Iterador();
    Iterador(Nodo *);
    void sig();
    bool existeActual();
    Coleccionable * getActual();
    char * getClave();
    ~Iterador();
};

#endif	/* ITERADOR_H */

