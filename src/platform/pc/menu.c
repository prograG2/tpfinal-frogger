/**
 * @file menu.c
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

#include "../../menu.h"
#include "../../sound.h"

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
	int actual_state;
	int max_states;
} window_t;


typedef struct
{
	window_t window[MENU_WINDOW_MAX];

	int actual_window;

} menu_t;




/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa el menu
 * 
 */
static void menu_init(void);

/**
 * @brief Actualiza el menu
 * 
 */
static void menu_update(void);

/**
 * @brief Dibuja lelas menu
 * 
 */
static void menu_draw(void);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//Menu
static menu_t menu;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void iniciarMenu(void)
{
	menu_init();

}

void destruirMenu(void)
{
	allegro_deinits();
}

void setMenu(int* a, unsigned int size)
{
	switch (a[0])
	{
		//menu principal (JUGAR, DIFICULTAD, RANKING, SALIRTXT)
		case JUGAR:
			menu.actual_window = MENU_WINDOW_HOME;
			
			break;
		
		//menu dificultades (FACIL, NORMAL, DIFICIL)
		case FACIL:
			menu.actual_window = MENU_WINDOW_DIFFICULTY;

			break;

		//menu pausa (CONTINUAR, REINICIAR, SALIRTXT)
		case CONTINUAR: 
			menu.actual_window = MENU_WINDOW_PAUSE;
			allegro_set_rick_flag(false);

			break;

		//menu game over (REINICIAR, SALIRTXT)
		case REINICIAR:
			menu.actual_window = MENU_WINDOW_GAME_OVER;

			break;
		
		default:
			break;
	}

	
	
}

void setOpcion(int opc)
{
	//Seleccina uno de los botones del menu actual
	menu.window[menu.actual_window].actual_state = opc;

	menu_draw();
}

int getOpcion(void)
{
	return(menu.window[menu.actual_window].actual_state);
}

void subirOpcion(void)
{
	int *actual_option = &menu.window[menu.actual_window].actual_state;
	int *max_option = &menu.window[menu.actual_window].max_states;

	(*actual_option)--;

	if(*actual_option < 0)
		setOpcion(*max_option - 1);
	else
		menu_draw();

	reproducir_efecto(EFECTO_SELECCION);
}

void bajarOpcion(void)
{
	int *actual_option = &menu.window[menu.actual_window].actual_state;
	int *max_option = &menu.window[menu.actual_window].max_states;

	(*actual_option)++;

	if(*actual_option == *max_option)
		setOpcion(0);
	else
		menu_draw();

	reproducir_efecto(EFECTO_SELECCION);
}

void moverOpcionActual(void)
{

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void menu_init(void)
{
	//menu principal (JUGAR, DIFICULTAD, RANKING, SALIRTXT)
	menu.window[MENU_WINDOW_HOME].max_states = 5;

	//menu dificultades (FACIL, NORMAL, DIFICIL)
	menu.window[MENU_WINDOW_DIFFICULTY].max_states = 3;

	//menu pausa (CONTINUAR, REINICIAR, SALIRTXT)
	menu.window[MENU_WINDOW_PAUSE].max_states = 3;

	//menu game over (REINICIAR, SALIRTXT)
	menu.window[MENU_WINDOW_GAME_OVER].max_states = 2;
	

}

static void menu_update()
{
	
}

static void menu_draw()
{
	allegro_clear_display();

	ALLEGRO_BITMAP* background = NULL;
	ALLEGRO_BITMAP* option = NULL;

	background = sprites.menu[menu.actual_window].background;
	option = sprites.menu[menu.actual_window].option[menu.window[menu.actual_window].actual_state];

	al_draw_bitmap(background, 0, 0, 0);

	al_draw_bitmap(option, MENU_OPTION_TOPLEFT_X,
							MENU_OPTION_TOPLEFT_Y + (menu.window[menu.actual_window].actual_state * MENU_OPTION_DELTA_Y),
							0);

	al_flip_display();

}

 