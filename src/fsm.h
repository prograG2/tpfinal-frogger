/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _FSM_H_
#define _FSM_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"
#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FIN_TABLA 0xFF

#define CTE_OPCION 100

#define JUGADOR_CLOCKS (clock_t)CLOCKS_PER_SEC*0.5
#define REFRESH_AUTOS_CLOCKS (clock_t)CLOCKS_PER_SEC*2
#define REFRESH_JUGADOR_CLOCKS (clock_t)CLOCKS_PER_SEC


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/**
 * @brief 
 * 
 */
typedef struct state_diagram_edge STATE;

/**
 * @brief Estructura genérica de un estado de la FSM.
 * 
 */
struct state_diagram_edge
{
	event_t evento;
	STATE *proximo_estado;
	void (*p_rut_accion)(void);
};


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Devuelve el estado inicial de la FSM.
 * 
 * @return STATE* Puntero al estado inicial.
 */

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