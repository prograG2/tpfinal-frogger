/**
 * @file menu.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "menu.h"
#include "allegro_stuff.h"
#include "geometry.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct
{
	unsigned char state;
	unsigned char window;

} menu_t;

enum MENU_STATES
{
	START,
	OPCION_0,
	OPCION_1,
	OPCION_2
};
enum MENU_WINDOWS
{
	HOME,
	DIFFICULTY,
	RANKING
};


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

///Menu
static menu_t menu;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void inicializarMenu(void)
{
	menu.window = HOME;
	menu.state = START;
}

void menu_update()
{
	switch (menu.state)
	{
	case START:
		if(keyboard_check_key(ALLEGRO_KEY_DOWN) == KEY_JUST_PRESSED)
		{
			menu.state = OPCION_0;
		}
		break;

	case OPCION_0:
		if(keyboard_check_key(ALLEGRO_KEY_UP) == KEY_JUST_PRESSED)
		{
			menu.state = START;
		}  
		else if(keyboard_check_key(ALLEGRO_KEY_DOWN) == KEY_JUST_PRESSED)
		{
			menu.state = OPCION_1;
		}
		break;
	case OPCION_1:
		if(keyboard_check_key(ALLEGRO_KEY_UP) == KEY_JUST_PRESSED)
		{
			menu.state = OPCION_0;
		}  
		else if(keyboard_check_key(ALLEGRO_KEY_DOWN) == KEY_JUST_PRESSED)
		{
			menu.state = OPCION_2;
			keyboard_set_key(ALLEGRO_KEY_DOWN);
		}
		break;
	case OPCION_2:
		if(keyboard_check_key(ALLEGRO_KEY_UP) == KEY_JUST_PRESSED)
		{
			menu.state = OPCION_1;
			keyboard_set_key(ALLEGRO_KEY_UP);
		}  
	default:
		break;
	}
	
}

void renderizarMenu()
{
	ALLEGRO_BITMAP* tempbitmap;

	tempbitmap = sprites.menu[menu.state];

	al_draw_bitmap(tempbitmap, 45, 175 + menu.state*100  , 0);

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 