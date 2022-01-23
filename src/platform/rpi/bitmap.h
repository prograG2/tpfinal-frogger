/**
 * @file bitmap.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _BITMAP_H_
#define _BITMAP_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "rpiconsts.h"

#include <stdint.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint16_t Matriz[CANT_FILAS];


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 * @param a 
 */
void printMatriz(Matriz a);

/**
 * @brief 
 * 
 * @param a 
 */
void limpiarMatriz(Matriz a);

/**
 * @brief 
 * 
 * @param destino 
 * @param desde 
 */
void copiarMatriz(Matriz destino, Matriz desde);


/*******************************************************************************
 ******************************************************************************/

#endif // _BITMAP_H_