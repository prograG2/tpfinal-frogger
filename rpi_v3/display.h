#ifndef DISPLAY
#define DISPLAY

#include "bitmap.h"
#include "mensajes.h"
#include "disdrv.h"
#include <time.h>
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