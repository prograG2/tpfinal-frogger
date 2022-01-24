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

static ALLEGRO_EVENT event;


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
	event_t retorno;
	bool queue_no_empty;

	queue_no_empty = al_get_next_event(allegro_get_event_queue(), &event);
	/*if(queue_no_empty)
	{
		allegro_set_var_event(event);

		
		switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                
                //si es 'escape', avisa para cerrar la ventana
                if(CHECK_KEY(ALLEGRO_KEY_ESCAPE))
                    allegro_set_var_done(true);     
                
                if(CHECK_KEY(ALLEGRO_KEY_T))
				{
					allegro_sound_set_stream_main_menu();
					allegro_sound_play_stream();
				}
				
                //avisa que hay que renderizar
                allegro_set_var_redraw(true);

                break;

            //se apretó la "x" de la ventana
            case ALLEGRO_EVENT_DISPLAY_CLOSE:

                allegro_set_var_done(true);
                
                break;

            default:

                break;

        }
		

		keyboard_update();
		
	}*/

	allegro_set_var_event(event);
	keyboard_update();
		
	

	if(allegro_get_var_redraw())
	{
		//pone todo en negro
		allegro_clear_display();

		//carga los cambios anteriores para verlos
		al_flip_display();

		//avisa que ya se renderizó
		allegro_set_var_redraw(false);
	}

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
		retorno = BORRAR;
	else
		retorno = NO_MOVER;

	return retorno;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 