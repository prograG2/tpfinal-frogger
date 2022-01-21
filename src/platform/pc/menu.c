#include "menu.h"

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

void moverOpcionActual(){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    int i, y_coord = 100;
        for(i=0;i<menu.max_opciones;i++){
            al_draw_text(font, al_map_rgb(0,0,255), ANCHO/2, y_coord, ALLEGRO_ALIGN_CENTER, menu.textos[menu.menu_actual[menu.opcion_actual]]);
            ALLEGRO_COLOR color;
            if(menu.opcion_actual == i)
                color = al_map_rgb(0, 100, 0);
            else
                color = al_map_rgb(100,100,100);
            al_draw_filled_rectangle(ANCHO/2 - 75, y_coord, ANCHO/2 + 75, y_coord + 50, color);
            y_coord += 100;

			
        }
    al_flip_display();
}
