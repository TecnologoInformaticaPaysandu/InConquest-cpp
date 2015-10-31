/* 
 * File:   main.cpp
 * Author: Matias
 *
 * Created on 17 de mayo de 2012, 12:22
 */

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdexcept>
#include "Controladores/ControladorUnidad.h"
#include "Controladores/ControladorMapa.h"
#include "Controladores/ControladorJugador.h"
#include "Controladores/ControladorPartida.h"
#include "Clases/Eliminacion.h"
#include "Clases/Dominacion.h"
#include "Clases/Fecha.h"
#include <time.h>

using namespace std;

void Menu(){
    system("cls");
    cout<<"*******************************************************************************"<<endl;
    cout<<"*                              InCONQUEST 1.0                                 *"<<endl;
    cout<<"*******************************************************************************"<<endl<<endl;
    cout<<"1) REGISTRAR USUARIO"<<endl;
    cout<<"2) VER PERFIL DE USUARIO"<<endl;
    cout<<"3) CREAR MAPA"<<endl;
    cout<<"4) VER MAPA"<<endl;
    cout<<"5) ELIMINAR MAPA"<<endl;
    cout<<"6) CREAR TIPO DE UNIDAD"<<endl;
    cout<<"7) CREAR PARTIDA"<<endl;
    cout<<"8) VER DATOS DE PARTIDA"<<endl;
    cout<<"9) JUGAR TURNO DE PARTIDA"<<endl;
    cout<<"10) CARGAR DATOS DE PRUEBA"<<endl<<endl;
    cout<<"0) SALIR"<<endl;
}

void registrarUsuario(ControladorJugador * cj){
    char nom[30]={'\0'}, email[40]={'\0'}, nacionalidad[30]={'\0'}, sexo[2];
    int dia, mes, anio;
    
    system("cls");
    cout<<"***************************** REGISTRAR USUSRIO *******************************"<<endl<<endl;
    cout<<"Ingrese Nombre: ";
    cin>>nom;
    cout<<"Ingrese e-mail: ";
    cin>>email;
    cout<<"Ingrese nacionalidad: ";
    cin>>nacionalidad;
    cout<<"Ingrese sexo[m/f]: ";
    cin>>sexo;
    
    do{
        system("cls");
        cout<<"Ingrese fecha de nacimiento"<<endl;
        cout<<"Dia: ";
        cin>>dia;
        cout<<"Mes: ";
        cin>>mes;
        cout<<"Anio: ";
        cin>>anio;
    } while(!esCorrecta(dia,mes,anio));
    
    cj->crearJugador(email,nom,nacionalidad,Fecha(dia,mes,anio),sexo);
    cout<<endl<<"El registro se ha efectuado exitosamente"<<endl;
    system("pause");
}

void verPerfilUsusrio(ControladorJugador * cj){
    char email[40]={'\0'};
    system("cls");
    cout<<"**************************** VER PERFIL DE USUARIO ****************************"<<endl<<endl;
    cj->listarJugadores();
    
    cout<<"Seleccione jugador indicando su e-mail: ";
    cin>>email;
    try{
        cj->verPerfil(email);
        cout<<endl;
    }
    catch(invalid_argument &e){
        cout<<endl<<e.what()<<endl;
    }
    system("pause");
}

void crearMapa(ControladorMapa * cm){
    int cant;
    char nom_mapa[20]={'\0'}, nom_terr[20]={'\0'}, terr1[20]={'\0'}, terr2[20]={'\0'}, continuar;
    
    system("cls");
    cout<<"********************************* CREAR MAPA **********************************"<<endl<<endl;
    cout<<"Nombre de Mapa: ";
    cin>>nom_mapa;
    cout<<"Ingrese cantidad de territorios: ";
    cin>>cant;
    Mapa * m=cm->crearMapa(nom_mapa);
    
    for (int i=0; i<cant; i++){
        cout<<"Nombre de territorio "<<i+1<<" : ";
        cin>>nom_terr;
        m->agregarTerritorio(nom_terr);
    }
    
    do{
        system("cls");
        cout<<"Ingrese los nombres de 2 territorios para indicar que son adyacentes"<<endl;
        cout<<"\nPrimer territorio: ";
        cin>>terr1;                    
        cout<<"\nSegundo territorio 2: ";
        cin>>terr2;
        try{
            m->agregarAdyacencias(terr1, terr2);
        }
        catch(invalid_argument &e){
            cout<<endl<<e.what()<<endl;
        }
        
        cout<<"\nDesea continuar? [s/n]: ";
        cin>>continuar;
        
    }while(continuar == 's' || continuar == 'S');
    system("pause");
}

void verMapa(ControladorMapa * cm){
    char nom_mapa[20]={'\0'};
    system("cls");
    cout<<"********************************* VER MAPA ***********************************"<<endl<<endl;
    
    cm->listarMapas();
    
    cout<<endl<<"Ingrese el nombre del mapa: ";
    cin>>nom_mapa;
    try{
        Mapa * m=cm->buscarMapa(nom_mapa);
        cout<<endl;
        m->mostrarInformacion();
        cout<<endl;
    }
    catch(invalid_argument &e){
        cout<<endl<<e.what()<<endl;
    }
    system("pause");
}

void eliminarMapa(ControladorMapa * cm){
    char nom_mapa[20]={'\0'};
    system("cls");
    cout<<"******************************* ELIMINAR MAPA ********************************"<<endl<<endl;
    cout<<"Ingrese el nombre del mapa: ";
    cin>>nom_mapa;
    try{
       cm->eliminarMapa(nom_mapa); 
    }
    catch(invalid_argument &e){
        cout<<endl<<e.what()<<endl;
    }
    system("pause");
}

void crearTipoUnidad(ControladorUnidad * cu){
    system("cls");
    char tipo[20]={'\0'};
    int ataq, def, costo;
    cout<<"***************************** CREAR TIPO DE UNIDAD ****************************"<<endl<<endl;
    cout<<"Ingrese el nombre: ";
    cin>>tipo;
    cout<<"Ingrese puntos de ataque: ";
    cin>>ataq;
    cout<<"Ingrese puntos de defensa: ";
    cin>>def;
    cout<<"Ingrese costo: ";
    cin>>costo;
    cu->crearTipoUnidad(tipo,ataq,def,costo);
    system("pause");
}

void crearPartida(ControladorPartida *cp, ControladorJugador *cj, ControladorMapa *cm, ControladorUnidad *cu){
    char nombre[20]={'\0'}, tipoU[20]={'\0'}, mapa[20]={'\0'};
    char email[40]={'\0'}, terr[20]={'\0'}, id_unidad[10]={'\0'}, opc;
    int cant_turnos=0;
    bool tiene_limite=false;
    
    time_t t;
    time(&t);
    struct tm* f = localtime(&t);
    
    system("cls");
    cout<<"******************************* CREA PARTIDA *********************************"<<endl<<endl;
    cout<<"Ingrese el nombre: ";
    cin>>nombre;
    Mapa *m;
    do{
        cout<<"Nombre del mapa a utilizar: ";
        cin>>mapa;
        try{
            m=cm->buscarMapa(mapa);
        }
        catch(invalid_argument &e){
            m=NULL;
            cout<<endl<<e.what()<<endl;
        }  
    }while(!m);
    
    cout<<"Tiene limite de turnos?[s/n]: ";
    cin>>opc;
    if(opc=='s' || opc=='S'){
        tiene_limite=true;
        cout<<"Cantidad de turnos: ";
        cin>>cant_turnos;
    }
    
    Partida *p=cp->crearPartida(nombre,tiene_limite,cant_turnos,Fecha(f->tm_mday,f->tm_mon+1,2012));
    p->setMapa(m);
    cout<<endl<<endl;
    cu->listarTiposUnidades();
    
    /**************************** seleccionar tipos de unidades ***********************/
    
    cout<<"Ingrese el nombre del tipo de unidad para que este disponible en la partida"<<endl;
    do{
        cout<<"Tipo Unidad: ";
        cin>>tipoU;
        try{
            TipoUnidad *tipo=cu->buscarTipoUnidad(tipoU);
            p->agregarTipoUnidad(tipo);
        }
        catch(invalid_argument &e){
            cout<<endl<<e.what()<<endl;
        }
        
        cout<<"Desea ingresar otro tipo?[s/n]: ";
        cin>>opc;
    }while(opc=='s' || opc=='S');
    //cout<<endl<<endl;
    
    /*************************************************************************************/
    system("cls");
    m->listarTerritorios();
    cj->listarJugadores();
    
    /************************* colocar jugadores en los territorios *********************/
    cout<<endl<<endl<<"Ingresar el email del jugador, en que territorio y la unidad inicial"<<endl;
    
    do{
        cout<<"E-mail: ";
        cin>>email;
        cout<<"Territorio: ";
        cin>>terr;
        cout<<"ID unidad: ";
        cin>>id_unidad;
        cout<<"Tipo de unidad: ";
        cin>>tipoU;
        try{
            Jugador *j = cj->buscarJugador(email);
            Territorio * t = m->buscarTerritorio(terr);
            TipoUnidad * tipo = cu->buscarTipoUnidad(tipoU);
            Unidad *u = cu->crearUnidad(id_unidad, tipo);
            
            j->setInfoPartida(0,0);
            p->colocarJugador(j,t,u);
        }
        catch(invalid_argument &e){
            cout<<endl<<e.what()<<endl;
        }
        
        cout<<"Desea ingresar otro jugador? [s/n]: ";
        cin>>opc;
         
    }while(opc=='s' || opc=='S');
        
    /*********************** se cargan los objetivos *****************************/
    system("cls");
    Iterador *it=new Iterador(p->getJugadores()->getPincipal()->getSig());
    Coleccionable *c;
    char obj;
    
    while(it->existeActual()){
        c=it->getActual();
        Jugador *jug=dynamic_cast<Jugador *>(c);
        
        cout<<"Tipo de objetivo para el jugador "<<jug->getNombre()<<endl;
        cout<<"Eliminacion(e) o Dominacion(d): ";
        cin>>obj;
        /************************* objetivo de eliminacion ********************/
        if(obj=='e' || obj=='E'){
            Eliminacion *e = new Eliminacion();
            p->getJugadores()->listar();
            cout<<endl<<"Ingrese el email del jugador a eliminar: ";
            cin>>email;
            try{
                Jugador *jug_eliminar = cj->buscarJugador(email);
                e->setJugador(jug_eliminar);
                p->asignarObjetivo(jug,e);
            }
            catch(invalid_argument &e){
                cout<<endl<<e.what()<<endl;
            }
        }
        /************************ objetivo de dominacion **********************/
        else if(obj=='d' || obj=='D'){
            Dominacion *d=new Dominacion();
            do{
                m->getTerritorios()->listar();
                cout<<endl<<"Ingrese nombre de territorio a conquistar: ";
                cin>>terr;
                try{
                    Territorio *t_dominar = m->buscarTerritorio(terr);
                    d->agregarTerritorio(t_dominar);
                }
                catch(invalid_argument &e){
                    cout<<endl<<e.what()<<endl;
                }
                cout<<endl<<"Desea ingresar oto territorio? [s/n]: ";
                cin>>opc;
                
            }while(opc=='s' || opc=='S');
            p->asignarObjetivo(jug,d);
        }
        it->sig();
    }
    cout<<endl<<"Se creo la Partida correctamente"<<endl;
    system("pause");
}

void verDatosPartida(ControladorPartida *cp){
    char nombre[20];
    system("cls");
    cout<<"*************************** VER DATOS DE PARTIDA *****************************"<<endl<<endl;
    cout<<"Partidas en curso:"<<endl;
    cp->listarPartidasEnCurso();
    cout<<"Seleccione una partida: ";
    cin>>nombre;
    try{
        Partida *p = cp->buscarPartida(nombre);
        p->verInfoPartida();
    }
    catch(invalid_argument &e){
        cout<<endl<<e.what()<<endl;
    }
    system("pause");
}

void jugarTurnoPartida(ControladorPartida *cp, ControladorJugador *cj, ControladorUnidad *cu){
    char nom_partida[20], email[40], tipo[20], terr[25], id[15], opc;
    Coleccionable *c1, *c2;
    system("cls");
    cout<<"*************************** JUGAR TURNO DE PARTIDA ****************************"<<endl<<endl;
    cout<<"Ingrese el nombre de la partida: ";
    cin>>nom_partida;
    cout<<"Ingrese el e-mail del jugador: ";
    cin>>email;
    try{
        Partida *partida = cp->buscarPartida(nom_partida);
        if(partida->getFinalizada())
            throw invalid_argument("Error, la partida seleccionada ya finalizo");
        
        Jugador *jugador = partida->puedeJugar(email);
        /////////////// muestra informacion de partida ////////////////
        partida->verInfoPartida();
        
        cout<<endl<<"********** DETALLES DE OBJETIVO **********"<<endl;
        jugador->getObjetivo()->imprimirDatos();
        cout<<endl<<"Creditos disponibles: "<<jugador->getInfoPartida()->getCreditos()<<endl<<endl;
        cout<<"Desea comprar unidades? [s/n]: ";
        cin>>opc;
        if(opc=='s' || opc=='S'){
            while(opc=='s' || opc=='S'){
                cout<<"Tipo de unidad: ";
                cin>>tipo;
                cout<<"ID unidad: ";
                cin>>id;
                cout<<"Territorio: ";
                cin>>terr;
                c1 = partida->getTiposUndades()->find(tipo);
                c2 = jugador->getTerritorios()->find(terr);
                if(c1==NULL)
                    cout<<"Error, el tipo de unidad no es correcto"<<endl;
                else{
                    if(c2==NULL)
                        cout<<"Error, el territorio no es correcto"<<endl;
                    else{
                        TipoUnidad *tu = dynamic_cast<TipoUnidad *>(c1);
                        if(tu->getCosto()>jugador->getInfoPartida()->getCreditos())
                            cout<<"No tiene creditos suficientes"<<endl;
                        else{
                            Territorio *t = dynamic_cast<Territorio *>(c2);
                            Unidad *uni = cu->crearUnidad(id,tu);
                            t->agregarUnidad(uni);
                            jugador->agregarUnidad(uni);
                            jugador->getInfoPartida()->actualizarCreditos(-tu->getCosto());
                            cout<<"Creditos disponibles: "<<jugador->getInfoPartida()->getCreditos()<<endl;
                        }
                    }
                }
                
                cout<<"Desea comprar otra unidad? [s/n]: ";
                cin>>opc;
            }
        }
        system("cls");
        cout<<"********** MOVER UNIDADES **********"<<endl<<endl;
        
        Iterador *it = new Iterador(jugador->getUnidades()->getPincipal()->getSig());
        Coleccionable *aux, *aux2;
        bool correcto, se_movio_iterador = false;
        
        while(it->existeActual()){
            aux=it->getActual();
            Unidad *unidad_movida = dynamic_cast<Unidad *>(aux);
            cout<<"*** INFO UNIDAD ***"<<endl<<endl;
            cout<<"ID: "<<unidad_movida->getId()<<endl;
            cout<<"Tipo: "<<unidad_movida->getTipo()->getNombre()<<endl;
            cout<<"Vida: "<<unidad_movida->getVida()<<endl;
            
            cout<<"Desea mover esta unidad? [s/n]: ";
            cin>>opc;
            if(opc=='s'||opc=='S'){
                Territorio *t_viejo = unidad_movida->getUbicacion();//territorio de la unidad antes de mover
                int cant_uni_t_viejo, cant_uni_t_nuevo;
                bool fue_ataque;
                
                do{
                    cout<<"Ingrese el territorio al cual moverla: ";
                    cin>>terr;
                    aux2=t_viejo->getAdyacentes()->find(terr);
                    if(aux2==NULL){
                        correcto=false;
                        cout<<"El territorio no es adyacente, intentelo de nuevo"<<endl;
                    }
                    else
                        correcto=true;
                }while(correcto==false);
                /*************************************************************************/
                
                Territorio *t_nuevo=dynamic_cast<Territorio *>(aux2);
                Jugador *jugador_atacado = t_nuevo->getOcupante();
                Unidad *defensora = t_nuevo->getDefensora();
                
                bool murio_defensa = false, murio_ataque = false;
                
                fue_ataque = unidad_movida->mover(t_nuevo);//se mueve la unidad
                
                if(fue_ataque){
                    if(defensora->getVida() == 0)
                        murio_defensa = true;
                    
                    if(unidad_movida->getVida() == 0)
                        murio_ataque = true;
                    
                    cant_uni_t_viejo = t_viejo->getUnidades()->getCantNodos();
                    cant_uni_t_nuevo = t_nuevo->getUnidades()->getCantNodos();
                    /////////////////// murio la unidad defensora ////////////////
                    if(murio_defensa){
                        cu->eliminarUnidad(defensora->getId());
                        t_nuevo->nuevaDefensora();
                        cant_uni_t_nuevo--;
                    }
                    ///////////////// murio unidad atacante /////////////////////
                    if(murio_ataque){
                        it->sig();//muevo el iterador a la unidad siguiente antes de borrarla
                        se_movio_iterador = true;
                        cu->eliminarUnidad(unidad_movida->getId());
                        t_viejo->nuevaDefensora();
                        cant_uni_t_viejo--;
                    }
                    if(cant_uni_t_nuevo == 0){
                        jugador_atacado->getTerritorios()->remove(t_nuevo->getNombre(), false);
                        if(not murio_ataque){
                            t_viejo->getUnidades()->remove(unidad_movida->getId(), false);
                            cant_uni_t_viejo--;
                            t_nuevo->agregarUnidad(unidad_movida);
                            jugador->agregarTerritorio(t_nuevo);
                            t_nuevo->nuevaDefensora();
                            cout<<"Conquisto el territorio "<<t_nuevo->getNombre()<<endl;
                        }
                    }
                    
                    if(cant_uni_t_viejo == 0){
                        jugador->getTerritorios()->remove(t_viejo->getNombre(), false);
                        t_viejo->setOcupante(NULL);
                        cout<<"Perdio el territorio "<<t_viejo->getNombre();
                        cout<<" porque movio la unica unidad que estaba en el"<<endl;
                    }
                    
                    //////////////// si el defensor perdio su ultima unidad ////////////////
                    if(jugador_atacado->getUnidades()->getCantNodos() == 0){
                        jugador_atacado->getInfoPartida()->setQuienLoElimino(jugador);
                        jugador_atacado->getInfoPartida()->setEliminado();
                    }
                    //////////////// si el atacante perdio su ultima unidad ////////////////
                    if(jugador->getUnidades()->getCantNodos() == 0){
                        jugador->getInfoPartida()->setQuienLoElimino(jugador_atacado);
                        jugador->getInfoPartida()->setEliminado();
                    }
                }        
            }
            if(se_movio_iterador == false)
                it->sig();
        }// termina ciclo while
        jugador->getInfoPartida()->actualizarTurno();// indica que el jugador ya termino su turno
        
        if(jugador->cumplioObjetivo(partida)){
            partida->agregarGanador(jugador->getEmail());
            cout<<"Has completado el objetivo"<<endl;
        }
        if(partida->todosJugaronTurno()){
            if(partida->getGanadores()->getCantNodos() > 0 || partida->getCantTurnos() == partida->getTurnoActual()){
                partida->finalizar();
                partida->getMapa()->limpiarMapa();
                cout<<"La partida a finalizado"<<endl;
            }
            else{
                int cred = 10;
                partida->sumarCreditos(cred);
                partida->actualizarTurno();
                cout<<"Se han sumado "<<cred<<" creditos a los jugadores"<<endl;
            }
        }
    }
    catch(invalid_argument &e){
        cout<<endl<<e.what()<<endl;
    }
    system("pause");
}

void cargarDatos(ControladorMapa * cm, ControladorUnidad * cu, ControladorJugador * cj, ControladorPartida *cp){
    
    /******************** se crean los tipos de unidades *************************/
    
    cu->crearTipoUnidad("Helicoptero",7,3,10);
    cu->crearTipoUnidad("Avion",9,6,15);
    cu->crearTipoUnidad("Mercenario",3,3,3);
    cu->crearTipoUnidad("Soldado",4,7,10);
    cu->crearTipoUnidad("Ranger",5,1,5);
    cu->crearTipoUnidad("Artilleria",1,4,5);
    cu->crearTipoUnidad("Kamikaze",6,0,5);
    cu->crearTipoUnidad("Tanque",9,9,20);
    
    /************************* se crean los mapas ********************************/
    
    Mapa * mundo=cm->crearMapa("Mundo");
    //territorios del mapa Mundo
    mundo->agregarTerritorio("America");
    mundo->agregarTerritorio("Asia");
    mundo->agregarTerritorio("Europa");
    mundo->agregarTerritorio("Africa");
    mundo->agregarTerritorio("Oceania");
    //adyacencias del mapa Mundo
    mundo->agregarAdyacencias("Europa", "Asia");
    mundo->agregarAdyacencias("Europa", "Africa");
    mundo->agregarAdyacencias("Asia", "Oceania");
    mundo->agregarAdyacencias("Africa", "Oceania");
    mundo->agregarAdyacencias("Oceania", "America");
    
    Mapa * gran=cm->crearMapa("GranBretania");
    //territorios del mapa Gran Bretaña
    gran->agregarTerritorio("IrlandaNorte");
    gran->agregarTerritorio("Irlanda");
    gran->agregarTerritorio("Escocia");
    gran->agregarTerritorio("Gales");
    gran->agregarTerritorio("Inglaterra");
    //adyacencias del mapa Gran Bretaña
    gran->agregarAdyacencias("IrlandaNorte", "Irlanda");
    gran->agregarAdyacencias("IrlandaNorte", "Escocia");
    gran->agregarAdyacencias("Escocia", "Gales");
    gran->agregarAdyacencias("Escocia", "Inglaterra");
    gran->agregarAdyacencias("Irlanda", "Inglaterra");
    gran->agregarAdyacencias("Gales", "Inglaterra");
    gran->agregarAdyacencias("Irlanda", "Gales");
    
    Mapa * tres=cm->crearMapa("Tres");
    //territorios del mapa Tres
    tres->agregarTerritorio("A");
    tres->agregarTerritorio("B");
    tres->agregarTerritorio("C");
    //adyacencias del mapa Tres
    tres->agregarAdyacencias("A", "B");
    tres->agregarAdyacencias("A", "C");
    tres->agregarAdyacencias("B", "C");
    
    /************************* se crean los jugadores *****************************/
    
    cj->crearJugador("jcarmack@xx.com","John-D.-Carmack","EEUU",Fecha(20,8,1970),"m");
    cj->crearJugador("will@xx.com","Will-Wright","EEUU",Fecha(20,6,1960),"m");
    cj->crearJugador("jromero@xx.com","John-Romero","EEUU",Fecha(28,10,1967),"m");
    cj->crearJugador("sid@xx.com","Sid-Meier","Canada",Fecha(24,2,1954),"m");
    cj->crearJugador("rebecca@xy.com","Rebecca-Ann-Heineman","EEUU",Fecha(30,10,1963),"f");
    cj->crearJugador("cyu@xy.com","Corrinne-Yu","Hong-Kong",Fecha(6,3,1974),"f");
    cj->crearJugador("jraymond@xy.com","Jade-Raymond","Canada",Fecha(28,8,1975),"f");
    cj->crearJugador("saka@xx.com","Hironobu-Sakaguchi","Japon",Fecha(25,11,1962),"m");
    
    
    
    /************************ se cargan los datos de partidas ********************/
    
    //////////////////////////// se crean las partidas //////////////////////////
    Partida *p1 = cp->crearPartida("Conquest",true,4,Fecha(25,5,2011));
    Partida *p2 = cp->crearPartida("Mundo",true,100,Fecha(26,5,2011));
    Partida *p3 = cp->crearPartida("Britania",false,0,Fecha(27,5,2011));
    Partida *p4 = cp->crearPartida("Mundo-4",false,0,Fecha(28,5,2011));
    Partida *p5 = cp->crearPartida("Conquest-5",true,15,Fecha(29,5,2011));
    Partida *p6 = cp->crearPartida("Inglesa",false,0,Fecha(24,5,2011));
    Partida *p7 = cp->crearPartida("Mundo-7",false,0,Fecha(23,5,2011));
    
    /////// Se obtienen los mapas /////////////////////
    Mapa *m1 = cm->buscarMapa("Mundo");
    Mapa *m2 = cm->buscarMapa("GranBretania");
    Mapa *m3 = cm->buscarMapa("Tres");
    
    ///////// se asignan lso mapas a las partidas ///////////
    p1->setMapa(m3);
    p2->setMapa(m1);
    p3->setMapa(m2);
    p4->setMapa(m3);
    p5->setMapa(m3);
    p6->setMapa(m2);
    p7->setMapa(m1);
    
    ////////// se indica las que finalizaron ///////////////////
    p2->finalizar();
    p3->finalizar();
    p4->finalizar();
    p5->finalizar();
    p7->finalizar();
    
    ////////////// se obtienen los jugadores //////////////
    Jugador *j1 = cj->buscarJugador("jcarmack@xx.com");
    Jugador *j2 = cj->buscarJugador("will@xx.com");
    Jugador *j3 = cj->buscarJugador("jromero@xx.com");
    Jugador *j4 = cj->buscarJugador("sid@xx.com");
    Jugador *j5 = cj->buscarJugador("rebecca@xy.com");
    Jugador *j6 = cj->buscarJugador("cyu@xy.com");
    Jugador *j7 = cj->buscarJugador("jraymond@xy.com");
    Jugador *j8 = cj->buscarJugador("saka@xx.com");
    
    /************************** PARTIDAS FINALIZADAS **********************************/
    
    /////////////// se agregan los jugadores y ganadores ////////////////////
    p2->agregarJugador(j2);
    p2->agregarJugador(j3);
    p2->agregarJugador(j4);
    p2->agregarJugador(j5);
    p2->agregarGanador("jromero@xx.com");
    
    p3->agregarJugador(j2);
    p3->agregarJugador(j5);
    p3->agregarJugador(j7);
    p3->agregarGanador("will@xx.com");
    p3->agregarGanador("rebecca@xy.com");
    
    p4->agregarJugador(j3);
    p4->agregarJugador(j5);
    p4->agregarGanador("jromero@xx.com");
    
    p5->agregarJugador(j2);
    p5->agregarJugador(j7);
    p5->agregarGanador("jraymond@xy.com");
    
    p7->agregarJugador(j2);
    p7->agregarJugador(j4);
    p7->agregarJugador(j5);
    p7->agregarGanador("will@xx.com");
    
    //////// se obtienen los territorios /////////////
    Territorio *t_A = m3->buscarTerritorio("A");
    Territorio *t_B = m3->buscarTerritorio("B");
    Territorio *t_Irlanda = m2->buscarTerritorio("Irlanda");
    Territorio *t_Escocia = m2->buscarTerritorio("Escocia");
    Territorio *t_Gales = m2->buscarTerritorio("Gales");
    Territorio *t_IrlandaNorte = m2->buscarTerritorio("IrlandaNorte");
    
    ///////// se obtienen los tipos de unidades /////////////
    TipoUnidad *t1 = cu->buscarTipoUnidad("Helicoptero");
    TipoUnidad *t4 = cu->buscarTipoUnidad("Soldado");
    TipoUnidad *t7 = cu->buscarTipoUnidad("Kamikaze");
    TipoUnidad *t8 = cu->buscarTipoUnidad("Tanque");
    
    /************************** PARTIDAS EN CURSO ***********************************/
    
    ////////////// se agregan los tipos de unidades a las partidas /////////////
    p1->agregarTipoUnidad(t1);
    p1->agregarTipoUnidad(t4);
    p1->agregarTipoUnidad(t7);
    
    p6->agregarTipoUnidad(t1);
    p6->agregarTipoUnidad(t8);
    
     ////////////// se crean las unidades ///////////////////////
    Unidad *u1 = cu->crearUnidad("uni1",t1);
    Unidad *u2 = cu->crearUnidad("uni2",t7);
    Unidad *u3 = cu->crearUnidad("uni3",t1);
    Unidad *u4 = cu->crearUnidad("uni4",t4);
    Unidad *u5 = cu->crearUnidad("uni5",t8);
    
    /////////////////// SE ASIGNAN LOS VALORES DE VIDA //////////////////
    u1->setVida(2);
    u2->setVida(5);
    u3->setVida(5);
    u4->setVida(5);
    u5->setVida(5);
    
    //////////////////// se crean los objetivos //////////////////////////
    Eliminacion *e=new Eliminacion();
    e->setJugador(j1);
    
    Dominacion *d1=new Dominacion();
    d1->agregarTerritorio(t_A);
    d1->agregarTerritorio(t_B);
    
    Dominacion *d2=new Dominacion();
    d2->agregarTerritorio(t_Escocia);
    d2->agregarTerritorio(t_Gales);
    d2->agregarTerritorio(t_Irlanda);
    
    Dominacion *d3=new Dominacion();
    d3->agregarTerritorio(t_IrlandaNorte);
    d3->agregarTerritorio(t_Irlanda);
    d3->agregarTerritorio(t_Escocia);
    
    ///////////////// se asignan los objetivos //////////////////////////
    p1->asignarObjetivo(j1,d1);
    p1->asignarObjetivo(j2,e);
    
    p6->asignarObjetivo(j6,d2);
    p6->asignarObjetivo(j8,d3);
    
    /////////////////// se indica el turno actual //////////////////////////
    p1->setTurnoActual(3);
    p6->setTurnoActual(2);
    
    //////////////// se asigna a los jugador territorios y unidades ///////////////
    p1->colocarJugador(j1,t_A,u1);
    p1->colocarJugador(j2,t_B,u2);
    
    p6->colocarJugador(j6,t_Irlanda,u3);
    t_Irlanda->agregarUnidad(u4);
    j6->agregarTerritorio(t_Irlanda);
    j6->agregarUnidad(u4);
    
    p6->colocarJugador(j8,t_Escocia,u5);
    
    ///////////////// SE CARGA INFORMACION DE JUGADORES EN LA PARTIDA ///////////////
    j1->setInfoPartida(30,3);// tiene 30 creditos y jugo el turno 3
    j2->setInfoPartida(5,2);// tiene 5 creditos y jugo el tueno 2
    
    j6->setInfoPartida(12,1);// tiene 12 creditos y jugo el turno 1
    j8->setInfoPartida(10,1);// tiene 10 creditos y jugo el turno 1
    
    /******************************************************************************/
    
    
    cout<<"Se cargaron los datos de prueba"<<endl<<endl;
    system("pause");
}


int main(int argc, char** argv) {

    int opcion;
    bool salir = false;
    
    ControladorMapa * CM = new ControladorMapa();
    ControladorUnidad * CU = new ControladorUnidad();
    ControladorJugador *CJ=new ControladorJugador();
    ControladorPartida * CP=new ControladorPartida();
    
    do{
        Menu();
        cout<<"\nOpcion: ";
        cin>>opcion;
        
        switch(opcion){
            case 1:{
                ////////////////// REGISTRO DE USUARIO ///////////////
                registrarUsuario(CJ);
            } break;
            case 2:{
                ////////////////// VER PERFIL DE USUARIO /////////////
                verPerfilUsusrio(CJ);
            } break;
            case 3: {
                /////////////////// CREAR MAPA ////////////////////
                crearMapa(CM);
                } break;
            case 4: {
                /////////////////// VER MAPA /////////////////////
                verMapa(CM);
            } break;
            case 5: {
                /////////////////// ELIMINAR MAPA ////////////////
                eliminarMapa(CM);
            } break;
            case 6:{
                /////////////////// CREAR TIPO DE UNIDAD ///////////
                crearTipoUnidad(CU);
            } break;
            case 7:{
                /////////////////// CREAR PARTIDA //////////////////
                crearPartida(CP,CJ,CM,CU);
            } break;
            case 8:{
                ////////////// VER INFO PARTIDA EN CURSO ///////////
                verDatosPartida(CP);
            } break;
            case 9:{
                //////////// JUGAR TURNO DE PARTIDA /////////////////
                jugarTurnoPartida(CP,CJ,CU);
            } break;
            case 10:{
                /////////////////// CARGAR DATOS DE PRUEBA ///////////////////
                cargarDatos(CM,CU,CJ,CP);
            } break;
            case 0: salir = true; break;
            default: {
                cout<<"Opcion incorrecta, ";
                system("pause");
            }break;
        }
    }
    while(!salir);
    return 0;
}

