/**
 * @file nombre.c
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

#include "../../nombre.h"

#include "allegro_stuff.h"
#include "game_data.h"

#include <string.h>


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

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void nuevoNombre(void)
{
	allegro_clear_display();
	al_clear_to_color(al_map_rgb(100,1,1));
	al_flip_display();
}

void subirLetra(void)
{

}

void bajarLetra(void)
{

}

void siguienteLetra(void)
{

}

void agregarLetra(void)
{
	int i;
	for(i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_Z; i++)
	{
		if(check_keyboard_copy(i))
		{
			game_data_add_name_letter(i + '@');
			break;
		}
	}

	if(check_keyboard_copy(ALLEGRO_KEY_BACKSPACE))
		game_data_add_name_letter(ALLEGRO_KEY_BACKSPACE);

}

void subirNombre(void)
{
	
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 