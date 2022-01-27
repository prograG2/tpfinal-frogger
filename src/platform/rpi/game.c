/**
 * @file game.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../game.h"

#include "bitmap.h"
#include "../../display.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define POS_AUTOS 4


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static struct{
    char nombre[L_MAX];
    int dificultad;
    int niv_actual;
    int agua;
    int posicion_sur;
    int posicion_oeste;
	int timeout_ref;
	int timeout_cnt;
    uint16_t vidas;
    uint16_t ranas;
    uint16_t jugador_1;
    uint16_t jugador_2;
    uint16_t tiempo_bits;
	uint32_t carril[5];
    uint64_t puntos;
    uint64_t max_puntos;
	bool jugando;
	bool refresco;
	bool timeout;
    clock_t tiempo;
    Matriz mapa;
} jugador;


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

extern Matriz disp_matriz;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_t ttiempo;

static int frac, acc;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setNombre(char* nombre){
	strcpy(jugador.nombre, nombre);
}

void setMaxPuntos(uint64_t max){
	jugador.max_puntos = max;
}

void refrescar(){
	static int refresco_autos = 0;

	uint16_t tmp = jugador.jugador_1;
	jugador.jugador_1 = jugador.jugador_2;
	jugador.jugador_2 = tmp;

	if(refresco_autos){
		int i;
	for(i=0; i<5; i++){
		jugador.carril[i] <<= 1;
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
	refresco_autos = ~refresco_autos;
}

bool tiempoRefrescoEntidades(void)
{
	return jugador.refresco;
}

bool tiempoLimite(void)
{
	return jugador.timeout;
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

int getNivel(){
	return jugador.niv_actual;
}

void reiniciarNivel(){
	jugador.ranas = 0b1001001001001001;
	jugador.timeout_cnt = 0;
	jugador.timeout_ref = 2*60*(1-0.05*(jugador.dificultad-FACIL));
	frac = jugador.timeout_ref / 16;
	acc = frac;
	jugador.tiempo = 0;
	jugador.tiempo_bits = 0b1111111111111111;
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
				jugador.jugando = false;
				jugador.niv_actual++;
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
	jugador.tiempo = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaAgua(){
	//ruido2
	jugador.vidas <<= 1;
	jugador.tiempo = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaTimeout(){
	//sin ruido?
	jugador.vidas <<= 1;
	jugador.tiempo = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void inicializarJuego()
{
    jugador.puntos = 0;
	jugador.niv_actual = 1;
	jugador.vidas = 0b1111100000000000;
}

void pausarJuego(){
	jugador.jugando = false;
}

void actualizarInterfaz(){
    disp_matriz[0] = jugador.vidas;
    disp_matriz[1] = jugador.tiempo_bits;
    disp_matriz[(jugador.posicion_sur)-1] |= jugador.jugador_1;
    disp_matriz[jugador.posicion_sur] |= jugador.jugador_2;
    actualizarDisplay();
    
    if((jugador.jugador_1 & jugador.mapa[jugador.posicion_sur-1]) | (jugador.jugador_2 & jugador.mapa[jugador.posicion_sur]))
        queue_insert(jugador.agua? AGUA : CHOCAR);
}

void imprimirMapa(){
	printMatriz(jugador.mapa);
}

void continuandoJuego(void)
{
	jugador.jugando = true;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void thread_tiempo(void* ptr){
	clock_t ref = clock();
	while(jugador.jugando && !(jugador.timeout)){
		jugador.tiempo += clock() - ref;
		if(jugador.tiempo >= SLEEP_CLOCKS){
			jugador.tiempo = 0;
			jugador.refresco = true;
			jugador.timeout = ++(jugador.timeout_cnt)  >= jugador.timeout_ref;
			if(jugador.timeout_cnt >= acc){
				acc += frac;
				jugador.tiempo_bits >>= 1;
			}
		}
	}
	
	return NULL;
}

 