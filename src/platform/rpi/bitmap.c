/**
 * @file 	bitmap.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Archivo para manejo de matrices 16x16
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "bitmap.h"

#include <stdio.h>

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void printMatriz(matriz_t a)
{
  for (int i = 0; i < CANT_FILAS; i++, putchar('\n'))
    for (int j = 0; j < CANT_FILAS; j++)
      putchar((a[i] & (0b1000000000000000 >> j)) ? '1' : '.');

  putchar('\n');
}

void limpiarMatriz(matriz_t a)
{
  for (int i = 0; i < CANT_FILAS; i++)
    a[i] = 0;
}

void copiarMatriz(matriz_t destino, const matriz_t desde)
{
  for (int i = 0; i < CANT_FILAS; i++)
    destino[i] = desde[i];
}

void matrizAnd(matriz_t a, matriz_t b)
{
  for (int i = 0; i < CANT_FILAS; i++)
    a[i] &= b[i];
}

void matrizOr(matriz_t a, matriz_t b)
{
  for (int i = 0; i < CANT_FILAS; i++)
    a[i] |= b[i];
}

void matrizXor(matriz_t a, matriz_t b)
{
  for (int i = 0; i < CANT_FILAS; i++)
    a[i] ^= b[i];
}

void matrizNot(matriz_t a)
{
  for (int i = 0; i < CANT_FILAS; i++)
    a[i] = ~a[i];
}