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
#include "global.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FIN_TABLA 0xFF


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/**
 * @brief Eventos posibles.
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

//Puntero al estado actual, presente en main.c
STATE* p2CurrentState;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Devuelve el estado inicial de la FSM.
 * 
 * @return STATE* Puntero al estado inicial.
 */
STATE* fsm_getInitState(void);

/**
 * @brief Intérprete de la FSM. Se encarga de hacer correr la FSM a partir de un estado y evento dados.
 * 
 * @param p_tabla_estado Estado actual.
 * @param evento_actual Evento recibido.
 * @return STATE* Puntero al siguiente estado.
 */
STATE* fsm(STATE *p_tabla_estado, event_t evento_actual);

extern STATE en_menu_ppal[];
extern STATE menu_ppal_esperando_opcion[];
extern STATE en_dificultad[];


extern STATE viendo_ranking[];
extern STATE poniendo_nombre[];
extern STATE jugando[];
extern STATE en_pausa[];
extern STATE en_pausa_esperando_opcion[];
extern STATE en_game_over[];
extern STATE en_game_over_esperando_opcion[];


/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_H_
