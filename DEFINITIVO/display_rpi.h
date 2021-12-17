#ifndef DISPLAY_RPI
#define DISPLAY_RPI

#include "bitmap_rpi.h"
#include "mensajes_rpi.h"
#include "disdrv.h"
#include <pthread.h>
#include "global.h"


pthread_mutex_t lock;

Matriz disp_matriz;

int iniciarDisplay();

void actualizarDisplay();

void escribirRenglonDisplay(Renglon r, int pos);

void escribirMatrizDisplay(Matriz m);

void limpiarDisplay();

void mostrarTexto(char* txt, int pos);



#endif