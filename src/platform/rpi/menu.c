/**
 * @file menu.c
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

#include "../../menu.h"
#include "../../display.h"

#include <stdlib.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

struct
{
	int *menu_actual; //arreglo con los índices de textos ordenados para mostrar como menú
	int opcion_actual;
	int max_opciones;
} menu;


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

char* menu_textos[9] = {"JUGAR", "DIFICULTAD", "RANKING", "SALIR", "CONTINUAR", "REINICIAR", "FACIL", "NORMAL", "DIFICIL"};


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setMenu(int* a, unsigned int size){
    menu.menu_actual = realloc(menu.menu_actual, size*sizeof(int));
    int i;
    for(i=0; i<size; i++){
        menu.menu_actual[i] = a[i];
    }
    menu.max_opciones = size;
}

void setOpcion(int opc){
    menu.opcion_actual = opc;
    fijarTexto(menu_textos[menu.menu_actual[menu.opcion_actual]], POS_OPCION);
}

int getOpcion(){
    return menu.opcion_actual;
}

void subirOpcion(){
    if(--menu.opcion_actual < 0)
        menu.opcion_actual = menu.max_opciones - 1;
    fijarTexto(menu_textos[menu.menu_actual[menu.opcion_actual]], POS_OPCION);
}

void bajarOpcion(){
    if(++menu.opcion_actual >= menu.max_opciones)
        menu.opcion_actual = 0;
    fijarTexto(menu_textos[menu.menu_actual[menu.opcion_actual]], POS_OPCION);
}

void iniciarMenu(){
    /*
    menu.textos[JUGAR] = "JUGAR";
    menu.textos[DIFICULTAD] = "DIFICULTAD";
    menu.textos[RANKING] = "RANKING";
    menu.textos[SALIRTXT] = "SALIR";
    menu.textos[CONTINUAR] = "CONTINUAR";
    menu.textos[REINICIAR] = "REINICIAR";
    menu.textos[FACIL] = "FACIL";
    menu.textos[NORMAL] = "NORMAL";
    menu.textos[DIFICIL] = "DIFICIL";
    */
}

void destruirMenu(){
    free(menu.menu_actual);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

 