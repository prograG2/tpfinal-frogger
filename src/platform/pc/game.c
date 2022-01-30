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


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setNombre(char* nombre)
{

}

void setMaxPuntos(uint64_t max)
{
	
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

}

bool tiempoLimite(void)
{
	
}


char* getNombre(void)
{

}

uint64_t getPuntos(void)
{

}

uint64_t getMaxPuntos(void)
{

}

int getNivel(void)
{

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

}

void refrescar(void)
{
	
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

void perderVidaChoque(void)
{

}

void perderVidaAgua(void)
{

}

void perderVidaTimeout(void)
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
		game_data_update();
		entities_update();

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



 