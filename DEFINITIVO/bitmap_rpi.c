#include "bitmap.h"

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
    for(int i=0; i<CANT_FILAS; i++)
        a[i] |= b[i];
}

void matrizNot(Matriz a){
    for(int i=0; i<CANT_FILAS; i++)
        a[i] = ~a[i];
}