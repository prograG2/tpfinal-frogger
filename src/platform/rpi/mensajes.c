/**
 * @file 	mensajes.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Permite codificar strings en formato renglon para mostrar en display
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "mensajes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define INDEX_ESPACIO 26
#define INDEX_CERO 27
#define INDEX_FULL 37
#define CANT_SIMBOLOS 38

#define PEDIR_FULL -1
#define ANCHO_MAXIMO 5

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Devuelve el ancho que ocupa un caracter en display
 *
 * @param a caracter
 * @return int ancho
 */
static int getLongitud(char a);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static const int longitudes[] = {3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5}; // sin contar Ñ (+ espacio + numeros + FULL)

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static uint16_t char_index[][TAM_RENGLON] = {{0x4000, 0xA000, 0xE000, 0xA000, 0xA000}, // A
                                             {0xC000, 0xA000, 0xC000, 0xA000, 0xC000},
                                             {0x4000, 0xA000, 0x8000, 0xA000, 0x4000},
                                             {0xC000, 0xA000, 0xA000, 0xA000, 0xC000},
                                             {0xE000, 0x8000, 0xC000, 0x8000, 0xE000},
                                             {0xE000, 0x8000, 0xC000, 0x8000, 0x8000},
                                             {0x6000, 0x8000, 0xA000, 0xA000, 0x6000},
                                             {0xA000, 0xA000, 0xE000, 0xA000, 0xA000},
                                             {0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
                                             {0x2000, 0x2000, 0xA000, 0xA000, 0x4000},
                                             {0xA000, 0xA000, 0xC000, 0xA000, 0xA000},
                                             {0x8000, 0x8000, 0x8000, 0x8000, 0xE000},
                                             {0x8800, 0xD800, 0xA800, 0xA800, 0x8800},
                                             {0x9000, 0xD000, 0xB000, 0x9000, 0x9000},
                                             {0x4000, 0xA000, 0xA000, 0xA000, 0x4000},
                                             {0xC000, 0xA000, 0xA000, 0xC000, 0x8000},
                                             {0x4000, 0xA000, 0xA000, 0xA000, 0x6000},
                                             {0xC000, 0xA000, 0xC000, 0xA000, 0xA000},
                                             {0x6000, 0x8000, 0x4000, 0x2000, 0xC000},
                                             {0xE000, 0x4000, 0x4000, 0x4000, 0x4000},
                                             {0xA000, 0xA000, 0xA000, 0xA000, 0x4000},
                                             {0xA000, 0xA000, 0xA000, 0x4000, 0x4000},
                                             {0x8800, 0xA800, 0xA800, 0x5000, 0x5000},
                                             {0xA000, 0xA000, 0x4000, 0xA000, 0xA000},
                                             {0xA000, 0xA000, 0x4000, 0x4000, 0x4000},
                                             {0xE000, 0x2000, 0x4000, 0x8000, 0xE000}, // Z
                                             {0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, // espacio
                                             {0x4000, 0xA000, 0xA000, 0xA000, 0x4000}, // 0
                                             {0x4000, 0xC000, 0x4000, 0x4000, 0xE000},
                                             {0x4000, 0xA000, 0x2000, 0x4000, 0xE000},
                                             {0xC000, 0x2000, 0x4000, 0x2000, 0xC000},
                                             {0xA000, 0xA000, 0xE000, 0x2000, 0x2000},
                                             {0xE000, 0x8000, 0xC000, 0x2000, 0xC000},
                                             {0x4000, 0x8000, 0xC000, 0xA000, 0xC000},
                                             {0xE000, 0x2000, 0x2000, 0x4000, 0x4000},
                                             {0x4000, 0xA000, 0x4000, 0xA000, 0x4000},
                                             {0x4000, 0xA000, 0x6000, 0x2000, 0x4000},  // 9
                                             {0xF800, 0xF800, 0xF800, 0xF800, 0xF800}}; // TODO (FULL)

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void printRenglon(renglon_t r)
{
  putchar('\n');
  for (int i = 0; i < TAM_RENGLON; i++, putchar('\n'))
  {
    for (int j = 0; j < 2 * CANT_FILAS; j++)
    {
      putchar((r[i].completo & (0x80000000 >> j)) ? '#' : '-');
      if (j == CANT_FILAS - 1)
        putchar('|');
    }
  }
}

void borrarRenglon(renglon_t r)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r[i].completo = 0;
}

void renglonShiftDer(renglon_t r, uint16_t s)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r[i].completo >>= s;
}

void renglonShiftIzq(renglon_t r, uint16_t s)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r[i].completo <<= s;
}

void renglonOr(renglon_t r, renglon_t s)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r[i].completo |= s[i].completo;
}

void renglonAnd(renglon_t r, renglon_t s)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r[i].completo &= s[i].completo;
}

void renglonNot(renglon_t r)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r[i].completo = ~r[i].completo;
}

void copiarRenglon(renglon_t r1, const renglon_t r2)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    r1[i].completo = r2[i].completo;
}

void copiarMatrizRenglon(matriz_t m, const renglon_t r, int pos)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    m[pos + i] = r[i].mitad_izq;
}

bool renglonIzquierdoLibre(mensaje_t *msj)
{
  for (int i = 0; i < TAM_RENGLON; i++)
    if ((msj->renglon)[i].mitad_izq)
      return false;
  return true;
}

void charARenglon(char c, renglon_t r)
{
  int indice;

  if (c == ' ' || !c)
    indice = INDEX_ESPACIO;
  else if ('0' <= c && c <= '9')
    indice = INDEX_CERO + c - '0';
  else if ('A' <= c && c <= 'Z')
    indice = c - 'A';
  else
    indice = INDEX_FULL;

  for (int i = 0; i < TAM_RENGLON; i++)
  {
    r[i].mitad_izq = char_index[indice][i];
    r[i].mitad_der = 0;
  }
}

void charAMatriz(char c, matriz_t m, const int coord[])
{
  limpiarMatriz(m);
  renglon_t r;
  charARenglon(c, r);
  renglonShiftDer(r, coord[0]);
  copiarMatrizRenglon(m, r, coord[1]);
}

void uintARenglon(uint16_t n, renglon_t r)
{
  renglon_t renglon_aux;
  int j = 0, resto = CANT_COLUMNAS;
  uint16_t div = 10000;

  while (n % div == n)
    div /= 10;

  while (n)
  {
    uint16_t aux = n % div;
    n = (n - aux) / div;
    resto = CANT_COLUMNAS - j - longitudes[INDEX_CERO + n];
    if (resto < 0)
      break;
    charARenglon(n + '0', renglon_aux);
    renglonShiftDer(renglon_aux, j);
    renglonOr(r, renglon_aux);
    j += longitudes[INDEX_CERO + n] + 1;
    n = aux;
    div /= 10;
  }
}

void reemplazarLetra(renglon_t r, char c, int j)
{
  renglon_t full, letra;
  charARenglon(c, letra);
  renglonShiftDer(letra, j);
  charARenglon(PEDIR_FULL, full);
  renglonShiftDer(full, j);
  renglonNot(full);
  renglonAnd(r, full);
  renglonOr(r, letra);
}

mensaje_t mensaje(char *msj, int pos, bool repetir)
{
  mensaje_t mensaje = {.posicion = pos, .habilitacion = true, .repetir_msj = repetir};
  borrarRenglon(mensaje.renglon);
  strcpy(mensaje.msj, msj);
  int longitud_parcial = strlen(mensaje.msj);

  int j = 0; // a partir de donde voy a escribir la proxima vez
  int i;
  for (i = 0; i < longitud_parcial; i++)
  {                  // rellena el mensaje por primera vez
    char c = msj[i]; // el caracter que debo escribir

    renglon_t letra;
    charARenglon(c, letra); // letra contiene la letra provisoria pasada a renglón

    int ancho = getLongitud(c);
    if (2 * CANT_COLUMNAS - j - ancho < 0)
      break; // lo que me quedaría libre si escribo

    renglonShiftDer(letra, j);         // muevo la letra sobre renglon
    renglonOr(mensaje.renglon, letra); // escribo en el renglon
    j += ancho + 1;                    // dejo un espacio entre letra y letra
  }

  mensaje.index = i;
  mensaje.j = j;

  mensaje.mover_texto = (i < longitud_parcial) || (j > CANT_COLUMNAS + 1); // veo si entra el mensaje en el renglon izquierdo

  if (mensaje.mover_texto)
  {
    strcat(mensaje.msj, "     ");
    mensaje.longitud = strlen(mensaje.msj);
  }
  else
    mensaje.longitud = longitud_parcial;

  return mensaje;
}

void moverMensaje(mensaje_t *msj)
{
  if (!(msj->mover_texto) || !(msj->habilitacion)) // tengo permitido mover el mensaje?
    return;

  renglonShiftIzq(msj->renglon, 1);
  msj->j--;

  if (!(msj->repetir_msj) && msj->index >= msj->longitud) // tengo que repetirlo cuando termine de recorrerlo?
  {
    if (renglonIzquierdoLibre(msj)) // termine de pasar el mensaje?
      msj->habilitacion = false;
    return;
  }

  char c = (msj->msj)[msj->index];
  int ancho = getLongitud(c);

  if (2 * CANT_COLUMNAS - msj->j - ancho < 0) // me queda espacio para poner la siguiente letra?
    return;

  // pongo la siguiente letra
  renglon_t letra;
  charARenglon(c, letra);
  renglonShiftDer(letra, msj->j);
  renglonOr(msj->renglon, letra);
  msj->j += ancho + 1; // dejo un espacio entre letra y letra
  if (++msj->index >= msj->longitud && msj->repetir_msj)
    msj->index = 0;
}

void concatenarLetraMensaje(char c, mensaje_t *msj)
{
  if (msj->index == L_MAX - 1)
    return;

  (msj->msj)[msj->index++] = c;
  (msj->msj)[msj->index] = 'A';
  (msj->msj)[msj->index + 1] = '\0';
  msj->longitud++;

  msj->j += getLongitud(c) + 1;
  while (CANT_COLUMNAS - msj->j-- - ANCHO_MAXIMO < 0) // corro a la izquierda hasta asegurarme que va a entrar cualquier letra
    renglonShiftIzq(msj->renglon, 1);

  renglon_t letra;
  charARenglon('A', letra);
  renglonShiftDer(letra, msj->j);
  renglonOr(msj->renglon, letra);
}

void reemplazarUltLetraMensaje(char c, mensaje_t *msj)
{
  (msj->msj)[msj->index] = c;
  reemplazarLetra(msj->renglon, c, msj->j);
}

/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int getLongitud(char c)
{
  if (c == ' ' || !c)
    return longitudes[INDEX_ESPACIO];
  else if ('0' <= c && c <= '9')
    return longitudes[INDEX_CERO + c - '0'];
  else if ('A' <= c && c <= 'Z')
    return longitudes[c - 'A'];
  else
    return longitudes[INDEX_FULL];
}