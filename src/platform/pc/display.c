/**
 * @file display.c
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

#include "../../display.h"
#include "../../ranking.h"

#include "allegro_stuff.h"
#include "game_data.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define CREDITS_SCROLL_SPEED	1


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

static pthread_mutex_t lock;

static int credits_scroll_cont;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int iniciarDisplay()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
        return 1;

	allegro_inits();


	return 0;
}

void actualizarDisplay()
{
}


void limpiarDisplay()
{
}

void mostrarTexto(char* txt, int pos)
{
	if(txt[0] == 'R')
	{

	}

}

void fijarTexto(char* txt, int pos)
{

}

void mostrarPosicion(char* posicion, char* nombre, char* puntos)
{
	printf("Posicion: %s ~ Nombre: %s ~ Score: %s\n", posicion, nombre, puntos);
}

void cargarRanking(void)
{
	int i = 0;
	
	int lines = getRankingLineas();
	char **names = getRankingNombres();
	uint64_t *scores = getRankingPuntos();

	allegro_clear_display();
	for(i = 0; i < lines; i++)
	{
		al_draw_textf(	allegro_get_var_font(),
						al_map_rgb(255,255,255),
						10,
						100 + i*20,
						0,
						"%s", names[i]);

		al_draw_textf(	allegro_get_var_font(),
						al_map_rgb(255,255,255),
						250,
						100 + i*20,
						0,
						"%ld", scores[i]);
	}
	al_flip_display();
	
}

bool mostrarRanking(void)
{
	

	

	return true;
}

void finalizarRanking(void)
{

}

void cargarCreditos(void)
{
	credits_scroll_cont = 0;
}

bool mostrarCreditos(void)
{
	if(allegro_get_var_redraw())
	{

		credits_scroll_cont -= CREDITS_SCROLL_SPEED;
		if(credits_scroll_cont == -CREDITS_SCREEN_LENGTH + DISPLAY_H)
			credits_scroll_cont = 0;

		allegro_clear_display();
		al_draw_bitmap(sprites.credits, 0, credits_scroll_cont, 0);
		al_flip_display();

		allegro_set_var_redraw(false);
	}

	return true;
}

void finalizarCreditos(void)
{
	
}

void reconfigurarDisplayON(void)
{
	allegro_reinit_display();
}

void reconfigurarDisplayOFF(void)
{
	allegro_deinit_display();
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 





