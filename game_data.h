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



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

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

const char* game_data_getNombre(void);
int game_data_getVidas(void);
unsigned long game_data_getPuntos(void);
char game_data_getDificultad(void);

int game_data_setNombre(const char* nombre);
int game_data_setVidas_full(void);
int game_data_setVidas_dec(void);
int game_data_setVidas_clear(void);
int game_data_setPuntos_inc(void);
int game_data_setPuntos_clear(void);
int game_data_setDificultad_easy(void);
int game_data_setDificultad_normal(void);
int game_data_setDificultad_hard(void);
int game_data_setDificultad_expert(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_DATA_H_
