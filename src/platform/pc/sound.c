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
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool iniciarSonido(void)
{
	return true;
}

void destruirSonido(void)
{
}

void pausarMusica(void)
{
	allegro_sound_pause_stream();
}

void reproducirMusica(int musica)
{
	switch (musica)
	{
	case MUSICA_CREDITOS:
		allegro_sound_set_stream_credits();
		break;

	case MUSICA_JUGANDO:
		allegro_sound_set_stream_playing();
		break;

	case MUSICA_MENU_PAUSA:
		allegro_sound_set_stream_pause_menu();
		break;

	case MUSICA_MENU_PPAL:
		allegro_sound_set_stream_main_menu();
		break;

	case MUSICA_RANKING:
		allegro_sound_set_stream_ranking();
		break;

	case MUSICA_GAME_OVER:
		allegro_sound_set_stream_game_over();
		break;

	default:
		break;
	}

	allegro_sound_play_stream();
}

void reproducirEfecto(int sonido)
{
	switch (sonido)
	{
	case EFECTO_AHOGADO:
		allegro_sound_play_effect_drowned();
		break;

	case EFECTO_IMPACTO:
		allegro_sound_play_effect_crash();
		break;

	case EFECTO_MENU_ENTER:
		allegro_sound_play_effect_menu_enter();
		break;

	case EFECTO_META:
		allegro_sound_play_effect_goal();
		break;

	case EFECTO_NIVEL_COMPLETO:
		allegro_sound_play_effect_run_completed();
		break;

	case EFECTO_NUEVO_MAX_SCORE:
		allegro_sound_play_effect_new_max_score();
		break;

	case EFECTO_POCO_TIEMPO:
		allegro_sound_play_effect_low_time();
		break;

	case EFECTO_SALIENDO:
		allegro_sound_play_effect_exiting();
		break;

	case EFECTO_SALTO:
		allegro_sound_play_effect_jump();
		break;

	case EFECTO_SELECCION:
		allegro_sound_play_effect_click();
		break;

	default:
		break;
	}
}
