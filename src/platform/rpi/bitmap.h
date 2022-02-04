/**
 * @file 	bitmap.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Encabezado del archivo para manejo de matrices 16x16
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
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

typedef uint16_t matriz_t[CANT_FILAS]; // se define el tipo de dato para trabajar en el display, cada elemento del array es una fila

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Imprime una matriz en consola (para debug)
 *
 * @param A
 */
void printMatriz(matriz_t A);

/**
 * @brief Borra el contenido de una matriz
 *
 * @param A
 */
void limpiarMatriz(matriz_t A);

/**
 * @brief Copia el contenido de una matriz en otra
 *
 * @param destino
 * @param desde
 */
void copiarMatriz(matriz_t destino, const matriz_t desde);

/**
 * @brief Dadas dos matrices A y B, se hará la operación "A &= B"
 *
 * @param A
 * @param B
 */
void matrizAnd(matriz_t A, matriz_t B);

/**
 * @brief Dadas dos matrices A y B, se hará la operación "A |= B"
 *
 * @param A
 * @param B
 */
void matrizOr(matriz_t A, matriz_t B);

/**
 * @brief Dadas una matriz A, se hará la operación "A = ~A"
 *
 * @param A
 */
void matrizNot(matriz_t A);

/**
 * @brief Dadas dos matrices A y B, se hará la operación "A ^= B"
 *
 * @param A
 * @param B
 */
void matrizXor(matriz_t A, matriz_t B);

/*******************************************************************************
 ******************************************************************************/

#endif // _BITMAP_H_