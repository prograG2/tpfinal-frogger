#ifndef GAMEDATA
#define GAMEDATA

#include <bitmap.h>
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
    uint64_t puntos;
    uint64_t max_puntos;
    clock_t inicio;
    clock_t tiempo;
    clock_t tiempo_limite;
    Matriz mapa;
}jugador;

void posicionInicial();

#endif