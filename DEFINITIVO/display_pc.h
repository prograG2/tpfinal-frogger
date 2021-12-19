#ifndef DISPLAY_PC
#define DISPLAY_PC

#include <pthread.h>
#include "global.h"
#include "queue.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


pthread_mutex_t lock;

int iniciarDisplay();

void actualizarDisplay();

void limpiarDisplay();

void mostrarTexto(char* txt, int pos);

ALLEGRO_DISPLAY* disp;
ALLEGRO_FONT* font;



#endif