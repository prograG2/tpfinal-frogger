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
#include "audio.h"

#include <stdio.h>

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
     EFECTOS_DIR "/low_time.wav",
     EFECTOS_DIR "/goal_reached.wav",
     EFECTOS_DIR "/run_completed.wav",
     EFECTOS_DIR "/new_max_score.wav",
     EFECTOS_DIR "/menu_enter.wav",
     EFECTOS_DIR "/saliendo.wav",
     EFECTOS_DIR "/no_time.wav"};

static Audio *musica[SIZEOF_MUSICA], *efectos[SIZEOF_EFECTOS];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool iniciarSonido(void)
{
  if (initAudio() == NO_INIT)
  {
    printf("Audio not initilized.\n");
    endAudio();
    return false;
  }
  int i;
  for (i = 0; i < SIZEOF_MUSICA; i++)
    musica[i] = createAudio(archivos_musica[i], 1, SDL_MIX_MAXVOLUME);
  for (i = 0; i < SIZEOF_EFECTOS; i++)
    efectos[i] = createAudio(archivos_efectos[i], 0, SDL_MIX_MAXVOLUME);
  return true;
}

void destruirSonido(void)
{
  endAudio();
  int i;
  for (i = 0; i < SIZEOF_MUSICA; i++)
    freeAudio(musica[i]);
  for (i = 0; i < SIZEOF_EFECTOS; i++)
    freeAudio(efectos[i]);
}

void pausarMusica(void)
{
  pauseAudio();
}

void reproducirMusica(int m)
{
  playMusicFromMemory(musica[m], SDL_MIX_MAXVOLUME);
}

void reproducirEfecto(int e)
{
  playSoundFromMemory(efectos[e], SDL_MIX_MAXVOLUME);
}