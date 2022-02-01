/**
 * @file game.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../game.h"
#include "../../menu.h"
#include "../../queue.h"
#include "../../sound.h"

#include "game_data.h"
#include "entities.h"
#include "allegro_stuff.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static bool next_run_flag = false;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setNombre(char* nombre)
{
	game_data_overwrite_name(nombre);
}

void setMaxPuntos(uint64_t max)
{
	game_data_set_score_max(max);
}

void setDificultad(int diff)				
{
	switch (diff)
	{
		case 0:
			game_data_set_diff(DIFFICULTIES_EASY);
			break;

		case 1:
			game_data_set_diff(DIFFICULTIES_NORMAL);
			break;
			
		case 2:
			game_data_set_diff(DIFFICULTIES_HARD);

		default:
			break;
	}
}

bool tiempoRefrescoEntidades(void)
{
	return allegro_get_var_redraw();
}

bool tiempoLimite(void)
{
	return game_data_get_time_left_flag();
}


char* getNombre(void)
{
	return game_data_get_name();
}

uint64_t getPuntos(void)
{
	return game_data_get_score();
}

uint64_t getMaxPuntos(void)
{
	return game_data_get_score_max();
}

int getNivel(void)
{
	return game_data_get_run_number();
}

void inicializarJuego(void)
{
	game_data_init();
	entities_init();

	allegro_clear_display();
	al_flip_display();

}

void pausarJuego(void)
{

}

void reiniciarNivel(void)
{
	if(next_run_flag)
	{
		game_data_next_run();
		next_run_flag = false;
	}
}

void refrescar(void)
{
	game_data_update();
	entities_update();

	if(game_data_are_goals_full())
	{
		next_run_flag = true;

		reproducirEfecto(EFECTO_NIVEL_COMPLETO);
		reiniciarNivel();
	}

	if(game_data_get_game_over_flag())
		queueInsertar(GAME_OVER);
}

void moverAdelante(void)
{
	entities_move_frog(DIRECTION_UP);
}

void moverAtras(void)
{
	entities_move_frog(DIRECTION_DOWN);
}

void moverIzda(void)
{
	entities_move_frog(DIRECTION_LEFT);
}

void moverDcha(void)
{
	entities_move_frog(DIRECTION_RIGHT);
}

void respawn(void)
{

}


void actualizarInterfaz(void)
{
	if(allegro_get_last_key() == ALLEGRO_KEY_8 && !allegro_get_rick_flag())
	{
		allegro_rick_on();
		allegro_set_rick_flag(true);	
	}
	
	if(allegro_get_last_key() == ALLEGRO_KEY_9 && allegro_get_rick_flag())
	{
		allegro_rick_off();
		allegro_set_rick_flag(false);
	}

	if(allegro_get_var_redraw())
	{
		allegro_clear_display();
		allegro_draw_background();

		if(allegro_get_rick_flag())
			allegro_rick_draw();

		entities_draw();
		game_data_draw();

		al_flip_display();

		allegro_set_var_redraw(false);
	}
	
}

void imprimirMapa(void)
{
	
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 