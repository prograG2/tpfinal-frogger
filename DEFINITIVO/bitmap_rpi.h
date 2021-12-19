#ifndef BITMAP_RPI
#define BITMAP_RPI

<<<<<<< HEAD
#include <stdint.h>
#include <stdio.h>

#define CANT_FILAS 16
#define CANT_COLUMNAS 16
=======
#include "global.h"
#include <stdint.h>
>>>>>>> rpi funcionando

typedef uint16_t Matriz[CANT_FILAS];

void printMatriz(Matriz a);

void limpiarMatriz(Matriz a);

<<<<<<< HEAD
=======
void copiarMatriz(Matriz destino, Matriz desde);

>>>>>>> rpi funcionando
void matrizAnd(Matriz a, Matriz b);

void matrizOr(Matriz a, Matriz b);

void matrizNot(Matriz a);

#endif