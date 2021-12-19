#ifndef GAME_PC
#define GAME_PC

#include "queue.h"
#include "global.h"
#include <time.h>
<<<<<<< HEAD

clock_t frac, acc;

=======
#include <stdint.h>
#include <string.h>

#define STEP_FRACTION_SIZE 50;

clock_t frac, acc;

void setNombre(char* nombre);
void setPuntos(uint64_t puntos);
void setMaxPuntos(uint64_t max);
void setMaxVidas();
void setTiempoInicial(clock_t tiempo);
void setTiempoLimite(clock_t limite);
void setDificultad(int dif);

char* getNombre();
uint64_t getPuntos();
uint64_t getMaxPuntos();
int getVidas();
clock_t getTiempoInicial();
clock_t getTiempoLimite();
int getNivel();
int getDificultad();

void inicializarJuego();
void reinciarNivel();
void decrementarVida();
void incrementarPuntos(int);
void refrescarJugador();
>>>>>>> rpi funcionando
void moverAdelante();
void moverAtras();
void moverIzda();
void moverDcha();
void respawn();
void perderVidaChoque();
void perderVidaAgua();
void perderVidaTimeout();
void llegar();
<<<<<<< HEAD

void inicializarJugador();
=======
void subirNivel();
>>>>>>> rpi funcionando



#endif