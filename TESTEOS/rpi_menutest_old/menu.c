#include "joydrv.h"
#include "mensajes.c"
#include <time.h>

enum movimiento{NO_MOVER, ARRIBA, IZDA, ABAJO, DCHA};
//enum opciones{NO_OPT = -1, JUGAR, DIFICULTAD, RANKING, SALIR};

#define TAM_MENU 4

#define ID_JUGAR 0
#define ID_DIFICULTAD 1
#define ID_RANKING 2
#define ID_SALIR 3

#define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*0.05

Matriz matriz = {0};

int movimiento(jcoord_t crd){
    if(crd.y >= 30 && (abs(crd.y) > abs(crd.x))) return ARRIBA;
    if(crd.y <= -30 && (abs(crd.y) > abs(crd.x))) return IZDA;
    if(crd.x >= 30 && (abs(crd.y) < abs(crd.x))) return ABAJO;
    if(crd.x <= -30 && (abs(crd.y) < abs(crd.x))) return DCHA;
    return NO_MOVER;
}

int abs(int8_t x){
    return x >= 0 ? x : -x;
}

void rotar_adelante(opcion_t arr[]){
    opcion_t tmp = arr[TAM_MENU-1];
    for(int i=TAM_MENU-1; i>0; i--)
        arr[i] = arr[i-1];
    arr[0] = tmp;

    
    arr[0].posicion = POS_MSJ1;
    arr[1].posicion = POS_MSJ2;
    arr[2].posicion = NO_POS;
}

void rotar_atras(opcion_t arr[]){
    opcion_t tmp = arr[0];
    for(int i=0; i<(TAM_MENU-1); i++)
        arr[i] = arr[i+1];
    arr[TAM_MENU-1] = tmp;

    arr[0].posicion = POS_MSJ1;
    arr[1].posicion = POS_MSJ2;
    arr[3].posicion = NO_POS;
}

void actualizarMenu(opcion_t menu[], int opt, int opt_prev){
    desltOpcion(&menu[opt_prev]);
    sltOpcion(&menu[opt]);
    escribirRenglon(matriz, menu[0].renglon, POS_MSJ1);
    escribirRenglon(matriz, menu[1].renglon, POS_MSJ2);
}

void *thread(opcion_t* opcion){
    clock_t meta = clock() + SLEEP_CLOCKS;
    while(clock() < meta);
    moverOpcion(opcion);
    escribirRenglon(matriz, opcion->renglon, opcion->posicion);
}

int main(){
    disp_init();       //inicializa el display
    disp_clear();      //limpia todo el display
    joy_init();//inicializo el joystick

    opcion_t menu[] = {opcion(ID_JUGAR, "JUGAR", POS_MSJ1), opcion(ID_DIFICULTAD, "DIFICULTAD", POS_MSJ2), opcion(ID_RANKING, "RANKING", NO_POS), opcion(ID_SALIR, "SALIR", NO_POS)};

    int opt = 0; //donde estoy
    int opt_prev = 0; //donde estaba

    int mov = NO_MOVER; //debo moverme (arriba, abajo, izda, dcha)?
    int mov_prev = NO_MOVER;

    actualizarMenu(menu, opt, opt_prev);

    pthread_t t1;
    
    pthread_create(&t1, NULL, thread, &menu[opt]);
    
    while(!(joy_get_switch() == J_PRESS && menu[opt].id == ID_SALIR)){
        joy_update();
        mov = movimiento(joy_get_coord());
        if((mov == ARRIBA || mov == ABAJO) && mov != mov_prev){
            opt += mov - 1; //ARRIBA -> -1 , ABAJO ->+1
            if (opt < 0){
                opt = 0;
                rotar_adelante(menu);
            }
            if(opt > 1){
                opt = 1;
                rotar_atras(menu);
            }
            actualizarMenu(menu, opt, opt_prev);
            opt_prev = opt;
        }
        mov_prev = mov;

    }

    pthread_join(t1, NULL);

}