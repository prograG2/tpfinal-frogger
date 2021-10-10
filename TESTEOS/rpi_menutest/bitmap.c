#ifndef BITMAP
#define BITMAP

#include <stdint.h>
#include <stdio.h>

#define CANT_FILAS 16
#define CANT_COLUMNAS 16

typedef uint16_t Matriz[CANT_FILAS];

void printMatriz(Matriz a){
    for(int i=0; i<CANT_FILAS; i++, putchar('\n'))
        for(int j=0; j<CANT_FILAS; j++)
            putchar((a[i] & (0b1000000000000000 >> j)) ? '1' : '.'); 
    
    putchar('\n');
}

void limpiarMatriz(Matriz a){
    for(int i=0; i<CANT_FILAS; i++)
        a[i] = 0;
}

void matrizAnd(Matriz a, Matriz b){
    for(int i=0; i<CANT_FILAS; i++)
        a[i] &= b[i];
}

void matrizOr(Matriz a, Matriz b){
    for(int i=0; i< CANT_FILAS; i++)
        a[i] |= b[i];
}

#endif