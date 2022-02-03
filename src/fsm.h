/**
 * @file 	fsm.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * 			
 * @brief 	Header del modulo fsm.
 * 			Contiene los prototipos de funciones necesarias para iniciar la
 * 			fsm desde main.c
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _FSM_H_
#define _FSM_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"
#include <stdbool.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa la FSM, notificando si tuvo exito
 *
 * @return true Exito
 * @return false Error
 */
bool inicializarFsm(void);

/**
 * @brief Intérprete de la FSM. Se encarga de hacer correr la FSM a partir de un estado y evento dados.
 *
 * @param p_tabla_estado Estado actual.
 * @param evento_actual Evento recibido.
 */
void fsm(event_t evento_actual);

/**
 * @brief Fixea consumo elevado de cpu en el while loop principal
 *
 * Not the best solucion, but sirve...
 *
 * https://softwareengineering.stackexchange.com/questions/256524/infinite-while-loop-cpu-usage
 *
 */
void fixHighCpuUsage(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_H_