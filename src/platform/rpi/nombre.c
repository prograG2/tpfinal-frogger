/**
 * @file nombre.c
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

#include "../../nombre.h"
#include "mensajes.h"
#include "../../display.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

extern matriz_t disp_matriz;


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

static mensaje_t nombre;
static char last;

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void nuevoNombre(){
	nombre = mensaje("", POS_MSJ2, false);
	last = 'A';
	concatenarLetraMensaje(last, &nombre);

}

void subirLetra(){
	if(--last < 'A')
		last = 'Z';
  	reemplazarUltLetraMensaje(last, &nombre);
  	copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
  	actualizarDisplay();
}

void bajarLetra(){
  if(++last < 'A')
		last = 'Z';
  	reemplazarUltLetraMensaje(last, &nombre);
  	copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
  	actualizarDisplay();
}

void siguienteLetra(){
	last = 'A';
	concatenarLetraMensaje(last, &nombre);
  copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
  actualizarDisplay();
  //printf("%d\n", ++i);
}

void agregarLetra(void){
}

char* devolverNombre(void){
	return nombre.msj;
}


/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 