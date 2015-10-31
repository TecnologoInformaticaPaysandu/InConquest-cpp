/* 
 * File:   Lista.h
 * Author: Matias
 *
 * Created on 2 de junio de 2012, 1:26
 */

#ifndef LISTA_H
#define	LISTA_H

#include "Nodo.h"

class Lista {
private:
    Nodo * principal;
public:
    Lista();
    Nodo * getPincipal();
    void add(Coleccionable *, const char *);
    void remove(const char *, bool);
    bool member(const char *);
    int getCantNodos();
    Coleccionable * find(const char *);
    void listar();
    ~Lista();
};

#endif	/* LISTA_H */

