/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/
//https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
#ifndef _LISTA_DINAMICA_H_
#define _LISTA_DINAMICA_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdlib.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct {
  int *array;
  unsigned long used;
  unsigned long size;
} Array;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void initArray(Array *a, unsigned long initialSize);
void insertArray(Array *a, int element);

void freeArray(Array *a);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
// +ej: char lcd_goto (int fil, int col);+


/*******************************************************************************
 ******************************************************************************/

#endif // _TEMPLATE_H_
