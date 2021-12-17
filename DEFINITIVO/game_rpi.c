#include "game_rpi.h"

void reiniciarNivel(){
	jugador.ranas = 0b1001001001001001;
	jugador.tiempo_limite = 60*CLOCKS_PER_SEC*(1-0.05*(jugador.dificultad-FACIL));
	frac = jugador.tiempo_limite / 16;
	acc = frac;
	jugador.tiempo_bits = 0b1111111111111111;
	jugador.inicio = 0;
	jugador.agua = 0;
	respawn();
}

void respawn(){
    jugador.jugador_1 = 0b0000000010000000;
    jugador.jugador_2 = 0b0000000100000000;
	jugador.posicion_sur = CANT_FILAS-1;
	jugador.posicion_oeste = 7;
    int i, j;
    for(i=POS_AUTOS; i<POS_AUTOS+10; i+=2){
        uint16_t carril = 0;
		for(j=0; j<CANT_COLUMNAS;){
			int r = rand();
			if(r & 1){
				if(r & 0b10){
					carril |= jugador.agua? 0b1111 << j : 0b11 << j;
					j += jugador.agua? 6 : 4; //dejo 2 espacios mas
				}
				else{
					carril |= jugador.agua? 0b111111 << j : 0b1111 << j;
					j += jugador.agua? 8 : 6; //dejo 2 espacios mas
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
	jugador.inicio = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaAgua(){
	//ruido2
	jugador.vidas <<= 1;
	jugador.inicio = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void perderVidaTimeout(){
	//sin ruido?
	jugador.vidas <<= 1;
	jugador.inicio = 0;
	jugador.agua = 0;
	if(!jugador.vidas)
		queue_insert(GAME_OVER);
	else
		respawn();
}

void llegada(){
	

}