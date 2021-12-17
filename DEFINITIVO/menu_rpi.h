#ifndef MENU_RPI
#define MENU_RPI

#include "mensajes_rpi.h"

struct{
mensaje_t textos[9];
int *menu_actual, *prev;
int opcion_actual;
int max_opciones;
} menu;

void setMenu(int* a, unsigned int size);

void setOpcion(int opc);

void subirOpcion();

void bajarOpcion();

void iniciarMenu();

static void cambiarAOpcionActual();

void moverOpcionActual();

void destruirMenu();

#endif