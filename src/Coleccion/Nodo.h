/* 
 * File:   Nodo.h
 * Author: Matias
 *
 * Created on 2 de junio de 2012, 1:29
 */

#ifndef NODO_H
#define	NODO_H

#include "Coleccionable.h"
#include <cstdlib>

class Nodo {
private:
    Coleccionable * dato;
    Nodo * sig;
    char * clave;
public:
    
    Nodo(Coleccionable * = NULL, const char * = "dami");
    Coleccionable * getDato();
    Nodo * getSig();
    char * getClave();
    void setSig(Nodo *);
    void add(Coleccionable *, const char *);
    void remove(const char *, bool);
    bool member(const char *);
    Coleccionable * find(const char *);
    ~Nodo();
};

#endif	/* NODO_H */

