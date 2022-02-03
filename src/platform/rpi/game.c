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
#include "../../sound.h"
#include "../../queue.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define POS_AUTOS_INICIO 4
#define POS_AUTOS_FIN 13
#define CANT_CARRILES 5


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static struct{
    char nombre[L_MAX];
    int dificultad;
    int niv_actual;
    int posicion_sur;
    int posicion_oeste;
	int timeout_ref;
	int timeout_cnt;
    uint16_t vidas;
    uint16_t ranas;
    uint16_t jugador_1;
    uint16_t jugador_2;
    uint16_t tiempo_bits;
    uint64_t puntos;
    uint64_t max_puntos;
	bool jugando;
	bool agua;
	bool refresco;
	bool timeout;
    clock_t tiempo;
	clock_t tiempo_referencia;
	union
	{
		uint32_t completo;
		struct{
			uint16_t derecho;
			uint16_t izquierdo;
		};
	}carril[CANT_CARRILES];
	matriz_t mapa;
} jugador;


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

extern matriz_t disp_matriz;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void reiniciarTimer();


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_t ttiempo;

static int frac, acc;

static void* threadTiempo(void* ptr);


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

void limpiarMapa(){
	for(int i=0; i< CANT_CARRILES; i++)
		jugador.carril[i].completo = 0;
	limpiarMatriz(jugador.mapa);
}

void moverCarrriles(int x){
	for(int i=0; i<5; i++)
		jugador.carril[i].completo <<= x;
}

void spawnearAutos(){
	int i;
		for(i=0; i<5; i++){
        	if(jugador.agua){
            	if(!(jugador.carril[i].completo & 0b1111111111) && !(rand() % 10))
                	jugador.carril[i].completo |= 0b111111;
            	else if(!(jugador.carril[i].completo & 0b111111111111) && !(rand() % 20))
                	jugador.carril[i].completo |= 0b11111111;
    		}
        	else{
            	if(!(jugador.carril[i].completo & 0b111111) && !(rand() % 10))
            		jugador.carril[i].completo |= 0b11;
            	else if(!(jugador.carril[i].completo & 0b11111111) && !(rand() % 20))
                	jugador.carril[i].completo |= 0b1111;
        	}
		}
}

void actualizarMapa(){
	if(jugador.agua){
		disp_matriz[2] = jugador.ranas;
		disp_matriz[3] = jugador.ranas;
	}
	else{
		disp_matriz[2] = 0;
		disp_matriz[3] = 0;
	}
	for(int i=0; i<5; i++){
		jugador.mapa[POS_AUTOS_INICIO+2*i] = jugador.carril[i].izquierdo;
		jugador.mapa[POS_AUTOS_INICIO+2*i+1] = jugador.carril[i].izquierdo;
	}
}

void refrescar(){
	static bool refresco_autos = 0;

	uint16_t tmp = jugador.jugador_1;
	jugador.jugador_1 = jugador.jugador_2;
	jugador.jugador_2 = tmp;

	if(refresco_autos){
		moverCarrriles(1);
		spawnearAutos();
	}
	
	refresco_autos = !refresco_autos;
	jugador.refresco = false;
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
	reiniciarTimer();
	jugador.agua = false;
	respawn();
	reanudarJuego();
}

void respawn(){
	jugador.posicion_sur = CANT_FILAS-1;

	limpiarMapa();

	for(int i = 0; i < 10 ; i++){
		moverCarrriles(4);
		spawnearAutos();
	}

	actualizarMapa();
}

void moverAdelante(){
	if(jugador.posicion_sur > 3)
		jugador.posicion_sur--;
    if(jugador.posicion_sur == 3){
        if(!jugador.agua){
		jugador.agua = true;
		respawn();
		}
		else{
			//printf("Agregando rana\n");
			jugador.ranas |= jugador.jugador_1 | jugador.jugador_2;
			//printf("%d\n", jugador.ranas);
			if(jugador.ranas == 0b1111111111111111){
				jugador.timeout = true;
				jugador.niv_actual++;
            	reproducirEfecto(EFECTO_NIVEL_COMPLETO);
				reiniciarNivel();
			}
			else{
				jugador.agua = false;
				respawn();
			}
	    }
    }
}

void moverAtras(){
	if(jugador.posicion_sur < 15){
		jugador.posicion_sur++;
		
	}
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


void perderVida(){
	jugador.agua && !jugador.timeout ? reproducirEfecto(EFECTO_AHOGADO) : reproducirEfecto(EFECTO_IMPACTO);
	jugador.agua = false;
	jugador.vidas <<= 1;
	if(!jugador.vidas)
		queueInsertar(GAME_OVER);
	else
		respawn();
	
	reiniciarTimer();
}

void inicializarJuego()
{
    jugador.puntos = 0;
	jugador.niv_actual = 1;
	jugador.vidas = 0b1111100000000000;
}

void reiniciarTimer(){
	jugador.tiempo = 0;
	jugador.tiempo_bits = 0b1111111111111111;
	jugador.tiempo_referencia = 0;
	jugador.timeout_cnt = 0;
	jugador.timeout_ref = 2*60*(1-0.05*(jugador.dificultad));
	frac = jugador.timeout_ref / 16;
	acc = frac;
	jugador.timeout = false;
}

void pausarJuego(){
	jugador.jugando = false;
	pthread_join(ttiempo, NULL);
}

void actualizarInterfaz(){
	actualizarMapa();
	copiarMatriz(disp_matriz, jugador.mapa);
    disp_matriz[0] = jugador.vidas;
    disp_matriz[1] = jugador.tiempo_bits;

    disp_matriz[(jugador.posicion_sur)-1] |= jugador.jugador_1;
    disp_matriz[jugador.posicion_sur] |= jugador.jugador_2;

	actualizarDisplay();

	if((jugador.mapa[(jugador.posicion_sur)-1]) & jugador.jugador_1 || (jugador.mapa[(jugador.posicion_sur)]) & jugador.jugador_2  || jugador.timeout)
		perderVida();
		
}

void reanudarJuego(void)
{
	jugador.jugando = true;
	pthread_create(&ttiempo, NULL, threadTiempo, NULL);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void* threadTiempo(void* ptr){
	clock_t ref = clock() - jugador.tiempo_referencia;
	while(jugador.jugando){
		if(!(jugador.timeout)){
			jugador.tiempo = clock() - ref;
			if(jugador.tiempo >= SLEEP_CLOCKS){
				jugador.tiempo = 0;
				jugador.refresco = true;
				jugador.timeout = ++(jugador.timeout_cnt)  >= jugador.timeout_ref;
				if(jugador.timeout_cnt >= acc){
					acc += frac;
					jugador.tiempo_bits >>= 1;
				}
				jugador.tiempo_referencia = 0;
				ref = clock();
			}
		}
		else{
			ref = clock() - jugador.tiempo_referencia;
		}
	}

	jugador.tiempo_referencia = jugador.tiempo;
	
	return NULL;
}
 