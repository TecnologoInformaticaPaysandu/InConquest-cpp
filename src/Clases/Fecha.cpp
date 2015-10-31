/* 
 * File:   Fecha.cpp
 * Author: Matias
 * 
 * Created on 17 de junio de 2012, 18:30
 */

#include "Fecha.h"
#include <iostream>

using namespace std;

////////////////////////// CONSTRUCTORES ////////////////////////////
Fecha::Fecha(){
    dia=0;
    mes=0;
    anio=0;
}
Fecha::Fecha(int d, int m, int a) {
    dia=d;
    mes=m;
    anio=a;
}
Fecha::Fecha(const Fecha &f){
    dia=f.dia;
    mes=f.mes;
    anio=f.anio;
}
////////////////////////// GETS Y SETS ///////////////////////////////
int Fecha::getDia(){
    return dia;
}
int Fecha::getMes(){
    return mes;
}
int Fecha::getAnio(){
    return anio;
}
void Fecha::setFecha(int d, int m, int a){
    if(esCorrecta(d,m,a)){
        dia=d;
        mes=m;
        anio=a;
    }
    else
        cout<<"La fecha ingresada no es correcta"<<endl;
}
/////////////////////// DESTRUCTOR ////////////////////////////////////
Fecha::~Fecha() {
}
////////////////////// IMPRIMIR FECHA //////////////////////////////////
void Fecha::imprimir(){
    cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
}
////////////////////////// VALIDACION DE FECHA //////////////////////////
bool esCorrecta(int d, int m, int a){
    int diasDelMes[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(a<=0)
        return false;
    if(d<=0 || d>31)
        return false;
    if(m<=0 || m>12)
        return false;
    if(d>diasDelMes[m-1])
        return false;
    if(m==2 && d==29 && !esBisiesto(a))
        return false;
    return true;
}

bool esBisiesto(int a){
    if ((a%4==0) || (a%400==0) && (a%100!=0))
        return true;
    else
        return false;
}
/////////////////////////////// SOBRECARGA OPERADOR = /////////////////////////
Fecha & Fecha::operator =(const Fecha f){
    if(this != &f){
        dia=f.dia;
        mes=f.mes;
        anio=f.anio;
    }
    return (*this);
}
