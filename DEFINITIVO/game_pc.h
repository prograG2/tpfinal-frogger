#ifndef GAME_PC
#define GAME_PC

#include "queue.h"
#include "global.h"
#include <time.h>

clock_t frac, acc;

void moverAdelante();
void moverAtras();
void moverIzda();
void moverDcha();
void respawn();
void perderVidaChoque();
void perderVidaAgua();
void perderVidaTimeout();
void llegar();

void inicializarJugador();



#endif