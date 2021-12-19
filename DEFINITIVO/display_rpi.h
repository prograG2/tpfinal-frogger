#ifndef DISPLAY_RPI
#define DISPLAY_RPI

#include "mensajes_rpi.h"
#include "bitmap_rpi.h"

int iniciarDisplay();

void actualizarDisplay();

void escribirRenglonDisplay(Renglon r, int pos);

void escribirMatrizDisplay(Matriz m);

void limpiarDisplay();

void mostrarTexto(char* txt, int pos);



#endif