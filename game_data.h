/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "global.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
    char rana : 1;
    char objeto : 5;
    char piso : 2;
}celda_t;


static struct
{
	const char* nombre;
	int vidas;
	unsigned long puntos;
	char dificultad;
} datos;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void inicializar();
void resetVidas();
void decrementarVidas();
int getVidas();
void setNombre();
const char* getNombre();
void setPuntos();
unsigned long getPuntos();


/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_DATA_H_
