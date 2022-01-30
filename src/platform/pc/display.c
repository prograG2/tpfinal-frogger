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

#include "allegro_stuff.h"
#include "game_data.h"


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

static pthread_mutex_t lock;


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
	pthread_mutex_lock(&lock);



	pthread_mutex_unlock(&lock);
}


void limpiarDisplay()
{
	pthread_mutex_lock(&lock);



	pthread_mutex_unlock(&lock);
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

void cargarRanking(FILE* pFile)
{

}

bool mostrarRanking(void)
{


}

void finalizarRanking(void)
{

}

void cargarCreditos(void)
{

}

bool mostrarCreditos(void)
{

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



 





