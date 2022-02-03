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
#define L_MAX 64


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

union{
	uint32_t completo;
	struct{
		uint16_t derecho;
		uint16_t izquierdo;
	};
}carril[CANT_CARRILES];

matriz_t mapa;

bool refresco_autos = false;

clock_t tiempo_refresco_autos;

static struct{
	char nombre[L_MAX];
    int dificultad;
    int niv_actual;
    int posicion_sur;
    int posicion_oeste;
    uint16_t vidas;
    uint16_t ranas;
    uint16_t jugador_1;
    uint16_t jugador_2;
    uint64_t puntos;
    uint64_t max_puntos;
	bool jugando;
	bool agua;
	bool refresco;
	bool timeout;
    clock_t tiempo;
	clock_t tiempo_inicio;
	clock_t tiempo_referencia;
} jugador;

static clock_t tiempo_refresco_jugador = CLOCKS_PER_SEC >> 1;

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

static pthread_t ttiempo, tjugador, tautos;

static void* threadTiempo(void* ptr);
static void* threadJugador(void* ptr);
static void* threadAutos(void* ptr);


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
	


}

void moverCarrriles(int x){
	for(int i=0; i<5; i++)
		carril[i].completo <<= x;
}

void spawnearAutos(){
	int i;
		for(i=0; i<5; i++){
        	if(jugador.agua){
            	if(!(carril[i].completo & 0b1111111111) && !(rand() % 10))
                	carril[i].completo |= 0b111111;
            	else if(!(carril[i].completo & 0b111111111111) && !(rand() % 20))
                	carril[i].completo |= 0b11111111;
    		}
        	else{
            	if(!(carril[i].completo & 0b111111) && !(rand() % 10))
            		carril[i].completo |= 0b11;
            	else if(!(carril[i].completo & 0b11111111) && !(rand() % 20))
                	carril[i].completo |= 0b1111;
        	}
		}
}

void actualizarMapa(){
	if(jugador.agua){
		mapa[2] = jugador.ranas;
		mapa[3] = jugador.ranas;
	}
	else{
		mapa[2] = 0;
		mapa[3] = 0;
	}
	for(int i=0; i<5; i++){
		mapa[POS_AUTOS_INICIO+2*i] = carril[i].izquierdo;
		mapa[POS_AUTOS_INICIO+2*i+1] = carril[i].izquierdo;
	}
}

void refrescar(){
	if(refresco_autos){
		moverCarrriles(1);
		spawnearAutos();
		refresco_autos = false;
	}
	if(jugador.refresco){
		uint16_t tmp = jugador.jugador_1;
		jugador.jugador_1 = jugador.jugador_2;
		jugador.jugador_2 = tmp;
		jugador.refresco = false;
	}
}

bool tiempoRefrescoEntidades(void)
{
	return jugador.refresco || refresco_autos;
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
	if(!jugador.agua){
		jugador.jugador_1 = 0b0000000100000000;
		jugador.jugador_2 = 0b0000000010000000;
		jugador.posicion_oeste = 7;
	}

	for(int i=0; i< CANT_CARRILES; i++)
		carril[i].completo = 0;
	limpiarMatriz(mapa);

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
			jugador.ranas |= jugador.jugador_1 | jugador.jugador_2;
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
	jugador.tiempo_inicio = CLOCKS_PER_SEC*60 - (jugador.dificultad-jugador.niv_actual);
	jugador.tiempo = jugador.tiempo_inicio;
	jugador.tiempo_referencia = jugador.tiempo_inicio;
	tiempo_refresco_autos = CLOCKS_PER_SEC*(1-0.125*(jugador.dificultad-jugador.niv_actual-1));
	jugador.timeout = false;
}

void pausarJuego(){
	jugador.jugando = false;
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tjugador, NULL);
}

void actualizarInterfaz(){
	actualizarMapa();
	copiarMatriz(disp_matriz, mapa);
    disp_matriz[0] = jugador.vidas;
	clock_t frac = jugador.tiempo_inicio >> 4, aux = jugador.tiempo;
	disp_matriz[1] = 0;
	while(aux > 0){
		disp_matriz[1] <<= 1;
		disp_matriz[1] |= 1;
		aux -= frac;
	}

    disp_matriz[(jugador.posicion_sur)-1] |= jugador.jugador_1;
    disp_matriz[jugador.posicion_sur] |= jugador.jugador_2;

	actualizarDisplay();

	if((mapa[(jugador.posicion_sur)-1]) & jugador.jugador_1 || (mapa[(jugador.posicion_sur)]) & jugador.jugador_2  || jugador.timeout)
		perderVida();
		
}

void reanudarJuego(void)
{
	jugador.jugando = true;
	pthread_create(&ttiempo, NULL, threadTiempo, NULL);
	pthread_create(&tjugador, NULL, threadJugador, NULL);
	pthread_create(&tautos, NULL, threadAutos, NULL);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void* threadTiempo(void* ptr){
	clock_t ref = clock();
	while(jugador.jugando){
		if(!(jugador.timeout)){
			jugador.tiempo = jugador.tiempo_referencia - (clock() - ref);
			jugador.timeout = jugador.tiempo <= 0;
		}
		else{
			ref = clock();
		}
	}

	jugador.tiempo_referencia = jugador.tiempo;
	
	return NULL;
}

static void* threadAutos(void* ptr){
	clock_t ref = clock();
	while(jugador.jugando){
		if(!jugador.timeout && !refresco_autos){
			refresco_autos = (clock()-ref) > tiempo_refresco_autos;
		}
		else{
			ref = clock();
		}
	}
	return NULL;
}

static void* threadJugador(void* ptr){
	clock_t ref = clock();
	while(jugador.jugando){
		if(!jugador.timeout && !jugador.refresco){
			jugador.refresco = (clock()-ref) > tiempo_refresco_jugador;
		}
		else{
			ref = clock();
		}
	}
	return NULL;
}