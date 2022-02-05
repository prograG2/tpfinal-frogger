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

/*******************************************************************************
 ******************************************************************************/

#endif // _ENTITIES_H_
