#ifndef DISPLAY
#define DISPLAY

#include "mensajes.h"
#include "bitmap.h"

int iniciarDisplay();

void actualizarDisplay();

void escribirRenglonDisplay(Renglon r, int pos);

void escribirMatrizDisplay(Matriz m);

void limpiarDisplay();

void mostrarTexto(char* txt, int pos);

void fijarTexto(char* txt, int pos);

void mostrarPosicion(char* posicion, char* nombre, char* puntos);

#endif
