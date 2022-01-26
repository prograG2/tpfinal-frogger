/**
 * @file display.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <pthread.h>
#include "queue.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

enum posiciones_mensajes{POS_MSJ_MENU, POS_MSJ_DIFICULTAD, POS_MSJ_RANKING, POS_MSJ_NOMBRE, POS_MSJ_PASAR, POS_MSJ_PAUSA, POS_MSJ_NEW_HI_SCORE, POS_MSJ_GAME_OVER};


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

/**
 * @brief 
 * 
 * @return int 
 */
int iniciarDisplay();

/**
 * @brief 
 * 
 */
void actualizarDisplay();

/**
 * @brief 
 * 
 */
void limpiarDisplay();

/**
 * @brief 
 * 
 * @param txt 
 * @param pos 
 */
void mostrarTexto(char* txt, int pos);

/**
 * @brief 
 * 
 * @param txt 
 * @param pos 
 */
void fijarTexto(char* txt, int pos);

/**
 * @brief 
 * 
 * @param posicion 
 * @param nombre 
 * @param puntos 
 */
void mostrarPosicion(char* posicion, char* nombre, char* puntos);

/**
 * @brief Construct a new reconfigurar Display object
 * 
 */
void reconfigurarDisplayON(void);

/**
 * @brief 
 * 
 */
void reconfigurarDisplayOFF(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _DISPLAY_H_
