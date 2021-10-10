#ifndef MENU
#define MENU

#include "joystick.c"
#include "mensajes.c"
#include "display.c"
#include <time.h>
#include <stdlib.h>

#define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*0.1

typedef struct Menu{
    mensaje_t* opciones;
    int cant_opciones;
    int opcion_actual;
    int opc_elegida;
} menu_t;

pthread_t t1, t2;


void cambiarAOpcionActual(menu_t* menu){
    mensaje_t* opcion = (menu->opciones)+(menu->opcion_actual);
    opcion->index = opcion->index_inicio;
    copiarRenglon(opcion->renglon_inicio, opcion->renglon);
    copiarRenglon(opcion->reserva_inicio, opcion->reserva);
}

menu_t Menu(char** menu_, int size){
    mensaje_t* opc = malloc(size*sizeof(mensaje_t));
    int i;
    for(i=0;i<size;i++){
        opc[i] = mensaje(menu_[i], POS_MSJ2);
    }
    return (menu_t){opc, size, 0, -1};
}



void *thread_display(void* p){
    menu_t* menu = p;
    while(menu->opc_elegida < 0){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje((menu->opciones)+(menu->opcion_actual), REPETIR);
        escribirMensajeDisplay((menu->opciones)+(menu->opcion_actual));
    }
}

void *thread_joystick(void* p){
    menu_t* menu = p;
    while(menu->opc_elegida < 0){
        int joystick = leerJoystick();
        switch(joystick){
            case PRESS:
                menu->opc_elegida = menu->opcion_actual;
                break;
            case IZDA:
                menu->opcion_actual--;
                if(menu->opcion_actual < 0) 
                    menu->opcion_actual = menu->cant_opciones - 1;
                cambiarAOpcionActual(menu);
                break;
            case DCHA:
                menu->opcion_actual++;
                if(menu->opcion_actual == menu->cant_opciones) 
                    menu->opcion_actual = 0;
                cambiarAOpcionActual(menu);
                break;
        }
    }
}

int obtenerOpcion(menu_t* menu){
    menu->opcion_actual = 0;
    menu->opc_elegida = -1;
    cambiarAOpcionActual(menu);
    pthread_create(&t1, NULL, thread_display, menu);
    pthread_create(&t2, NULL, thread_joystick, menu);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return menu->opc_elegida;
}


void destruirMenu(menu_t* menu){
    free(menu->opciones);
}

#endif