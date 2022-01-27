/**
 * @file sound.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../sound.h"

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

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


bool iniciarSonido(void)
{
	bool state = true;


	return state;
}

void destruirSonido(void)
{
	
}


void pausar_musica(void)
{
	allegro_sound_pause_stream();
}

void reproducir_musica(int musica){

}

void reproducir_sonido(int sonido){

}

/*

void reproducir_musica_menu_ppal(void)
{
	allegro_sound_set_stream_main_menu();
	allegro_sound_play_stream();
}

void reproducir_musica_ranking(void)
{
	allegro_sound_set_stream_ranking();
	allegro_sound_play_stream();
}

void reproducir_musica_creditos(void)
{
	allegro_sound_set_stream_credits();
	allegro_sound_play_stream();
}

void reproducir_musica_jugando(void)
{
	allegro_sound_set_stream_playing();
	allegro_sound_play_stream();
}

void reproducir_musica_menu_pausa(void)
{
	allegro_sound_set_stream_pause_menu();
	allegro_sound_play_stream();
}


void reproducir_efecto_seleccion(void)
{
	allegro_sound_play_effect_click();
}

void reproducir_efecto_salto(void)
{
	
}

void reproducir_efecto_impacto(void)
{
	
}

void reproducir_efecto_ahogado(void)
{
	
}

void reproducir_efecto_poco_tiempo(void)
{
	
}

void reproducir_efecto_meta(void)
{
	
}

void reproducir_efecto_nivel_completo(void)
{
	
}

void reproducir_efecto_nuevo_max_score(void)
{
	
}

void reproducir_efecto_game_over(void)
{
	
}

void reproducir_efecto_menu_enter(void)
{
	allegro_sound_play_effect_menu_enter();
}

void reproducir_efecto_saliendo(void)
{
	allegro_sound_play_effect_exiting();	
}

*/




/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 