/**
 * @file entities.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _ENTITIES_H_
#define _ENTITIES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MAX_CARS            10
#define MAX_LOGS            10
#define CARS_TYPES          1
#define MAX_TURTLE_PACKS    4 


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

/*******************************************************************************
 ******************************************************************************/

#endif // _ENTITIES_H_
