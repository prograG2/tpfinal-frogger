/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/
//https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
#ifndef _QUEUE_H_
#define _QUEUE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef int event_t;

enum eventos{NADA = -1, SALIR = 0, GAME_OVER, FORCE_SALIR};
enum eventos_tecla{NO_MOVER = -1, ESC = 59, BORRAR = 63, ENTER = 67, IZDA = 82, DCHA, ARRIBA, ABAJO}; //Se respetan las definiciones de ALLEGRO ¡Chequear si se cambió la versión!

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief 
 * 
 */
void queueInsertar(event_t);

/**
 * @brief 
 * 
 * @return int 
 */
int queueVacia();

/**
 * @brief 
 * 
 * @return event_t 
 */
event_t queueSiguienteEvento();

/**
 * @brief 
 * 
 */
void destruirQueue();

/*******************************************************************************
 ******************************************************************************/

#endif // _QUEUE_H_
