#include "game.h"

#include "queue.h"
#include "bitmap.h"
#include "global.h"
#include "display.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define POS_AUTOS 4

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
	uint32_t carril[5];
    uint64_t puntos;
    uint64_t max_puntos;
    clock_t tiempo_inicial;
	clock_t tiempo;
    clock_t tiempo_limite;
    Matriz mapa;
}jugador;

clock_t frac, acc;

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
	jugador.vidas = 5;
}

void decrementarVida(){
	jugador.vidas--;
}

int refresco_autos = 0;

void refrescar(){
	refrescarJugador();
	if(refresco_autos)
		refrescarAutos();
	refresco_autos = ~refresco_autos;
}

void refrescarJugador(){
	uint16_t tmp = jugador.jugador_1;
	jugador.jugador_1 = jugador.jugador_2;
	jugador.jugador_2 = tmp;
}

void refrescarAutos(){
	int i;
	for(i=0; i<5; i++){
		jugador.carril[i] << 1;
        if(jugador.agua){
            if(!(jugador.carril[i] & 0b11111111) && !(rand() % 10))
                jugador.carril[i] |= 0b11;
            else if(!(jugador.carril[i] & 0b1111111111) && !(rand() % 20))
                jugador.carril[i] |= 0b1111;
        }
        else{
            if(!(jugador.carril[i] & 0b111111) && !(rand() % 10))
            jugador.carril[i] |= 0b11;
            else if(!(jugador.carril[i] & 0b11111111) && !(rand() % 20))
                jugador.carril[i] |= 0b1111;
        }
		uint16_t medio_carril = jugador.carril[i] >> 16;
        jugador.mapa[POS_AUTOS+2*i] = medio_carril;
        jugador.mapa[POS_AUTOS+2*i+1] = medio_carril;
	}

}

void setTiempoInicial(clock_t tiempo){
	jugador.tiempo_inicial = tiempo;
}

void setTiempoLimite(clock_t limite){
	jugador.tiempo_limite = limite;
}

void setTiempo(clock_t tiempo){
	jugador.tiempo = tiempo;
	if(jugador.tiempo > acc){
		acc += frac;
		jugador.tiempo_bits >>= 1;
	}

}

void setDificultad(int dificultad){
	jugador.dificultad = dificultad;
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

int getNivel(){
	return jugador.niv_actual;
}

int getAgua(){
	return jugador.agua;
}

clock_t getTiempoInicial(){
	return jugador.tiempo_inicial;
}

clock_t getTiempoLimite(clock_t limite){
	return jugador.tiempo_limite;
}

int getDificultad(){
	return jugador.dificultad;
}

void reiniciarNivel(){
	jugador.ranas = 0b1001001001001001;
	jugador.tiempo_limite = 60*CLOCKS_PER_SEC*(1-0.05*(jugador.dificultad-FACIL));
	frac = jugador.tiempo_limite / 16;
	acc = frac;
	jugador.tiempo_bits = 0b1111111111111111;
	jugador.tiempo_inicial = 0;
	jugador.agua = 0;
	respawn();
}

void respawn(){
	if(jugador.agua){
		jugador.mapa[2] = jugador.ranas;
		jugador.mapa[3] = jugador.ranas;
	}
	else{
    	jugador.jugador_1 = 0b0000000010000000;
    	jugador.jugador_2 = 0b0000000100000000;
		jugador.mapa[2] = 0;
		jugador.mapa[3] = 0;
	}
	jugador.posicion_sur = CANT_FILAS-1;
	jugador.posicion_oeste = 7;
    int i, j;

	for(i=0; i<5; i++){
		jugador.carril[i] = 0;
		int max = 2*CANT_COLUMNAS;
		for(j=0; j<CANT_COLUMNAS;){
			if(rand() & 1){
				if(jugador.agua){
					if(!(rand()%2)){
						jugador.carril[i] |= 0b111111 << j;
						j += 8;
					}
				}
				else if(!(rand()%10)){
					jugador.carril[i] |= 0b11 << j;
					j += 4;
				}
				else if(!(rand()%20)){
					jugador.carril[i] |= 0b1111 << j;
					j += 6;
				}
			}
			else{
				j += 2; //dejo 2 espacios
			}
			if (jugador.agua)
				jugador.carril[i] = ~jugador.carril[i];
			jugador.mapa[POS_AUTOS+2*i] = jugador.carril[i];
			jugador.mapa[POS_AUTOS+2*i+1] = jugador.carril[i];
		}
	}
}

void moverAdelante(){
	if(jugador.posicion_sur > 3)
		jugador.posicion_sur--;
    if(jugador.posicion_sur == 3){
        if(!jugador.agua){
		jugador.agua = 1;
		respawn();
		}
		else{
			//printf("Agregando rana\n");
			jugador.ranas |= jugador.jugador_1 | jugador.jugador_2;
			//printf("%d\n", jugador.ranas);
			if(jugador.ranas == 0b1111111111111111){
            	queue_insert(META);
			}
			else{
				jugador.agua = 0;
				respawn();
			}
	    }
    }
}

void moverAtras(){
	if(jugador.posicion_sur < 15)
		jugador.posicion_sur++;
}

void moverIzda(){
	if(jugador.posicion_oeste > 0){
		jugador.posicion_oeste--;
		jugador.jugador_1 <<= 1;
		jugador.jugador_2 <<= 1;
	}
}

void moverDcha(){
	if(jugador.posicion_oeste < 14){
		jugador.posicion_oeste++;
		jugador.jugador_1 >>= 1;
		jugador.jugador_2 >>= 1;
	}
}

void perderVidaChoque(){
	//ruido1
	jugador.vidas <<= 1;
	jugador.tiempo_inicial = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaAgua(){
	//ruido2
	jugador.vidas <<= 1;
	jugador.tiempo_inicial = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaTimeout(){
	//sin ruido?
	jugador.vidas <<= 1;
	jugador.tiempo_inicial = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void llegada(){
	

}

void inicializarJuego()
{
    jugador.puntos = 0;
	jugador.niv_actual = 1;
	jugador.vidas = 0b1111100000000000;
}

void actualizarInterfaz(){
	Matriz m;
	copiarMatriz(m, jugador.mapa);
    m[0] = jugador.vidas;
    m[1] = jugador.tiempo_bits;
    m[(jugador.posicion_sur)-1] |= jugador.jugador_1;
    m[jugador.posicion_sur] |= jugador.jugador_2;
    escribirMatrizDisplay(m);
    
    if((jugador.jugador_1 & jugador.mapa[jugador.posicion_sur-1]) | (jugador.jugador_2 & jugador.mapa[jugador.posicion_sur]))
        queue_insert(jugador.agua? AGUA : CHOCAR);
}

void subirNivel(){
	jugador.niv_actual++;
}

void imprimirMapa(){
	printMatriz(jugador.mapa);
}
