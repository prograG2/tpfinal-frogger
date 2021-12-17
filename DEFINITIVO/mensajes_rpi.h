#ifndef MENSAJES_RPI
#define MENSAJES_RPI

#include "bitmap_rpi.h"
#include "global.h"
#include <stdint.h>

#define MOVER_TEXTO 1
#define NO_MOVER_TEXTO 0
#define TAM_RENGLON 5
#define INDEX_ESPACIO 26
#define CANT_SIMBOLOS 27
#define NO_REPETIR 0
#define REPETIR 1
#define CERO_INDEX 27
#define FULL_INDEX 37

typedef uint16_t Renglon[TAM_RENGLON];

int longitudes[] = {3,3,3,3,3,3,3,3,1,3,3,3,5,4,3,3,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5}; //sin contar Ñ (+ espacio + numeros + FULL)

Renglon char_index[] = {{0x4000, 0xA000, 0xE000, 0xA000, 0xA000}, //A
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
                            {0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //espacio
                            {0x4000, 0xA000, 0xA000, 0xA000, 0x4000}, //0
                            {0x4000, 0xC000, 0x4000, 0x4000, 0xE000},
                            {0x4000, 0xA000, 0x2000, 0x4000, 0xE000},
                            {0xC000, 0x2000, 0x4000, 0x2000, 0xC000},
                            {0xA000, 0xA000, 0xE000, 0x2000, 0x2000},
                            {0xE000, 0x8000, 0xC000, 0x2000, 0xC000},
                            {0x4000, 0x8000, 0xC000, 0xA000, 0x8000},
                            {0xE000, 0x2000, 0x2000, 0x4000, 0x4000},
                            {0x4000, 0xA000, 0x4000, 0xA000, 0x4000},
                            {0x4000, 0xA000, 0x6000, 0x2000, 0x4000}, //9
                            {0xF800, 0xF800, 0xF800, 0xF800, 0xF800}}; //TODO (FULL)

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

void uintARenglon(unsigned int n, Renglon r); //copia un número a renglon hasta que se acabe el número o el renglon (lo 1 q ocurra)

void reemplazarLetra(Renglon r, char c, int j);

mensaje_t mensaje(char* msj, int pos);

void moverMensaje(mensaje_t* msj, int repetir);

#endif