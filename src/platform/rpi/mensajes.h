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
 * @brief 
 * 
 * @param r 
 */
void printRenglon(Renglon r);

/**
 * @brief 
 * 
 * @param r1 
 * @param r2 
 */
void printRenglonDoble(Renglon r1, Renglon r2);

/**
 * @brief 
 * 
 * @param r 
 */
void borrarRenglon(Renglon r);

/**
 * @brief 
 * 
 * @param r 
 * @param s 
 */
void renglonShiftDer(Renglon r, uint16_t s);

/**
 * @brief 
 * 
 * @param r 
 * @param s 
 */
void renglonShiftIzq(Renglon r, uint16_t s);

/**
 * @brief 
 * 
 * @param r 
 * @param s 
 */
void renglonOr(Renglon r, Renglon s);

/**
 * @brief 
 * 
 * @param r 
 * @param s 
 */
void renglonAnd(Renglon r, Renglon s);

/**
 * @brief 
 * 
 * @param r 
 */
void renglonNot(Renglon r);

/**
 * @brief 
 * 
 * @param r1 
 * @param r2 
 * @param s 
 */
void renglonDobleShiftDer(Renglon r1, Renglon r2, unsigned int s);

/**
 * @brief 
 * 
 * @param r1 
 * @param r2 
 * @param s 
 */
void renglonDobleShiftIzq(Renglon r1, Renglon r2, unsigned int s);

/**
 * @brief 
 * 
 * @param r1 
 * @param r2 
 */
void copiarRenglon(Renglon r1, Renglon r2);

/**
 * @brief 
 * 
 * @param m
 * @param r 
 * @param pos
 */
void copiarMatrizRenglon(Matriz m, Renglon r, int pos);

/**
 * @brief 
 * 
 * @param r 
 * @return int 
 */
int renglonBool(Renglon r);

/**
 * @brief 
 * 
 * @param c 
 * @param r 
 */
void CharARenglon(char c, Renglon r);

/**
 * @brief 
 * 
 * @param n 
 * @param r 
 */
void uintARenglon(uint16_t n, Renglon r); //copia un número a renglon hasta que se acabe el número o el renglon (lo 1 q ocurra)

/**
 * @brief 
 * 
 * @param r 
 * @param c 
 * @param j 
 */
void reemplazarLetra(Renglon r, char c, int j);

/**
 * @brief 
 * 
 * @param msj 
 * @param pos 
 * @return mensaje_t 
 */
mensaje_t mensaje(char* msj, int pos);

/**
 * @brief 
 * 
 * @param msj 
 * @param repetir 
 */
void moverMensaje(mensaje_t* msj, int repetir);

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
