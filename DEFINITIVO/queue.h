/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/
//https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "global.h"

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#if PLATAFORMA == PC
  #include <allegro5/allegro5.h>
  ALLEGRO_EVENT_QUEUE* al_queue;
  int last_key;
#endif

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
int queue_init();
void queue_insert(event_t);
int queue_empty();
event_t queue_next();
int queue_destroy();




/*******************************************************************************
 ******************************************************************************/

#endif // _QUEUE_H_
