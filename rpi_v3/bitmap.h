#ifndef BITMAP
#define BITMAP

#include <stdint.h>
#include <stdio.h>

#define CANT_FILAS 16
#define CANT_COLUMNAS 16

typedef uint16_t Matriz[CANT_FILAS];

void printMatriz(Matriz a);

void limpiarMatriz(Matriz a);

void matrizAnd(Matriz a, Matriz b);

void matrizOr(Matriz a, Matriz b);

void matrizNot(Matriz a);

#endif