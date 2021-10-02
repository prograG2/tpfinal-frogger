#ifndef MENU
#define MENU

#include "joystick.c"
#include "mensajes.c"
#include "display.c"
#include <time.h>
#include <stdlib.h>

#define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*1

mensaje_t* menu;
int opcion_actual, cant_opciones, opc_elegida;
pthread_t t1, t2;


void cambiarAOpcionActual(){
    mensaje_t* opcion = menu+opcion_actual;
    opcion->index = opcion->index_inicio;
    copiarRenglon(opcion->renglon_inicio, opcion->renglon);
    copiarRenglon(opcion->reserva_inicio, opcion->reserva);
}

void nuevoMenu(char** menu_, int size){
    menu = malloc(size*sizeof(mensaje_t));
    int i;
    for(i=0;i<size;i++){
        menu[i] = mensaje(menu_[i], POS_MSJ2);
    }
    cant_opciones = size;
}



void *thread_display(){
    while(opc_elegida < 0){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje(menu+opcion_actual);
        escribirMensajeDisplay(menu+opcion_actual);
    }
}

void *thread_joystick(){
    while(opc_elegida < 0){
        int joystick = leerJoystick();
        switch(joystick){
            case PRESS:
                opc_elegida = opcion_actual;
                break;
            case IZDA:
                opcion_actual--;
                if(opcion_actual < 0) opcion_actual = cant_opciones - 1;
                cambiarAOpcionActual();
                break;
            case DCHA:
                opcion_actual++;
                if(opcion_actual == cant_opciones) opcion_actual = 0;
                cambiarAOpcionActual();
                break;
        }
    }
}

int iniciarMenu(){
    opcion_actual = 0;
    opc_elegida = -1;
    cambiarAOpcionActual();
    pthread_create(&t1, NULL, thread_display, NULL);
    pthread_create(&t2, NULL, thread_joystick, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return opc_elegida;
}


void destruirMenu(){
    free(menu);
}

#endif