#include "game.h"

struct{
    char nombre[L_MAX];
    int dificultad;
    int niv_actual;
    int agua;
    int x;
    int y;
    uint16_t vidas;
    uint16_t ranas;
    uint16_t tiempo_bits;
    uint64_t puntos;
    uint64_t max_puntos;
    clock_t tiempo_inicial;
    clock_t tiempo;
    clock_t tiempo_limite;
}jugador;

void setNombre(char* nombre){
	strcpy(jugador.nombre, nombre);
}
void setPuntos(uint64_t puntos){
	jugador.puntos = puntos;
}

void setMaxPuntos(uint64_t max){
	jugador.max_puntos = max;
}

void setMaxVidas(){
	jugador.vidas = 0b1111100000000000;
}

void decrementarVida(){
	jugador.vidas--;
}

void refrescarJugador(){
}

void setTiempoInicial(clock_t tiempo){
	jugador.tiempo_inicial = tiempo;
}

void setTiempoLimite(clock_t limite){
	jugador.tiempo_limite = limite;
}

void setDificultad(int dif){
    jugador.dificultad = dif;
}

char* getNombre(){
	return jugador.nombre;
}
uint64_t getPuntos(){
	return jugador.puntos;
}

uint64_t getMaxPuntos(){
	return jugador.max_puntos;
}

int getVidas(){
	return jugador.vidas;
}

clock_t getTiempoInicial(){
	return jugador.tiempo_inicial;
}

clock_t getTiempoLimite(clock_t limite){
	return jugador.tiempo_limite;
}

void reiniciarNivel(){
}

void respawn(){
}

void moverAdelante(){
    jugador.y -=STEP_FRACTION_SIZE;
}

void moverAtras(){
    jugador.y += STEP_FRACTION_SIZE;
}

void moverIzda(){
    jugador.x -= STEP_FRACTION_SIZE;
}

void moverDcha(){
    jugador.x += STEP_FRACTION_SIZE;
}

void perderVidaChoque(){
}

void perderVidaAgua(){
}

void perderVidaTimeout(){
}

void llegada(){
}

void inicializarJugador()
{

}
