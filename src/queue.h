/**
 * @file 	queue.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo queue.
 * 			Prototipos de funciones de interaccion con la cola de eventos.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

// https://stackoverflow.com/questions/3536153/c-dynamically-growing-array

#ifndef _QUEUE_H_
#define _QUEUE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Tipo de dato para eventos
typedef int event_t;

// Eventos posibles principales
enum eventos
{
    NADA = -1,
    SALIR = 0,
    GAME_OVER,
    FORCE_SALIR
};

// Eventos posibles de interacción en el juego
enum eventos_tecla
{
    NO_MOVER = -1,
    ESC = 59,
    BORRAR = 63,
    ENTER = 67,
    IZDA = 82,
    DCHA,
    ARRIBA,
    ABAJO
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Agrega un evento a la cola
 *
 */
void queueInsertar(event_t);

/**
 * @brief Chequea si la cola está vacía
 *
 * @return true Vacía
 * @return false No vacía
 */
bool queueVacia(void);

/**
 * @brief Devuelve el siguiente evento de la cola
 *
 * @return event_t
 */
event_t queueSiguienteEvento(void);

/**
 * @brief Destruye la cola de eventos
 *
 */
void destruirQueue(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _QUEUE_H_
