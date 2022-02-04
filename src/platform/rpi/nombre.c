/**
 * @file 	nombre.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Archivo para manejo de información en el ingreso del nombre
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../nombre.h"
#include "mensajes.h"
#include "../../display.h"

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

extern matriz_t disp_matriz;

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

void nuevoNombre()
{
    nombre = mensaje("A", POS_MSJ2, false);
    nombre.index = 0;
    nombre.j = 0;
    last = 'A';
    copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
    actualizarDisplay();
}

void subirLetra()
{
    if (--last < 'A')
        last = 'Z';
    reemplazarUltLetraMensaje(last, &nombre);
    copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
    actualizarDisplay();
}

void bajarLetra()
{
    if (++last > 'Z')
        last = 'A';
    reemplazarUltLetraMensaje(last, &nombre);
    copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
    actualizarDisplay();
}

void siguienteLetra()
{
    concatenarLetraMensaje(last, &nombre);
    last = 'A';
    copiarMatrizRenglon(disp_matriz, nombre.renglon, POS_MSJ2);
    actualizarDisplay();
}

void agregarLetra(void)
{
}

char *devolverNombre(void)
{
    return nombre.msj;
}
