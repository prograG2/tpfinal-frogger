#ifndef MENU_RPI
#define MENU_RPI

<<<<<<< HEAD
#include "mensajes_rpi.h"

struct{
mensaje_t textos[9];
int *menu_actual, *prev;
int opcion_actual;
int max_opciones;
} menu;

=======
>>>>>>> rpi funcionando
void setMenu(int* a, unsigned int size);

void setOpcion(int opc);

<<<<<<< HEAD
=======
int getOpcion();

>>>>>>> rpi funcionando
void subirOpcion();

void bajarOpcion();

void iniciarMenu();

<<<<<<< HEAD
static void cambiarAOpcionActual();

=======
>>>>>>> rpi funcionando
void moverOpcionActual();

void destruirMenu();

#endif