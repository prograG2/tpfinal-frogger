#ifndef MENU_PC
#define MENU_PC

#include "queue.h"

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

void subirOpcion();

void bajarOpcion();

void iniciarMenu();

void destruirMenu();

#endif