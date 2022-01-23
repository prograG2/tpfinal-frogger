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

static Renglon nombreDisp;
static char nombre[L_MAX];
static int index, j, i;


/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void nuevoNombre(){
	index = 0;
	j = 0;
	i = 0;
	nombre[index] = 'A';
	nombre[index+1] = '\0';
}

void subirLetra(){
	if(--nombre[index] < 'A')
		nombre[index] = 'Z';
  reemplazarLetra(nombreDisp, nombre[index], j);
  escribirRenglonDisplay(nombreDisp, POS_MSJ2);
}

void bajarLetra(){
  if(++nombre[index] > 'Z')
		nombre[index] = 'A';
  reemplazarLetra(nombreDisp, nombre[index], j);
  escribirRenglonDisplay(nombreDisp, POS_MSJ2);
}

void siguienteLetra(){
  if(index == L_MAX-2)
		return;
	index++;
	nombre[index] = 'A';
	nombre[index+1] = '\0';
  int resto = (CANT_COLUMNAS-j) - 6; //Considero el peor caso para calcular el espacio
  if(resto < 0){
	renglonShiftIzq(nombreDisp, -resto); //Me corro lo que necesito para que entre la sig letra
	j = CANT_COLUMNAS - 6;
  }
  else  
		j += getLongitud(nombre[index]) + 1;
	
  reemplazarLetra(nombreDisp, nombre[index], j);
  escribirRenglonDisplay(nombreDisp, POS_MSJ2);
  //printf("%d\n", ++i);
}

void agregarLetra(){
}


/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 