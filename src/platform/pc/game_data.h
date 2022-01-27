/**
 * @file game_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_NAME_CHAR		20

#define MAX_LIVES           3

#define SCORE_PER_GOAL		500		//puntaje por llegar a la meta
#define SCORE_PER_GOAL_FLY	750		//puntaje por llegar a la meta con mosca
#define SCORE_PER_RUN		1000	//puntaje por completar una run

enum DIFFICULTIES
{
	DIFFICULTIES_EASY = 1,
	DIFFICULTIES_NORMAL,
	DIFFICULTIES_HARD
};


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
 * @brief Inicializa datos internos del juego 
 * 
 */
void game_data_init(void);

/**
 * @brief Actualiza datos internos del juego
 * 
 */
void game_data_update(void);

/**
 * @brief Grafica datos del juego (HUD pricipalmente)
 * 
 */
void game_data_draw(void);

/**
 * @brief Devuelve vidas
 * 
 * @return int vidas
 */
int game_data_get_lives(void);

/**
 * @brief Resta una vida
 * 
 */
void game_data_subtract_live(void);

/**
 * @brief Devuelve score
 * 
 * @return int 
 */
int game_data_get_score(void);

/**
 * @brief Agrega un valor al score actual
 * 
 * @param add Valor a agregar. Si es negativo, no agrega.
 */
void game_data_add_score(int add);

/**
 * @brief Devuelve el numero de run
 * 
 * @return int Numero de run
 */
int game_data_get_run_number(void);

/**
 * @brief Indica que se pase a la siguiente run
 * 
 */
void game_data_next_run(void);

/**
 * @brief Devuelve el tiempo restante de la run en segundos
 * 
 * @return int Tiempo restante
 */
int game_data_get_run_time_left(void);

/**
 * @brief Devuelve los frames transcurridos del juego
 * 
 * @return long Frames transcurridos
 */
long game_data_get_frames(void);

/**
 * @brief Devuelve el tiempo transcurrido en segundos
 * 
 * @return int Segundos transcurridos
 */
int game_data_get_timer_in_sec(void);

/**
 * @brief Setea dificultad 
 * 
 * @param diff enum DIFFICULTIES
 */
void game_data_set_diff(int diff);

/**
 * @brief Limpia el nombre del jugador
 * 
 */
void game_data_clear_name(void);

/**
 * @brief Agrega una letra la nombre del jugador
 * 
 * @param letter Letra
 */
void game_data_add_name_letter(char letter);

/**
 * @brief Devuelve puntero al nombre del jugador
 * 
 * @return char* 
 */
const char *game_data_get_name(void);



/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_DATA_H_
