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
#include "audio.h"

#include <stdio.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MUSICA_DIR "/../res/sounds/streams"
#define EFECTOS_DIR "/../res/sounds/samples"

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

static char* archivos_musica[] = {MUSICA_DIR"/main_menu_theme.wav", MUSICA_DIR"/ranking_theme.wav", MUSICA_DIR"/credits_theme.wav", MUSICA_DIR"/playing_theme.wav", MUSICA_DIR"/pause_menu_theme.wav", MUSICA_DIR"/game_over_menu_theme.wav"};
static char* archivos_efectos[] = {EFECTOS_DIR"/click.wav", EFECTOS_DIR"/jump_original.wav", EFECTOS_DIR"/crash.wav", EFECTOS_DIR"/fall_in_water.wav", EFECTOS_DIR"/low_time.wav", EFECTOS_DIR"/goal_reached.wav", EFECTOS_DIR"/run_completed.wav", EFECTOS_DIR"/respect.wav", EFECTOS_DIR"/menu_enter.wav"}

static Audio *musica[SIZEOF_MUSICA], *efectos[SIZEOF_EFECTOS];
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


bool iniciarSonido(void)
{
	if ( initAudio() == NO_INIT)
    {
        printf("Audio not initilized.\n");
	    endAudio();
	    return false;
    }
    int i;
    for(i=0; i<SIZEOF_MUSICA; i++)
        musica[i] = createAudio(archivos_musica[i], 1, SDL_MIX_MAXVOLUME);
    for(i=0; i<SIZEOF_EFECTOS; i++)
        efectos[i] = createAudio(archivos_efectos[i], 0, SDL_MIX_MAXVOLUME / 2);
    return true;
}

void destruirSonido(void)
{
	endAudio();
    int i;
    for(i=0; i<SIZEOF_MUSICA; i++)
        musica[i] = freeAudio(archivos_musica[i], 1, SDL_MIX_MAXVOLUME);
    for(i=0; i<SIZEOF_EFECTOS; i++)
        efectos[i] = freeAudio(archivos_efectos[i], 0, SDL_MIX_MAXVOLUME / 2);
}


void pausar_musica(void)
{
	pauseAudio();
}

void reproducir_musica(int m)
{
    playMusicFromMemory(musica[m], SDL_MIX_MAXVOLUME);
}


void reproducir_efecto(int e)
{
	memory_fun(efectos[e]);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 