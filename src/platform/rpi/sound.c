/**
 * @file 	sound.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Archivo para manejo del sonido en RPI
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../sound.h"
#include "simpleSDL2audio/audio.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MUSICA_DIR "../res/sounds/streams"
#define EFECTOS_DIR "../res/sounds/samples"

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static char *archivos_musica[] =
	{MUSICA_DIR "/main_menu_theme.wav",
	 MUSICA_DIR "/ranking_theme.wav",
	 MUSICA_DIR "/credits_theme.wav",
	 MUSICA_DIR "/playing_theme.wav",
	 MUSICA_DIR "/pause_menu_theme.wav",
	 MUSICA_DIR "/game_over.wav"};

static char *archivos_efectos[] =
	{EFECTOS_DIR "/click.wav",
	 EFECTOS_DIR "/jump_original.wav",
	 EFECTOS_DIR "/crash.wav",
	 EFECTOS_DIR "/fall_in_water.wav",
	 EFECTOS_DIR "/low_time_RPI.wav",
	 EFECTOS_DIR "/goal_reached.wav",
	 EFECTOS_DIR "/run_completed.wav",
	 EFECTOS_DIR "/new_max_score.wav",
	 EFECTOS_DIR "/menu_enter.wav",
	 EFECTOS_DIR "/saliendo.wav",
	 EFECTOS_DIR "/no_time.wav"};

static Audio *musica;

static int actual;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool iniciarSonido(void)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		return 1;
	}

	initAudio();
	actual = -1;
	return true;
}

void destruirSonido(void)
{
	endAudio();
	freeAudio(musica);
	SDL_Quit();
}

void pausarMusica(void)
{
	pauseAudio();
	actual = -1;
}

void reproducirMusica(int m)
{
	if (m != actual)
	{
		endAudio();
		freeAudio(musica);
		initAudio();
		musica = createAudio(archivos_musica[m], 1, SDL_MIX_MAXVOLUME >> 1);
		playMusicFromMemory(musica, SDL_MIX_MAXVOLUME >> 1);
		actual = m;
	}
}

void reproducirEfecto(int e)
{
	playSound(archivos_efectos[e], SDL_MIX_MAXVOLUME);
}