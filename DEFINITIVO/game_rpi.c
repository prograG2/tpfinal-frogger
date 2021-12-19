#include "game_rpi.h"

<<<<<<< HEAD
=======
#include "queue.h"
#include "bitmap_rpi.h"
#include "global.h"
#include "display_rpi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

void refrescarJugador(){
	uint16_t tmp = jugador.jugador_1;
	jugador.jugador_1 = jugador.jugador_2;
	jugador.jugador_2 = tmp;
}

void refrescarAutos(){
	int i;
    for(i=POS_AUTOS; i<POS_AUTOS+10; i+=2){
        uint16_t carril = jugador.mapa[i] << 1;
        if(jugador.agua){
            if(!(carril & 0b11111111) && !(rand() % 10))
                carril |= 0b11;
            else if(!(carril & 0b1111111111) && !(rand() % 20))
                carril |= 0b1111;
        }
        else{
            if(!(carril & 0b111111) && !(rand() % 10))
            carril |= 0b11;
            else if(!(carril & 0b11111111) && !(rand() % 20))
                carril |= 0b1111;
        }
        jugador.mapa[i] = carril;
        jugador.mapa[i+1] = carril;
        
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

>>>>>>> rpi funcionando
void reiniciarNivel(){
	jugador.ranas = 0b1001001001001001;
	jugador.tiempo_limite = 60*CLOCKS_PER_SEC*(1-0.05*(jugador.dificultad-FACIL));
	frac = jugador.tiempo_limite / 16;
	acc = frac;
	jugador.tiempo_bits = 0b1111111111111111;
<<<<<<< HEAD
	jugador.inicio = 0;
=======
	jugador.tiempo_inicial = 0;
>>>>>>> rpi funcionando
	jugador.agua = 0;
	respawn();
}

void respawn(){
    jugador.jugador_1 = 0b0000000010000000;
    jugador.jugador_2 = 0b0000000100000000;
<<<<<<< HEAD
=======
	if(jugador.agua){
		jugador.mapa[2] = jugador.ranas;
		jugador.mapa[3] = jugador.ranas;
	}
	else{
		jugador.mapa[2] = 0;
		jugador.mapa[3] = 0;
	}
>>>>>>> rpi funcionando
	jugador.posicion_sur = CANT_FILAS-1;
	jugador.posicion_oeste = 7;
    int i, j;
    for(i=POS_AUTOS; i<POS_AUTOS+10; i+=2){
        uint16_t carril = 0;
		for(j=0; j<CANT_COLUMNAS;){
<<<<<<< HEAD
			int r = rand();
			if(r & 1){
				if(r & 0b10){
					carril |= jugador.agua? 0b1111 << j : 0b11 << j;
					j += jugador.agua? 6 : 4; //dejo 2 espacios mas
				}
				else{
					carril |= jugador.agua? 0b111111 << j : 0b1111 << j;
					j += jugador.agua? 8 : 6; //dejo 2 espacios mas
=======
			if(rand() & 1){
				if(jugador.agua){
					if(!(rand()%2)){
						carril |= 0b111111 << j;
						j += 8;
					}
				}
				else if(!(rand()%10)){
					carril |= 0b11 << j;
					j += 4;
				}
				else if(!(rand()%20)){
					carril |= 0b1111 << j;
					j += 6;
>>>>>>> rpi funcionando
				}
			}
			else{
				j += 2; //dejo 2 espacios
			}
		}
		if (jugador.agua)
			carril = ~carril;
		jugador.mapa[i] = carril;
		jugador.mapa[i+1] = carril;
    }
}

void moverAdelante(){
	if(jugador.posicion_sur > 3)
		jugador.posicion_sur--;
<<<<<<< HEAD
    else{
        if(!jugador.agua){
		jugador.agua = 1;
		jugador.mapa[2] = jugador.ranas;
		jugador.mapa[3] = jugador.ranas;
		respawn();
	}
	else{
		jugador.ranas |= jugador.jugador_1 | jugador.jugador_2;
		if(jugador.ranas == 0b1111111111111111){
            queue_insert(META);
		}
		else
			respawn();
=======
    if(jugador.posicion_sur == 3){
        if(!jugador.agua){
		jugador.agua = 1;
		respawn();
		}
		else{
			printf("Agregando rana\n");
			jugador.ranas |= jugador.jugador_1 | jugador.jugador_2;
			printf("%d\n", jugador.ranas);
			if(jugador.ranas == 0b1111111111111111){
            	queue_insert(META);
			}
			else{
				jugador.agua = 0;
				respawn();
			}
>>>>>>> rpi funcionando
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
<<<<<<< HEAD
	jugador.inicio = 0;
=======
	jugador.tiempo_inicial = 0;
>>>>>>> rpi funcionando
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaAgua(){
	//ruido2
	jugador.vidas <<= 1;
<<<<<<< HEAD
	jugador.inicio = 0;
=======
	jugador.tiempo_inicial = 0;
>>>>>>> rpi funcionando
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaTimeout(){
	//sin ruido?
	jugador.vidas <<= 1;
<<<<<<< HEAD
	jugador.inicio = 0;
=======
	jugador.tiempo_inicial = 0;
>>>>>>> rpi funcionando
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void llegada(){
	

}

<<<<<<< HEAD
void inicializarJugador()
{
    
=======
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
>>>>>>> rpi funcionando
}