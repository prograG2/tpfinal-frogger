#include "menu_pc.h"

void setMenu(int* a, unsigned int size){
    menu.menu_actual = realloc(menu.prev = menu.menu_actual, size*sizeof(int));
    int i;
    for(i=0; i<size; i++){
        menu.menu_actual[i] = a[i];
    }
    menu.max_opciones = size;
}

void setOpcion(int opc){
    menu.opcion_actual = opc;
}

void subirOpcion(){
    if(--menu.opcion_actual < 0)
        menu.opcion_actual = menu.max_opciones - 1;
}

void bajarOpcion(){
    if(++menu.opcion_actual >= menu.max_opciones)
        menu.opcion_actual = 0;
}

void iniciarMenu(){
    menu.textos[0] = "JUGAR";
    menu.textos[1] = "DIFICULTAD";
    menu.textos[2] = "RANKING";
    menu.textos[3] = "SALIR";
    menu.textos[4] = "CONTINUAR";
    menu.textos[5] = "REINICIAR";
    menu.textos[6] = "FACIL";
    menu.textos[7] = "NORMAL";
    menu.textos[8] = "DIFICIL";
}

void destruirMenu(){
    free(menu.menu_actual);
    free(menu.prev);
}
