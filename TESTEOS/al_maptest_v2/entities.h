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

#define MAX_LIVES   3

#define MAX_CARS    10

#define MAX_LOGS    10
#define MAX_LOGS_ON_SCREEN  5
#define LOGS_BASE_SPEED     1


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
 * @brief Inicializa la rana
 * 
 */
void frog_init(void);

/**
 * @brief Actualiza posicionamiento de la rana
 * 
 */
void frog_update(void);

/**
 * @brief Dibuja la rana
 * 
 */
void frog_draw(void);

/**
 * @brief Inicializa troncos
 * 
 */
void logs_init(void);

/**
 * @brief Actualiza troncos
 * 
 */
void logs_update(void);

/**
 * @brief Dibuja troncos
 * 
 */
void logs_draw(void);

/**
 * @brief Devuelve coordenada x topleft de rana
 * 
 * @return int Coordenada x
 */
int frog_get_x(void);

/**
 * @brief Devuelve coordenada y topleft de rana
 * 
 * @return int Coordenada y
 */
int frog_get_y(void);

/**
 * @brief Devuelve coordenada x topleft del tronco i
 * 
 * @param i Número de tronco
 * @return int Coordenada x
 */
int log_get_x(int i);

/**
 * @brief Devuelve coordenada y topleft del tronco i
 * 
 * @param i Número de tronco
 * @return int Coordenada y
 */
int log_get_y(int i);




/*******************************************************************************
 ******************************************************************************/

#endif // _ENTITIES_H_
