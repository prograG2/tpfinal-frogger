#ifndef MENSAJES_RPI
#define MENSAJES_RPI

#include "global.h"
#include <stdint.h>

#define MOVER_TEXTO 1
#define NO_MOVER_TEXTO 0
#define TAM_RENGLON 5
#define NO_REPETIR 0
#define REPETIR 1

typedef uint16_t Renglon[TAM_RENGLON];

typedef struct Mensaje{
    char msj[L_MAX];
    int posicion;
    int index;
    int index_inicio;
    int j_inicio;
    int longitud;
    int mover;
    Renglon renglon;
    Renglon reserva;
    Renglon renglon_inicio;
    Renglon reserva_inicio;
} mensaje_t;

void printRenglon(Renglon r);

void printRenglonDoble(Renglon r1, Renglon r2);

void borrarRenglon(Renglon r);

void renglonShiftDer(Renglon r, uint16_t s);

void renglonShiftIzq(Renglon r, uint16_t s);

void renglonOr(Renglon r, Renglon s);

void renglonAnd(Renglon r, Renglon s);

void renglonNot(Renglon r);

void renglonDobleShiftDer(Renglon r1, Renglon r2, unsigned int s);

void renglonDobleShiftIzq(Renglon r1, Renglon r2, unsigned int s);

void copiarRenglon(Renglon r1, Renglon r2);

int renglonBool(Renglon r);

void CharARenglon(char c, Renglon r);

void uintARenglon(uint16_t n, Renglon r); //copia un número a renglon hasta que se acabe el número o el renglon (lo 1 q ocurra)

void reemplazarLetra(Renglon r, char c, int j);

mensaje_t mensaje(char* msj, int pos);

void moverMensaje(mensaje_t* msj, int repetir);

int getLongitud(char a);

#endif