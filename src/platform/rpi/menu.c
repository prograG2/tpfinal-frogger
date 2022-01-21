#include "menu.h"
#include "mensajes.h"
#include "display.h"
#include <stdlib.h>

struct{
mensaje_t textos[9];
int *menu_actual;
int opcion_actual;
int max_opciones;
} menu;

static void cambiarAOpcionActual();

void setMenu(int* a, unsigned int size){
    menu.menu_actual = realloc(menu.menu_actual, size*sizeof(int));
    int i;
    for(i=0; i<size; i++){
        menu.menu_actual[i] = a[i];
    }
    menu.max_opciones = size;
}

void setOpcion(int opc){
    menu.opcion_actual = opc;
    cambiarAOpcionActual();
}

int getOpcion(){
    return menu.opcion_actual;
}

void subirOpcion(){
    if(--menu.opcion_actual < 0)
        menu.opcion_actual = menu.max_opciones - 1;
    cambiarAOpcionActual();
}

void bajarOpcion(){
    if(++menu.opcion_actual >= menu.max_opciones)
        menu.opcion_actual = 0;
    cambiarAOpcionActual();
}

void iniciarMenu(){
    menu.textos[JUGAR] = mensaje("JUGAR", POS_MSJ2);
    menu.textos[DIFICULTAD] = mensaje("DIFICULTAD", POS_MSJ2);
    menu.textos[RANKING] = mensaje("RANKING", POS_MSJ2);
    menu.textos[SALIRTXT] = mensaje("SALIR", POS_MSJ2);
    menu.textos[CONTINUAR] = mensaje("CONTINUAR", POS_MSJ2);
    menu.textos[REINICIAR] = mensaje("REINICIAR", POS_MSJ2);
    menu.textos[FACIL] = mensaje("FACIL", POS_MSJ2);
    menu.textos[NORMAL] = mensaje("NORMAL", POS_MSJ2);
    menu.textos[DIFICIL] = mensaje("DIFICIL", POS_MSJ2);
}

static void cambiarAOpcionActual(){
    menu.textos[menu.menu_actual[menu.opcion_actual]].index = menu.textos[menu.menu_actual[menu.opcion_actual]].index_inicio;
    copiarRenglon(menu.textos[menu.menu_actual[menu.opcion_actual]].renglon_inicio, menu.textos[menu.menu_actual[menu.opcion_actual]].renglon);
    copiarRenglon(menu.textos[menu.menu_actual[menu.opcion_actual]].reserva_inicio, menu.textos[menu.menu_actual[menu.opcion_actual]].reserva);
}

void moverOpcionActual(){
    moverMensaje(&menu.textos[menu.menu_actual[menu.opcion_actual]], REPETIR);
    escribirRenglonDisplay(menu.textos[menu.menu_actual[menu.opcion_actual]].renglon, menu.textos[menu.menu_actual[menu.opcion_actual]].posicion);
}

void destruirMenu(){
    free(menu.menu_actual);
}
