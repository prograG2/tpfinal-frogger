#ifndef GAMEDATA
#define GAMEDATA

#define MAX 64

#include "joystick.c"
#include "mensajes.c"
#include "display.c"
#include <time.h>
#include <stdlib.h>

typedef struct{
    char nombre[MAX];
    int dificultad;
    int niv_actual;
    clock_t tiempo_actual;
    clock_t limite;
    uint64_t puntos;
    uint64_t max_puntos;

}gamedata_t;


gamedata_t nuevoJugador(){
    gamedata_t jugador;
    Renglon nombre_;
    CharARenglon('A', nombre_);
    char nombre[MAX] = {0};
    char c = 'A';
    int i=0;
    int j = longitudes[0] + 1; //a partir de donde voy a escribir la proxima vez
    int resto = CANT_COLUMNAS - j; //cuantos espacios me quedarían si escribo la próxima letra
    nombre[i] = c;
    int joystick;
    Renglon aux;
    while(joystick = leerJoystick() != PRESS){
        switch(joystick){
            case ARRIBA:
                c--;
                if(c < 'A') c='Z';
                CharARenglon(c, aux);
                renglonShiftDer(aux, j);
                renglonOr(nombre_, aux);
            break;

            case ABAJO:
                c++;
                if(c > 'Z') c='A';
                CharARenglon(c, aux);
                renglonShiftDer(aux, j);
                renglonOr(nombre_, aux);
            break;

            case DCHA:
                if(i == MAX) break;
                i++;
                c = 'A';
                nombre[i] = c;
                CharARenglon(c, aux);
                resto = (CANT_COLUMNAS-j) - 5; //Considero el peor caso para calcular el espacio
                if(resto < 0){
                    renglonShiftIzq(nombre_, -resto);
                    j = CANT_COLUMNAS - 6;
                }
                else 
                    j += longitudes[c] + 1;              
                CharARenglon(c, aux);
                renglonShiftDer(aux, j);
                renglonOr(nombre_, aux);
            break;
        }
    }
    mostrarTexto(nombre, 1);
}

#endif