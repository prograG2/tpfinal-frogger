#ifndef GAME_RPI
#define GAME_RPI

<<<<<<< HEAD
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
=======
#include <stdint.h>
#include <time.h>

void setNombre(char* nombre);
void setPuntos(uint64_t puntos);
void setMaxPuntos(uint64_t max);
void setMaxVidas();
void setTiempoInicial(clock_t tiempo);
void setTiempoLimite(clock_t limite);
void setDificultad(int dif);
void setTiempo(clock_t tiempo);

char* getNombre();
uint64_t getPuntos();
uint64_t getMaxPuntos();
int getVidas();
int getNivel();
clock_t getTiempoInicial();
clock_t getTiempoLimite();
int getDificultad();
int getAgua();

void inicializarJuego();
void inicializarNivel();
void reiniciarNivel();
void decrementarVida();
void incrementarPuntos(int);
void refrescarJugador();
void refrescarAutos();
>>>>>>> rpi funcionando
void moverAdelante();
void moverAtras();
void moverIzda();
void moverDcha();
void respawn();
void perderVidaChoque();
void perderVidaAgua();
void perderVidaTimeout();
void llegada();
<<<<<<< HEAD
void inicializarJugador();
=======
void subirNivel();
void actualizarInterfaz();
void imprimirMapa();
>>>>>>> rpi funcionando

#endif