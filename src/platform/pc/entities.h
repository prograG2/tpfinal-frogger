/**
 * @file 	entities.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo entities. Prototipos de funciones globales
 * 			para el manejo de entidades.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _ENTITIES_H_
#define _ENTITIES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa las entidades
 *
 */
void entities_init(void);

/**
 * @brief Actualiza las entidades
 *
 */
void entities_update(void);

/**
 * @brief Dibuja las entidades
 *
 */
void entities_draw(void);

/**
 * @brief Indica que la rana debe dar un salto en la direccion dada
 *
 * @param direction enum DIRECTIONS
 */
void entities_move_frog(unsigned char direction);

/**
 * @brief Setea el estado del flag tutorial
 * 
 */
void entities_set_tutorial(void);

/**
 * @brief Indica el estado del flag tutorial
 * 
 * @return true Tutorial done
 * @return false Playing tutorial
 */
bool entities_get_tutorial(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _ENTITIES_H_
