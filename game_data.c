/***************************************************************************//**
	@file     +Nombre del archivo (ej: template.c)+
	@brief    +Descripcion del archivo+
	@author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "game_data.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

//Estructura con datos del juego.
static struct
{
	const char* nombre; //Viene con terminador???
	int vidas;
	unsigned long puntos;
	char dificultad;
} datos;

//Estructura de una celda del mapa.
typedef struct
{
    char rana : 1;
    char objeto : 5;
    char piso : 2;
} celda_t;


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

//Mapa del juego
static celda_t mapa[ALTO][ANCHO];


/*******************************************************************************
 *******************************************************************************
												GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/*******************************************************************************
 *******************************************************************************
												LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 