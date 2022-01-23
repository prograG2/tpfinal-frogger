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

#include "mensajes.h"
#include "bitmap.h"
#include "disdrv.h"

#include <pthread.h>
#include <string.h>


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

static void fijarTexto(char* txt, int pos);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_mutex_t lock;

static Matriz disp_matriz;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int iniciarDisplay()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        return 1;
    }

    disp_init();       //inicializa el display
    disp_clear();      //limpia todo el display

    return 0;
}

void actualizarDisplay()
{
	for(int i = DISP_MIN; i <= (DISP_MAX_Y); i++)
        for(int j = DISP_MIN; j <= (DISP_MAX_X) ; j++)
            disp_write((dcoord_t){j, i}, disp_matriz[i] & (0x8000 >> j));

    disp_update();

}


void limpiarDisplay()
{
	pthread_mutex_lock(&lock);
    limpiarMatriz(disp_matriz);
    actualizarDisplay();
    pthread_mutex_unlock(&lock);
}

void mostrarTexto(char* txt, int pos)
{
	mensaje_t msj = mensaje(txt, pos);
    while(renglonBool(msj.renglon)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje(&msj, NO_REPETIR);
        escribirRenglonDisplay(msj.renglon, pos);
    }
}

void mostrarPosicion(char* posicion, char* nombre, char* puntos){
    limpiarDisplay();
    fijarTexto(posicion, POS_MSJ1);
    mostrarTexto(nombre, POS_MSJ2);
    mostrarTexto(puntos, POS_MSJ2);
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void fijarTexto(char* txt, int pos){
    mensaje_t msj = mensaje(txt, pos);
    escribirRenglonDisplay(msj.renglon, POS_MSJ1);
}


 





