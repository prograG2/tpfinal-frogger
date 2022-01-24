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

#include "mensajes.h"

#include <stdlib.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
	mensaje_t textos[9];
	int *menu_actual;
	int opcion_actual;
	int max_opciones;
} menu_t;


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

extern Matriz disp_matriz;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 */
static void cambiarAOpcionActual();


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static menu_t menu;


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
    cambiarAOpcionActual();
}

int getOpcion(){
    return menu.opcion_actual;
}

void subirOpcion(){
    if(--menu.opcion_actual < 0)
        menu.opcion_actual = menu.max_opciones - 1;
    cambiarAOpcionActual();
}

void bajarOpcion(){
    if(++menu.opcion_actual >= menu.max_opciones)
        menu.opcion_actual = 0;
    cambiarAOpcionActual();
}

void iniciarMenu(){
    menu.textos[JUGAR] = mensaje("JUGAR", POS_MSJ2);
    menu.textos[DIFICULTAD] = mensaje("DIFICULTAD", POS_MSJ2);
    menu.textos[RANKING] = mensaje("RANKING", POS_MSJ2);
    menu.textos[SALIRTXT] = mensaje("SALIR", POS_MSJ2);
    menu.textos[CONTINUAR] = mensaje("CONTINUAR", POS_MSJ2);
    menu.textos[REINICIAR] = mensaje("REINICIAR", POS_MSJ2);
    menu.textos[FACIL] = mensaje("FACIL", POS_MSJ2);
    menu.textos[NORMAL] = mensaje("NORMAL", POS_MSJ2);
    menu.textos[DIFICIL] = mensaje("DIFICIL", POS_MSJ2);
}

void moverOpcionActual(){
    moverMensaje(&menu.textos[menu.menu_actual[menu.opcion_actual]], REPETIR);
    copiarMatrizRenglon(disp_matriz, menu.textos[menu.menu_actual[menu.opcion_actual]].renglon, menu.textos[menu.menu_actual[menu.opcion_actual]].posicion);
    actualizarDisplay();
}

void destruirMenu(){
    free(menu.menu_actual);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void cambiarAOpcionActual(){
    menu.textos[menu.menu_actual[menu.opcion_actual]].index = menu.textos[menu.menu_actual[menu.opcion_actual]].index_inicio;
    copiarRenglon(menu.textos[menu.menu_actual[menu.opcion_actual]].renglon_inicio, menu.textos[menu.menu_actual[menu.opcion_actual]].renglon);
    copiarRenglon(menu.textos[menu.menu_actual[menu.opcion_actual]].reserva_inicio, menu.textos[menu.menu_actual[menu.opcion_actual]].reserva);
}


 