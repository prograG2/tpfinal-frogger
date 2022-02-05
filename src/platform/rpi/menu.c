/**
 * @file 	menu.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Archivo para manejo de los menús en RPI
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../menu.h"
#include "../../display.h"
#include "../../sound.h"

#include <stdlib.h>

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static struct
{
    int *menu_actual; // arreglo con los índices de textos ordenados para mostrar como menú
    int opcion_actual;
    int max_opciones;
} menu;

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static char *menu_textos[] = {"JUGAR", "DIFICULTAD", "RANKING", "CREDITOS", "SALIR", "CONTINUAR", "REINICIAR", "FACIL", "NORMAL", "DIFICIL"};

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setMenu(int *a, unsigned int size)
{
    int *aux = realloc(menu.menu_actual, size * sizeof(int));
    if(aux == NULL){
        free(menu.menu_actual);
        queueInsertar(FORCE_SALIR);
    }

    menu.menu_actual = aux;
    int i;
    for (i = 0; i < size; i++)
    {
        menu.menu_actual[i] = a[i];
    }
    menu.max_opciones = size;
}

void setOpcion(int opc)
{
    menu.opcion_actual = opc;
    dejarTexto(menu_textos[menu.menu_actual[menu.opcion_actual]], POS_OPCION, true);
}

int getOpcion()
{
    return menu.opcion_actual;
}

void subirOpcion()
{
    if (--menu.opcion_actual < 0)
        menu.opcion_actual = menu.max_opciones - 1;
    dejarTexto(menu_textos[menu.menu_actual[menu.opcion_actual]], POS_OPCION, true);

    reproducirEfecto(EFECTO_SELECCION);
}

void bajarOpcion()
{
    if (++menu.opcion_actual >= menu.max_opciones)
        menu.opcion_actual = 0;
    dejarTexto(menu_textos[menu.menu_actual[menu.opcion_actual]], POS_OPCION, true);

    reproducirEfecto(EFECTO_SELECCION);
}

void iniciarMenu()
{
}

void destruirMenu()
{
    free(menu.menu_actual);
}
