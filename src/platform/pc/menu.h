#ifndef MENU
#define MENU

#include "queue.h"
#include "display.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define BOTON_ANCHO 25
#define BOTON_ALTO 10

struct{
char* textos[9];
int *menu_actual, *prev;
int opcion_actual;
int max_opciones;
} menu;

void setMenu(int* a, unsigned int size);

void setOpcion(int opc);

int getOpcion();

void subirOpcion();

void bajarOpcion();

void iniciarMenu();

void destruirMenu();

void moverOpcionActual();

#endif
