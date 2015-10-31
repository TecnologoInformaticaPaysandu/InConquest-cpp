/* 
 * File:   ControladorUnidades.h
 * Author: Matias
 *
 * Created on 11 de junio de 2012, 23:36
 */

#ifndef CONTROLADORUNIDAD_H
#define	CONTROLADORUNIDAD_H

#include "../Coleccion/Lista.h"
#include "../Clases/TipoUnidad.h"
#include "../Clases/Unidad.h"

class ControladorUnidad {
private:
    Lista * tipos;
    Lista * unidades;
public:
    ControladorUnidad();
    ~ControladorUnidad();
    Lista * getUnidades();
    Lista * getTipos();
    Unidad * crearUnidad(const char *, TipoUnidad *);
    void crearTipoUnidad(const char *, int, int, int);
    void eliminarUnidad(const char *);
    TipoUnidad * buscarTipoUnidad(const char *);
    void listarTiposUnidades();
    void eliminarUnidadesNoUsadas();
};

#endif	/* CONTROLADORUNIDAD_H */

