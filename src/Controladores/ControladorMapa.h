/* 
 * File:   ControladorMapa.h
 * Author: Matias
 *
 * Created on 13 de junio de 2012, 23:18
 */

#ifndef CONTROLADORMAPA_H
#define	CONTROLADORMAPA_H

#include "../Coleccion/Lista.h"
#include "../Clases/Mapa.h"

class ControladorMapa {
private:
    Lista * mapas;
public:
    ControladorMapa();
    Lista * getMapas();
    Mapa * crearMapa(const char *);
    Mapa * buscarMapa(const char *);
    void eliminarMapa(const char *);
    void listarMapas();
    ~ControladorMapa();
};

#endif	/* CONTROLADORMAPA_H */

