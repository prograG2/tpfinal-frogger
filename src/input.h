/**
 * @file 	input.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * 			
 * @brief 	Header del modulo input
 * 			Vinculo entre la fsm y las plataformas en lo que respecta
 * 			al manejo de acciones externas
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _INPUT_H_
#define _INPUT_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"

#include <stdbool.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa las entradas de la plataforma
 * 
 * 
 */
void iniciarEntradas(void);

/**
 * @brief Devuelve una entrada válida
 * 
 * @return event_t enum eventos_tecla
 */
event_t leerEntradas(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _INPUT_H_
