#include <stdint.h>
#include <stdio.h>
#include "disdrv.h"

#define CANT_FILAS 16
#define CANT_COLUMNAS 16

typedef uint16_t Matriz[CANT_FILAS];


const int longitudes[] = {3,3,3,3,3,3,3,3,1,3,3,3,5,4,3,3,3,3,3,3,3,3,5,3,3,3,3}; //sin contar Ñ (+ espacio)

void printMatriz(Matriz a){
    for(int i=0; i<CANT_FILAS; i++, putchar('\n'))
        for(int j=0; j<CANT_FILAS; j++)
            putchar((a[i] & (0b1000000000000000 >> j)) ? '1' : '.'); 
    
    putchar('\n');
}

void matrizAnd(Matriz a, Matriz b){
    for(int i=0; i<CANT_FILAS; i++)
        a[i] &= b[i];
}

void matrizOr(Matriz a, Matriz b){
    for(int i=0; i< CANT_FILAS; i++)
        a[i] |= b[i];
}

void actualizarDisplay(Matriz a){
    for(int i = DISP_MIN; i <= (DISP_MAX_Y); i++)
        for(int j = DISP_MIN; j <= (DISP_MAX_X) ; j++)
            disp_write((dcoord_t){j, i}, a[i] & (0x8000 >> j));

    disp_update();
}