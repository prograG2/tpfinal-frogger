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

#define TAM_RENGLON 5

#define POS_MSJ1 2
#define POS_MSJ2 9
#define POS_MSJ3 5


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef union{
    uint32_t completo;
    struct{
        uint16_t mitad_der;
        uint16_t mitad_izq;
    };
}renglon_t[5];

typedef struct Mensaje{
    char msj[L_MAX];
    int posicion;
    int index;
    int longitud;
    int j;
    bool habilitacion;
    bool mover_texto;
    bool repetir_msj;
    renglon_t renglon;
} mensaje_t;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief imprime dos renglon en consola (para debuggear)
 * 
 * @param r renglon a imprimir
 */
void printRenglon(renglon_t r);

/**
 * @brief elimina el contenido del Renglon
 * 
 * @param r Renglon a limpiar
 */
void borrarRenglon(renglon_t r);

/**
 * @brief Desplaza a la derecha el contenido de un Renglon 
 * 
 * @param r Renglon a desplazar
 * @param s cantidad de espacios
 */
void renglonShiftDer(renglon_t r, uint16_t s);

/**
 * @brief Desplaza a la izquierda el contenido de un Renglon
 * 
 * @param r Renglon a desplazar
 * @param s cantidad de espacios
 */
void renglonShiftIzq(renglon_t r, uint16_t s);

/**
 * @brief Se ejecuta la operación "r |= s"
 * 
 * @param r primer operando OR
 * @param s segundo operando OR
 */
void renglonOr(renglon_t r, renglon_t s);

/**
 * @brief Se ejecuta la operación "r &= s"
 * 
 * @param r primer operando AND
 * @param s segundo operando AND
 */
void renglonAnd(renglon_t r, renglon_t s);

/**
 * @brief Se invierte el contenido del Renglon (se obtiene el complemento)
 * 
 * @param r Renglon a invertir
 */
void renglonNot(renglon_t r);

/**
 * @brief copia el contenido de r1 en r2
 * 
 * @param r1 Renglon origen
 * @param r2 Renglon destino
 */
void copiarRenglon(renglon_t r1, renglon_t r2);

/**
 * @brief copia un Renglon sobre una Matriz a partir de una fila especificada
 * 
 * @param m Matriz destino
 * @param r Renglon origen
 * @param pos Fila de inicio
 */
void copiarMatrizRenglon(matriz_t m, renglon_t r, int pos);

/**
 * @brief indica si la parte izquierda del renglón está vacía
 * 
 * @param r Renglon a chequear
 * @return true
 * @return false
 */
bool renglonIzquierdoLibre(mensaje_t *msj);

/**
 * @brief Convierte un caracter a Renglon, ubicándolo en el extremo izquierdo del Renglon
 * 
 * @param c caracter
 * @param r Renglon
 */
void charARenglon(char c, renglon_t r);

/**
 * @brief Convierte un caracter a Renglon, ubicándolo en el extremo izquierdo del Renglon
 * 
 * @param c caracter
 * @param m Matriz
 * @param x
 * @param y
 */

void charAMatriz(char c, matriz_t m, const int coord[]);

/**
 * @brief Convierte un entero no signado a Renglon, ubicándolo en el extremo izquierdo del renglon
 * 
 * @param n entero no signado de 16 bits
 * @param r Renglon
 */
void uintARenglon(uint16_t n, renglon_t r); //copia un número a renglon hasta que se acabe el número o el renglon (lo 1 q ocurra)

/**
 * @brief (re)escribe sobre el Renglon un caracter dado a partir de la columna j
 * 
 * @param r Renglon
 * @param c caracter
 * @param j columna sobre la que se quiere escribir
 */
void reemplazarLetra(renglon_t r, char c, int j);

/**
 * @brief constructor de la variable mensaje_t
 * 
 * @param msj String que se desea convertir a mensaje
 * @param pos fila sobre la que se deberá mostrar en display
 * @param repetir si se repetirá una vez terminado de mostrar
 * @return mensaje_t 
 */
mensaje_t mensaje(char* msj, int pos, bool repetir);

/**
 * @brief desplaza el contenido del Renglon doble hacia la izquierda
 * 
 * @param msj puntero a la variable mensaje_t
 */
void moverMensaje(mensaje_t* msj);

void concatenarLetraMensaje(char c, mensaje_t *msj);

void reemplazarUltLetraMensaje(char c, mensaje_t *msj);

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
