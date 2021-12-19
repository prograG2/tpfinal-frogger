#ifndef DISPLAY_RPI
#define DISPLAY_RPI

<<<<<<< HEAD
#include "bitmap_rpi.h"
#include "mensajes_rpi.h"
#include "disdrv.h"
#include <pthread.h>
#include "global.h"


pthread_mutex_t lock;

Matriz disp_matriz;
=======
#include "mensajes_rpi.h"
#include "bitmap_rpi.h"
>>>>>>> rpi funcionando

int iniciarDisplay();

void actualizarDisplay();

void escribirRenglonDisplay(Renglon r, int pos);

void escribirMatrizDisplay(Matriz m);

void limpiarDisplay();

void mostrarTexto(char* txt, int pos);



#endif