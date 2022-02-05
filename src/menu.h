/**
 * @file 	game.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo genérico menu.
 * 			Prototipos de funciones de interaccion con el menu del juego.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _MENU_H_
#define _MENU_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum textos_menu
{
	JUGAR = 0,
	DIFICULTAD,
	RANKING,
	CREDITOS,
	SALIRTXT,
	CONTINUAR,
	REINICIAR,
	FACIL,
	NORMAL,
	DIFICIL
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicia el menu
 *
 */
void iniciarMenu(void);

/**
 * @brief Destruye del menu
 *
 */
void destruirMenu(void);

/**
 * @brief Selecciona un menu
 *
 * @param a Puntero a textos del menu
 * @param size Opciones del menu
 */
void setMenu(int *a, unsigned int size);

/**
 * @brief Selecciona una opcion del menu
 *
 * @param opc Opcion a seleccionar
 */
void setOpcion(int opc);

/**
 * @brief Devuelve la opcion actual del menu
 *
 * @return int Opcion seleccionada actualmente
 */
int getOpcion(void);

/**
 * @brief Selecciona la opcion superior a la actual
 *
 */
void subirOpcion(void);

/**
 * @brief Selecciona la opcion inferior a la actual
 *
 */
void bajarOpcion(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _MENU_H_
