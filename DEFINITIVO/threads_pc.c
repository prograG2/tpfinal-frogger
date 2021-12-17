#include "threads_pc.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

void *thread_display_menu(){
    while((p2CurrentState == en_menu_ppal) || (p2CurrentState == en_pausa) || (p2CurrentState == en_game_over)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        //pone todo en negro
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
    return NULL;
}

//cambiar los accesos a "jugador.algo" por algún "get_jugador", que lo dé game_pc.h
void *thread_tiempo(){
    clock_t ref = clock();
    while((p2CurrentState == jugando) && (jugador.tiempo < jugador.tiempo_limite)){
        jugador.tiempo = jugador.inicio + clock() - ref;
        if(jugador.tiempo > acc){
            jugador.tiempo_bits >>= 1;
            acc += frac;
        }
    }
    jugador.inicio = jugador.tiempo;
    queue_insert(TIMEOUT);
    return NULL;
}

void *thread_autos(){
    return NULL;
}

void *thread_display_juego(){
    return NULL;
}

void *thread_display_ranking(){
    FILE* pFile;
    char linea[100];
    pFile = fopen ("ranking.txt" , "r");
    if (pFile == NULL){
        perror ("mostrarRanking(): Error opening file");
        return NULL;
    }
    int puesto = 1;
    while(fgets(linea, 100, pFile) != NULL){
        char puesto_[2];
        ulltoa(puesto, puesto_);

        al_draw_text(font, al_map_rgb(0,0,255), ANCHO/2, 50, ALLEGRO_ALIGN_CENTER, puesto_);
        al_draw_text(font, al_map_rgb(0,0,255), ANCHO/2, 100, ALLEGRO_ALIGN_CENTER, linea);
        al_flip_display();
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
    }
    fclose (pFile);
    queue_insert(ENTER);
    return NULL;
}