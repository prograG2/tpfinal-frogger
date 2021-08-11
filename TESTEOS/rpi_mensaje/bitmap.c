#include <stdint.h>
#include <stdio.h>
#include "disdrv.h"

#define CANT_FILAS 16
#define CANT_COLUMNAS 16
#define TAM_RENGLON 5

typedef uint16_t Matriz[CANT_FILAS];
typedef uint16_t Renglon[TAM_RENGLON];

const int longitudes[] = {3,3,3,3,3,3,3,3,1,3,3,3,5,4,3,3,3,3,3,3,3,3,5,3,3,3,3}; //sin contar Ñ (+ espacio)
const int char_index[][TAM_RENGLON] = {{0x4000, 0xA000, 0xE000, 0xA000, 0xA000}, //A
                            {0xC000, 0xA000, 0xC000, 0xA000, 0xC000},
                            {0x4000, 0xA000, 0x8000, 0xA000, 0x4000},
                            {0xC000, 0xA000, 0xA000, 0xA000, 0xC000},
                            {0xE000, 0x8000, 0xC000, 0x8000, 0xE000},
                            {0xE000, 0x8000, 0xC000, 0x8000, 0x8000},
                            {0x6000, 0x8000, 0xA000, 0xA000, 0x6000},
                            {0xA000, 0xA000, 0xE000, 0xA000, 0xA000},
                            {0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
                            {0x2000, 0x2000, 0xA000, 0xA000, 0x4000},
                            {0xA000, 0xA000, 0xC000, 0xA000, 0xA000},
                            {0x8000, 0x8000, 0x8000, 0x8000, 0xE000},
                            {0x8800, 0xD800, 0xA800, 0xA800, 0x8800},
                            {0x9000, 0xD000, 0xB000, 0x9000, 0x9000},
                            {0x4000, 0xA000, 0xA000, 0xA000, 0x4000},
                            {0xC000, 0xA000, 0xA000, 0xC000, 0x8000},
                            {0x4000, 0xA000, 0xA000, 0xA000, 0x6000},
                            {0xC000, 0xA000, 0xC000, 0xA000, 0xA000},
                            {0x6000, 0x8000, 0x4000, 0x2000, 0xC000},
                            {0xE000, 0x4000, 0x4000, 0x4000, 0x4000},
                            {0xA000, 0xA000, 0xA000, 0xA000, 0x4000},
                            {0xA000, 0xA000, 0xA000, 0x4000, 0x4000},
                            {0x8800, 0xA800, 0xA800, 0x5000, 0x5000},
                            {0xA000, 0xA000, 0x4000, 0xA000, 0xA000},
                            {0xA000, 0xA000, 0x4000, 0x4000, 0x4000},
                            {0xE000, 0x2000, 0x4000, 0x8000, 0xE000}, //Z
                            {0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; //espacio


void printMatriz(Matriz a){
    for(int i=0; i<CANT_FILAS; i++, putchar('\n'))
        for(int j=0; j<CANT_FILAS; j++)
            putchar((a[i] & (0b1000000000000000 >> j)) ? '1' : '.'); 
    
    putchar('\n');
}

void printRenglon(Renglon r){
    for(int i=0; i<TAM_RENGLON; i++, putchar('\n'))
        for(int j=0; j<CANT_FILAS; j++)
            putchar((r[i] & (0b1000000000000000 >> j)) ? '1' : '.'); 
    
    putchar('\n');
}

void printRenglonDoble(Renglon r1, Renglon r2){
    for(int i=0; i<TAM_RENGLON; i++, putchar('\n')){
        for(int j=0; j<CANT_FILAS; j++)
            putchar((r1[i] & (0b1000000000000000 >> j)) ? '1' : '.');
        putchar('|');
        for(int j=0; j<CANT_FILAS; j++)
            putchar((r2[i] & (0b1000000000000000 >> j)) ? '1' : '.');
    }

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

void CharARenglon(char c, Renglon r){
    if(!c) c = ' ';
    int indice = c == ' ' ? 26 : c - 'A';
    for(int i=0; i<TAM_RENGLON; i++)
        r[i] = char_index[indice][i];
}

void renglonShiftDer(Renglon r, uint16_t s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] >>= s;
}

void renglonShiftIzq(Renglon r, uint16_t s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] <<= s;
}

void renglonOr(Renglon r, Renglon s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] |= s[i];
}

void escribirRenglon(Matriz m, Renglon r, int fila){
    for(int i=0; i<TAM_RENGLON; i++)
        m[fila+i] = r[i];
}

void renglonDobleShiftDer(Renglon r1, Renglon r2, unsigned int s){
    for (int i=0; i<TAM_RENGLON; i++){
        r2[i] >>= s;
        r2[i] |= (r1[i] & ((1 << s) - 1)) << (CANT_COLUMNAS - s); //pego los últimos bits de r1
        r1[i] >>= s;
    }
}

void renglonDobleShiftIzq(Renglon r1, Renglon r2, unsigned int s){
    for (int i=0; i<TAM_RENGLON; i++){
        r1[i] <<= s;
        r1[i] |= (r2[i] & ((uint16_t)(0b11111111111111110000000000000000 >> s))) >> (CANT_COLUMNAS-s);//pego los últimos bits de r2
        r2[i] <<= s;
    }
}

int renglonBool(Renglon r){
    for (int i=0; i<TAM_RENGLON; i++)
        if(r[i]) return 1;
    return 0;
}