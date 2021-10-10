#ifndef GAMEDATA
#define GAMEDATA

#define MAX 64

#include "joystick.c"
#include "mensajes.c"
#include "display.c"
#include <time.h>
#include <stdlib.h>

extern Renglon char_index[];

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
    escribirRenglonDisplay(nombre_, POS_MSJ2);
    char nombre[MAX] = {0};
    char c = 'A';
    int i=0;
    int j = 0; //a partir de donde voy a escribir la proxima vez
    int resto = CANT_COLUMNAS - j; //cuantos espacios me quedarían si escribo la próxima letra
    nombre[i] = c;
    int joystick = 0; //si no se inicializa se devuelve 1 en leerJoystick, why?
    Renglon aux, full;
    while((joystick = leerJoystick()) != PRESS){
        switch(joystick){
            case ARRIBA:
                borrarRenglon(full);
                copiarRenglon(char_index[FULL_INDEX], full);
                renglonShiftDer(full, j);
                renglonNot(full);
                renglonAnd(nombre_, full);
                c--;
                if(c < 'A') c='Z';
                nombre[i] = c;
                CharARenglon(c, aux);
                renglonShiftDer(aux, j);
                renglonOr(nombre_, aux);
                escribirRenglonDisplay(nombre_, POS_MSJ2);
            break;

            case ABAJO:
                borrarRenglon(full);
                copiarRenglon(char_index[FULL_INDEX], full);
                renglonShiftDer(full, j);
                renglonNot(full);
                renglonAnd(nombre_, full);
                c++;
                if(c > 'Z') c='A';
                nombre[i] = c;
                CharARenglon(c, aux);
                renglonShiftDer(aux, j);
                renglonOr(nombre_, aux);
                escribirRenglonDisplay(nombre_, POS_MSJ2);
            break;

            case DCHA:
                if(i == MAX) break;
                i++;
                c = 'A';
                nombre[i] = c;
                CharARenglon(c, aux);
                resto = (CANT_COLUMNAS-j) - 6; //Considero el peor caso para calcular el espacio
                if(resto < 0){
                    renglonShiftIzq(nombre_, -resto);
                    j = CANT_COLUMNAS - 6;
                }
                else 
                    j += longitudes[c-'A'] + 1;              
                CharARenglon(c, aux);
                renglonShiftDer(aux, j);
                renglonOr(nombre_, aux);
                escribirRenglonDisplay(nombre_, POS_MSJ2);
            break;
        }
    }
    mostrarTexto(nombre, 1);
    return jugador;
}

#endif