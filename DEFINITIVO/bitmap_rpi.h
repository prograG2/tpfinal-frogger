#ifndef BITMAP_RPI
#define BITMAP_RPI

#include "global.h"
#include <stdint.h>

typedef uint16_t Matriz[CANT_FILAS];

void printMatriz(Matriz a);

void limpiarMatriz(Matriz a);

void copiarMatriz(Matriz destino, Matriz desde);

void matrizAnd(Matriz a, Matriz b);

void matrizOr(Matriz a, Matriz b);

void matrizNot(Matriz a);

#endif