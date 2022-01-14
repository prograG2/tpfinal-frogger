#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define CHAR_H = 8 //al_create_builtin_font() crea caracteres de 8x8 pixeles. CREO.
#define CHAR_W = 8

ALLEGRO_FONT* font;
long score_display;
char runs_display;
char timer_min;
char timer_sec;

//Inicializa el HUD y pone los contadores en 0.
void hud_init()
{
    font = al_create_builtin_font();
    must_init(font, "font");

    score_display = 0;
    runs_display = 0;
    timer_min = 0;
    timer_sec = 0;
}

//Destruye lo usado.
void hud_deinit()
{
    al_destroy_font(font);
}

void hud_update()
{
    if(frames % 2)          //Para que se actualice cada 2 frames y se vea mejor (no creo que cambie mucho).
        return;

    /*
    Aca se aumenta el puntuacion en pantalla hasta igualar la puntuacion real. Lo que hace el for es calcular 2^i (1 << i, no pregunten como),
    para que se vea bien 'fluido' como aumentan los numeros. En otras palabras mientras mas lejos este la puntuecion en pantalla de la real,
    mas rapido aumenta. CLARAMENTE ESTA ROBADA ESTA PARTE.

    Para determinar las condiciones de puntuacion que dijimos hay que tirar cada cosa a la variable 'score' i.e si damos 1000 puntos por
    completar la vuelta, donde se determina que la vuelta se completa hay que agregar una lines 'score += 100;'.
    */
    for(long i = 5; i > 0; i--)
    {
        long diff = 1 << i;
        if(score_display <= (score - diff))
            score_display += diff;
    }

    //Ve si llega a la ultima filaa.
    if(runs_display < runs)           //'runs' deberia aumentar cada vez que la rana vuelve a la primera fila (recomiendo que empiece en 0).
        runs_display++;  

    //Analiza el tiempo.
    if(timer_sec < 60)
        timer_sec++;
    else
    {   timer_sec = 0;
        timer_min++;
    }
}

void hud_draw()
{
    //Dibuja la puntuacion en pantalla.
    al_draw_textf(
        font,
        al_map_rgb(0, 0, 0),        //Negro porque por ahora sigue el fondo blanco, sino recomiendo amarillo (255, 255, 51).
        1, 1,                       //Arriba a la izquierda.
        0,
        "%06ld",                    //6 cifras (por ahi es mucho).
        score_display);

    //Dibuja el numero de vuelta.
    al_draw_textf(
        font,
        al_map_rgb(0, 0, 0),
        1, CHAR_H + 2,              //Para que quede abaj de la puntuacion en pantalla.
        0,
        "%02ld",                    //2 cifras. No me acuerdo si esta bien asi.
        runs_display);

    //Dibuja vidas.
    for(int i = 0; i < frog.lives; i++)         //No se si la rana tiene 'frog.lives' pero aca va el equivalente.
        al_draw_bitmap(
            "minecraft_heart.png",
            BUFFEER_w - (1 + (i * (LIFE_W + 1))), 1,         //Arriba a la derecha. 'LIFE_W' depende de la imagen que usemos.
            0);
    if(frog.lives < 0)
        al_draw_text(
            font,
            al_map_rgb(255, 255, 51),       //Amarillo, es el color que mas se ditingue en general.
            BUFFER_W / 2, BUFFER_H / 2,
            ALLEGRO_ALIGN_CENTER,           //Para que se dibuje en el medio.
            "G A M E  O V E R");

    //Dibuja el timer.
    //Minutos.
    al_draw_textf(
        font,
        al_map_rgb(0, 0, 0),
        5 * CHAR_W, CHAR_H + 2,         //Para que quede abajo de las vidas.
        0,
        "%02ld",
        timer_min);
    //:
    al_draw_text(
        font,
        al_map_rgb(0, 0, 0),
        3 * CHAR_W, CHAR_H + 2,
        0,
        ":");
    //Segundos.
    al_draw_textf(
        font,
        al_map_rgb(0, 0, 0),
        2 * CHAR_W, CHAR_H + 2,
        0,
        "%02ld",
        timer_sec);
}