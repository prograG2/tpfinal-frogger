#include "game_pc.h"

struct{
    char nombre[L_MAX];
    int dificultad;
    int niv_actual;
    int agua;
    int x;
    int y;
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
}jugador;

void reiniciarNivel(){
}

void respawn(){
}


case UP:
                            y -= STEP_FRACTION_SIZE;
                            break;

                        case DOWN:
                            y += STEP_FRACTION_SIZE;
                            break;

                        case RIGHT:
                            x += STEP_FRACTION_SIZE;
                            break;

                        case LEFT:
                            x -= STEP_FRACTION_SIZE;
                            break;
void moverAdelante(){
    jugador.
}

void moverAtras(){

}

void moverIzda(){
}

void moverDcha(){
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