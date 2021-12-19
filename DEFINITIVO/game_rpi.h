#ifndef GAME_RPI
#define GAME_RPI

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
void moverAdelante();
void moverAtras();
void moverIzda();
void moverDcha();
void respawn();
void perderVidaChoque();
void perderVidaAgua();
void perderVidaTimeout();
void llegada();
void subirNivel();
void actualizarInterfaz();
void imprimirMapa();

#endif