/**
 * @file input.c
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

#include "../../input.h"

#include "allegro_stuff.h"
#include "entities.h"
#include "game_data.h"


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

static ALLEGRO_EVENT* event;

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
	//bool queue_no_empty;

	event = allegro_get_next_event();
	int i;

	if(event != NULL)
	{
		switch ((*event).type)
		{
			case ALLEGRO_EVENT_TIMER:
				allegro_set_var_redraw(true);

				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				last_key = allegro_get_last_key();

				if(last_key != (*event).keyboard.keycode)
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

						case ALLEGRO_KEY_8:
							break;

						case ALLEGRO_KEY_9:
							break;

						case ALLEGRO_KEY_PAD_1:
							game_data_add_score();
							break;

						case ALLEGRO_KEY_PAD_2:
							retorno = GAME_OVER;
							break;

						case ALLEGRO_KEY_PAD_3:
							//int i;
							for(i = 0; i < MAX_GOALS; i++)
								game_data_set_goal(i);
							break;

						case ALLEGRO_KEY_PAD_4:
							game_data_reset_goals();
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

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 