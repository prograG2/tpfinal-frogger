/**
 * @file mensajes.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _MENSAJES_H_
#define _MENSAJES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "rpiconsts.h"
#include "bitmap.h"

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MOVER_TEXTO 1
#define NO_MOVER_TEXTO 0
#define TAM_RENGLON 5
#define NO_REPETIR 0
#define REPETIR 1

#define POS_MSJ1 2
#define POS_MSJ2 9


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint16_t Renglon[TAM_RENGLON];

typedef struct Mensaje{
    char msj[L_MAX];
    int posicion;
    int index;
    int index_inicio;
    int j_inicio;
    int longitud;
    int mover;
    Renglon renglon;
    Renglon reserva;
    Renglon renglon_inicio;
    Renglon reserva_inicio;
} mensaje_t;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief imprime Renglon en consola (para debuggear)
 * 
 * @param r Renglon a imprimir
 */
void printRenglon(Renglon r);

/**
 * @brief imprime dos variables Renglon en consola en forma contigua (para debuggear)
 * 
 * @param r1 Renglon izquierdo
 * @param r2 Renglon derecho
 */
void printRenglonDoble(Renglon r1, Renglon r2);

/**
 * @brief elimina el contenido del Renglon
 * 
 * @param r Renglon a limpiar
 */
void borrarRenglon(Renglon r);

/**
 * @brief Desplaza a la derecha el contenido de un Renglon 
 * 
 * @param r Renglon a desplazar
 * @param s cantidad de espacios
 */
void renglonShiftDer(Renglon r, uint16_t s);

/**
 * @brief Desplaza a la izquierda el contenido de un Renglon
 * 
 * @param r Renglon a desplazar
 * @param s cantidad de espacios
 */
void renglonShiftIzq(Renglon r, uint16_t s);

/**
 * @brief Se ejecuta la operación "r |= s"
 * 
 * @param r primer operando OR
 * @param s segundo operando OR
 */
void renglonOr(Renglon r, Renglon s);

/**
 * @brief Se ejecuta la operación "r &= s"
 * 
 * @param r primer operando AND
 * @param s segundo operando AND
 */
void renglonAnd(Renglon r, Renglon s);

/**
 * @brief Se invierte el contenido del Renglon (se obtiene el complemento)
 * 
 * @param r Renglon a invertir
 */
void renglonNot(Renglon r);

/**
 * @brief Desplaza a la derecha el contenido de dos renglones en forma conjunta ("r1:r2 >>= s")
 * 
 * @param r1 Renglon izquierdo
 * @param r2 Renglon derecho
 * @param s cantidad de espacios
 */
void renglonDobleShiftDer(Renglon r1, Renglon r2, unsigned int s);

/**
 * @brief Desplaza a la izquierda el contenido de dos renglones en forma conjunta ("r1:r2 <<= s")
 * 
 * @param r1 Renglon izquierdo
 * @param r2 Renglon derecho
 * @param s cantidad de espacios
 */
void renglonDobleShiftIzq(Renglon r1, Renglon r2, unsigned int s);

/**
 * @brief copia el contenido de r1 en r2
 * 
 * @param r1 Renglon origen
 * @param r2 Renglon destino
 */
void copiarRenglon(Renglon r1, Renglon r2);

/**
 * @brief copia un Renglon sobre una Matriz a partir de una fila especificada
 * 
 * @param m Matriz destino
 * @param r Renglon origen
 * @param pos Fila de inicio
 */
void copiarMatrizRenglon(Matriz m, Renglon r, int pos);

/**
 * @brief indica si el Renglon tiene contenido
 * 
 * @param r Renglon a chequear
 * @return true Renglon con contenido
 * @return false Renglon vacío
 */
bool renglonBool(Renglon r);

/**
 * @brief Convierte un caracter a Renglon, ubicándolo en el extremo izquierdo del Renglon
 * 
 * @param c caracter
 * @param r Renglon
 */
void CharARenglon(char c, Renglon r);

/**
 * @brief Convierte un entero no signado a Renglon, ubicándolo en el extremo izquierdo del renglon
 * 
 * @param n entero no signado de 16 bits
 * @param r Renglon
 */
void uintARenglon(uint16_t n, Renglon r); //copia un número a renglon hasta que se acabe el número o el renglon (lo 1 q ocurra)

/**
 * @brief (re)escribe sobre el Renglon un caracter dado a partir de la columna j
 * 
 * @param r Renglon
 * @param c caracter
 * @param j columna sobre la que se quiere escribir
 */
void reemplazarLetra(Renglon r, char c, int j);

/**
 * @brief constructor de la variable mensaje_t
 * 
 * @param msj String que se desea convertir a mensaje
 * @param pos fila sobre la que se deberá mostrar en display
 * @return mensaje_t 
 */
mensaje_t mensaje(char* msj, int pos);

/**
 * @brief desplaza el contenido del Renglon doble hacia la izquierda
 * 
 * @param msj puntero a la variable mensaje_t
 * @param repetir Indica si es necesario volver a pasar el contenido del mensaje tras haberlo hecho una vez
 */
void moverMensaje(mensaje_t* msj, int repetir);

/**
 * @brief 
 * 
 * @param msj
 */
void reiniciarMensaje(mensaje_t* msj);

/**
 * @brief Get the Longitud object
 * 
 * @param a 
 * @return int 
 */
int getLongitud(char a);


/*******************************************************************************
 ******************************************************************************/

#endif // _MENSAJES_H_
