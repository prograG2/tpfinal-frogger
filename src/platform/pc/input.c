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

static ALLEGRO_EVENT_TYPE event;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int iniciarEntradas(void)
{
	return 1;
}

event_t leerEntradas(void)
{
	event_t retorno = NO_MOVER;
	//bool queue_no_empty;

	event = allegro_get_next_event();

	if(event)
	{
		switch (event)
		{
			case ALLEGRO_EVENT_TIMER:

				break;

			default:
				break;
		}

		//actualiza teclado
		keyboard_update();
		
		//NO_MOVER = -1, ESC = 59, BORRAR = 63, ENTER = 67, IZDA = 82, DCHA, ARRIBA, ABAJO

		if(CHECK_KEY(ALLEGRO_KEY_ESCAPE))
			retorno = ESC;
		else if(CHECK_KEY(ALLEGRO_KEY_ENTER))
			retorno = ENTER;
		else if(CHECK_KEY(ALLEGRO_KEY_LEFT))
			retorno = IZDA;
		else if(CHECK_KEY(ALLEGRO_KEY_RIGHT))
			retorno = DCHA;
		else if(CHECK_KEY(ALLEGRO_KEY_UP))
			retorno = ARRIBA;
		else if(CHECK_KEY(ALLEGRO_KEY_DOWN))
			retorno = ABAJO;
		else if(CHECK_KEY(ALLEGRO_KEY_BACKSPACE))
		{
			retorno = BORRAR;
			save_keyboard_state();
		}
		else
		{
			int i;
			for(i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_Z; i++)
			{
				if(CHECK_KEY(i))
				{
					retorno = i;
					save_keyboard_state();

					break;
				}
			}
		}
			

	
		
	}
	
	return retorno;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 