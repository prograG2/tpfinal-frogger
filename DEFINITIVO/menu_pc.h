#ifndef MENU_PC
#define MENU_PC

#include "queue.h"
<<<<<<< HEAD
=======
#include "display_pc.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
>>>>>>> rpi funcionando

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

<<<<<<< HEAD
=======
int getOpcion();

>>>>>>> rpi funcionando
void subirOpcion();

void bajarOpcion();

void iniciarMenu();

void destruirMenu();

<<<<<<< HEAD
=======
void moverOpcionActual();

>>>>>>> rpi funcionando
#endif