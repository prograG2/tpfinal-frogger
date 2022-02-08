/**
 * @file 	input.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo input, orientado a PC. Se encarga de procesar
 * 			las entradas en la implementación de PC, y devolverlas adecuadamente
 * 			a la FSM.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../input.h"

#include "allegro_stuff.h"
#include "entities.h"
#include "game_data.h"

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static ALLEGRO_EVENT *event;

static unsigned char last_key;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void iniciarEntradas(void)
{
}

event_t leerEntradas(void)
{
	event_t retorno = NO_MOVER;
	// bool queue_no_empty;

	event = allegro_get_next_event();

	if (event != NULL)
	{
		switch ((*event).type)
		{
		case ALLEGRO_EVENT_TIMER:
			allegro_set_var_redraw(true);
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			last_key = allegro_get_last_key();

			if (last_key != (*event).keyboard.keycode)
			{
				retorno = (*event).keyboard.keycode;
				allegro_set_last_key(retorno);

				switch (retorno)
				{
				case ALLEGRO_KEY_F2:
					allegro_sound_set_stream_gain_up();
					break;

				case ALLEGRO_KEY_F1:
					allegro_sound_set_stream_gain_down();
					break;

				case ALLEGRO_KEY_2:
					allegro_sound_unmute();
					break;

				case ALLEGRO_KEY_1:
					allegro_sound_mute();
					break;

				case ALLEGRO_KEY_4:
					game_data_add_score();
					break;

				case ALLEGRO_KEY_5:
					game_data_add_run_time_goal();
					break;

				case ALLEGRO_KEY_6:
					retorno = GAME_OVER;
					break;

				default:
					break;
				}
			}

			break;

		case ALLEGRO_EVENT_KEY_UP:
			allegro_set_last_key(0);

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			retorno = FORCE_SALIR;
			break;

		default:
			break;
		}
	}

	return retorno;
}