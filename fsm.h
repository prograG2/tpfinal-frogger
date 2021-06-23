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
enum eventos{SALIR = 0, ARRIBA, ABAJO, IZDA, DCHA, ENTER, BORRAR, ESC, LISTO, REFRESH};

typedef unsigned char event_t;

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
extern STATE* p2CurrentState;

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
 * @brief Devuelve el estado actual de la FSM.
 * 
 * @return STATE* Puntero al estado actual.
 */
STATE* fsm_getCurrentState(void);

/**
 * @brief Intérprete de la FSM. Se encarga de hacer correr la FSM a partir de un estado y evento dados.
 * 
 * @param p_tabla_estado Estado actual.
 * @param evento_actual Evento recibido.
 * @return STATE* Puntero al siguiente estado.
 */
STATE* fsm(STATE *p_tabla_estado, event_t evento_actual);


/*******************************************************************************
 ******************************************************************************/

#endif // _FSM_H_
