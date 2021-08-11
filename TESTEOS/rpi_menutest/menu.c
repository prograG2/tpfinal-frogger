#include "joydrv.h"
#include "mensajes.c"

enum movimiento{NO_MOVER, ARRIBA, ABAJO, IZDA, DCHA};
enum opciones{NO_OPT = -1, JUGAR, DIFICULTAD, RANKING, SALIR};

#define POS_MSJ1 2
#define POS_MSJ2 9

int movimiento(jcoord_t crd){
    if(crd.y >= 30 && (abs(crd.y) > abs(crd.x))) return ARRIBA;
    if(crd.y <= -30 && (abs(crd.y) > abs(crd.x))) return ABAJO;
    if(crd.x >= 30 && (abs(crd.y) < abs(crd.x))) return IZDA;
    if(crd.x <= -30 && (abs(crd.y) < abs(crd.x))) return DCHA;
    return NO_MOVER;
}

int abs(int8_t x){
    return x >= 0 ? x : -x;
}

int main(){
    disp_init();       //inicializa el display
    disp_clear();      //limpia todo el display
    joy_init();//inicializo el joystick

    char menu[][15] = {"JUGAR", "DIFICULTAD", "RANKING", "SALIR"};
    int opt = JUGAR; //donde estoy
    int slt = NO_OPT; //seleccionado
    int mov = NO_MOVER; //debo moverme (arriba, abajo, izda, dcha)?

    pthread_t p1, p2;

    p1 = escribirTexto(menu[opt], POS_MSJ1, 0);
    p2 = escribirTexto(menu[opt+1], POS_MSJ2, 1);

    do{
        joy_update();
        mov = movimiento(joy_get_coord());
        if(mov == ARRIBA){
            opt--;
            if (opt < JUGAR) opt = SALIR;
        }
        if(mov == ABAJO){
            opt++;
            if(opt > SALIR) opt = JUGAR;
        }



        slt = joy_get_switch() ? opt : NO_OPT;

    }while(slt != SALIR);

}