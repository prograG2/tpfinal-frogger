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

static bool rick_flag = false;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setNombre(char* nombre)
{

}

void setPuntos(uint64_t puntos)
{

}

void setMaxPuntos(uint64_t max)
{

}

void setMaxVidas()
{

}

void setTiempoInicial(clock_t tiempo)
{

}

void setTiempoLimite(clock_t limite)
{

}

void setDificultad(int diff)
{
	if(diff == FACIL)
		game_data_set_diff(DIFFICULTIES_EASY);
	else if(diff == NORMAL)
		game_data_set_diff(DIFFICULTIES_NORMAL);
	else if(diff == DIFICIL)
		game_data_set_diff(DIFFICULTIES_HARD);
}

void setTiempo(clock_t tiempo)
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

int getVidas(void)
{

}

int getNivel(void)
{

}

clock_t getTiempoInicial(void)
{

}

clock_t getTiempoLimite(void)
{

}

int getDificultad(void)
{

}

int getAgua(void)
{

}


void inicializarJuego(void)
{
	game_data_init();
	entities_init();

	allegro_sound_set_stream_playing();
	allegro_sound_play_stream();

	allegro_clear_display();
	al_flip_display();

}

void inicializarNivel(void)
{

}

void reiniciarNivel(void)
{

}

void decrementarVida(void)
{

}


void incrementarPuntos(int pt)
{

}

void refrescar(void)
{
	
}

void refrescarJugador(void)
{

}

void refrescarAutos(void)
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

void llegada(void)
{

}

void subirNivel(void)
{

}

void actualizarInterfaz(void)
{
	if(allegro_get_last_key() == ALLEGRO_KEY_9)
	{
		if(!rick_flag)
		{
			allegro_rick_on();
			rick_flag = true;
		}

		else
		{
			allegro_rick_off();
			rick_flag = false;
		}		
	}

	game_data_update();
	entities_update();

	allegro_clear_display();
	allegro_draw_background();

	if(rick_flag)
		allegro_rick_draw();

	entities_draw();
	game_data_draw();

	al_flip_display();
	
}

void imprimirMapa(void)
{
	
}

void continuandoJuego(void)
{
	allegro_sound_set_stream_playing();
	allegro_sound_play_stream();
	rick_flag = false;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 