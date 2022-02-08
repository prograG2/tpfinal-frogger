/**
 * @file 	game.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo game, orientado a PC. Vincula la FSM con lo
 * 			específico de PC en lo relacionado a la interacción con el juego.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
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
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static bool next_run_flag = false;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setNombre(char *nombre)
{
	game_data_overwrite_name(nombre);
}

void setMaxPuntos(unsigned long long max)
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

char *getNombre(void)
{
	return game_data_get_name();
}

unsigned long long getPuntos(void)
{
	return game_data_get_score();
}

unsigned long long getMaxPuntos(void)
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
	if (next_run_flag)
	{
		game_data_next_run();
		next_run_flag = false;
	}
}

void refrescar(void)
{
	game_data_update();
	entities_update();

	if (game_data_are_goals_full())
	{
		next_run_flag = true;

		reproducirEfecto(EFECTO_NIVEL_COMPLETO);
		reiniciarNivel();
	}

	if (game_data_get_game_over_flag())
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
	

	if (allegro_get_last_key() == ALLEGRO_KEY_8 && !allegro_get_rick_flag())
	{
		allegro_rick_on();
		allegro_set_rick_flag(true);
	}

	if (allegro_get_last_key() == ALLEGRO_KEY_9 && allegro_get_rick_flag())
	{
		allegro_rick_off();
		allegro_set_rick_flag(false);
	}

	if (allegro_get_var_redraw())
	{
		allegro_clear_display();
		allegro_draw_background();

		if (allegro_get_rick_flag())
			allegro_rick_draw();

		entities_draw();
		game_data_draw();

		al_draw_bitmap(sprites.border, SPRITE_BORDER_START_X, SPRITE_BORDER_START_Y, 0);

		if(!entities_get_tutorial()){
				al_draw_bitmap(sprites.tutorial, 0, 0, 0);
			}
		if(!entities_get_tutorial() && allegro_get_last_key() == ALLEGRO_KEY_SPACE){
				entities_set_tutorial();
			}

		al_flip_display();

		allegro_set_var_redraw(false);
	}
}

void reanudarJuego(void)
{
}