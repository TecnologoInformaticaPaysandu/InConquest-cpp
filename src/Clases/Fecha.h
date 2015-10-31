/* 
 * File:   Fecha.h
 * Author: Matias
 *
 * Created on 17 de junio de 2012, 18:30
 */

#ifndef FECHA_H
#define	FECHA_H

class Fecha {
private:
    int dia;
    int mes;
    int anio;
public:
    Fecha();
    Fecha(int, int, int);
    Fecha(const Fecha &);
    int getDia();
    int getMes();
    int getAnio();
    void setFecha(int, int, int);
    void imprimir();
    ~Fecha();
    Fecha & operator=(const Fecha);
};

bool esCorrecta(int, int, int);
bool esBisiesto(int);
#endif	/* FECHA_H */

