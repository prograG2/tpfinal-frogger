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

#include <stdbool.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

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
 * @brief Agrega score por llegar a la meta
 * 
 */
void game_data_add_score(void);

/**
 * @brief Agrega score por llegar a la meta con bonus (coins)
 * 
 */
void game_data_add_score_bonus(void);

/**
 * @brief Carga el score maximo del jugador actual
 * 
 * @param score 
 */
void game_data_set_score_max(int score);

/**
 * @brief Devuelve el score maximo del jugador actual
 * 
 * @return int Score maximo
 */
int game_data_get_score_max(void);

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
 * @brief Agrega tiempo a la run por llegar a una meta
 * 
 */
void game_data_add_run_time_goal(void);

/**
 * @brief Agrega tiempo (más) a la run por llegar a una meta con coin
 * 
 */
void game_data_add_run_time_goal_bonus(void);

/**
 * @brief Devuelve los frames transcurridos del juego
 * 
 * @return unsigned long Frames transcurridos
 */
unsigned long game_data_get_frames(void);

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
 * @brief Devuelve dificultad
 * 
 * @return int 
 */
int game_data_get_diff(void);
/**
 * @brief Limpia el nombre del jugador
 * 
 */
void game_data_clear_name(void);

/**
 * @brief Sobreescribe el nombre del jugador
 * 
 * @param name 
 */
void game_data_overwrite_name(char* name);

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
char *game_data_get_name(void);

/**
 * @brief Revisa si un punto de llegada es valido o no (vacio o lleno)
 * 
 * @param goal 0 a MAX_GOALS-1
 * @return true Invalido
 * @return false Valido
 */
bool game_data_get_goal_state(unsigned int goal);

/**
 * @brief Setea un goal como completado
 * 
 * @param goal 0 a MAX_GOALS-1
 */
void game_data_set_goal(unsigned int goal);

/**
 * @brief Habilita todos los goals
 * 
 */
void game_data_reset_goals(void);

/**
 * @brief Avisa si se excedio el tiempo de juego
 * 
 * @return true Excedido
 * @return false No excedido
 */
bool game_data_get_time_left_flag(void);

/**
 * @brief Devuelve flag de game over
 * 
 * @return true Game over
 * @return false No game over
 */
bool game_data_get_game_over_flag(void);

/**
 * @brief Avisa si estan todas las metas completas
 * 
 * @return true Si
 * @return false No
 */
bool game_data_are_goals_full(void);

/**
 * @brief Devuelve el score maximo sin actualizar al terminar el juego
 * 
 * @return int 
 */
int game_data_get_old_max_score(void);



/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_DATA_H_
