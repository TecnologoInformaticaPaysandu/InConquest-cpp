/* 
 * File:   Mapa.h
 * Author: Matias
 *
 * Created on 17 de mayo de 2012, 12:23
 */

#ifndef MAPA_H
#define	MAPA_H

#include "../Coleccion/Coleccionable.h"
#include "Territorio.h"
#include "../Coleccion/Lista.h"

class Mapa : public Coleccionable {
private:
    char *nombre;
    int cant_terr;
    bool utilizado;
    Lista * terr;

public:
    Mapa(const char * = "");
    char * getNombre();
    int getCantTerr();
    bool getUtilizado();
    Lista * getTerritorios();
    void setUtilizado();
    Territorio * buscarTerritorio(const char *);
    
    void agregarTerritorio(const char *);
    void agregarAdyacencias(const char*, const char*);
    void mostrarInformacion();
    void listarTerritorios();
    void limpiarMapa();
    ~Mapa();
};

#endif	/* MAPA_H */

