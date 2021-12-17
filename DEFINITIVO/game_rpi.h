#ifndef GAME_RPI
#define GAME_RPI

#include "queue.h"
#include "bitmap_rpi.h"
#include "global.h"
#include <time.h>

struct{
    char nombre[L_MAX];
    int dificultad;
    int niv_actual;
    int agua;
    int posicion_sur;
    int posicion_oeste;
    uint16_t vidas;
    uint16_t ranas;
    uint16_t jugador_1;
    uint16_t jugador_2;
    uint16_t tiempo_bits;
    uint64_t puntos;
    uint64_t max_puntos;
    clock_t inicio;
    clock_t tiempo;
    clock_t tiempo_limite;
    Matriz mapa;
}jugador;

clock_t frac, acc;

void reiniciarNivel();
void moverAdelante();
void moverAtras();
void moverIzda();
void moverDcha();
void respawn();
void perderVidaChoque();
void perderVidaAgua();
void perderVidaTimeout();
void llegada();
void inicializarJugador();

#endif