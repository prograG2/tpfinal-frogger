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

#include <stdint.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define CANT_FILAS 16
#define CANT_COLUMNAS 16


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint16_t matriz_t[CANT_FILAS];


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
void printMatriz(matriz_t a);

/**
 * @brief 
 * 
 * @param a 
 */
void limpiarMatriz(matriz_t a);

/**
 * @brief 
 * 
 * @param destino 
 * @param desde 
 */
void copiarMatriz(matriz_t destino, matriz_t desde);


/**
 * @brief 
 * 
 * @param a 
 * @param b 
 */
void matrizAnd(matriz_t a, matriz_t b);

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 */
void matrizOr(matriz_t a, matriz_t b);

/**
 * @brief 
 * 
 * @param a 
 */
void matrizNot(matriz_t a);

void matrizXor(matriz_t a, matriz_t b);


/*******************************************************************************
 ******************************************************************************/

#endif // _BITMAP_H_