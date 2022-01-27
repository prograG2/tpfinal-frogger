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

#define CASTEAR_POSICION(pos) (((pos) == POS_OPCION) || ((pos) == POS_RANKING_2) ? POS_MSJ2 : POS_MSJ1)

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

/**
 * @brief 
 * 
 * @param ptr 
 * @return void* 
 */
static void* thread_texto_display(void* ptr);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_mutex_t lock;

static Matriz disp_matriz;

static pthread_t ttextodisplay;

static mensaje_t texto1, texto2;

static int texto;
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
    pthread_mutex_lock(&lock);
	for(int i = DISP_MIN; i <= (DISP_MAX_Y); i++)
        for(int j = DISP_MIN; j <= (DISP_MAX_X) ; j++)
            disp_write((dcoord_t){j, i}, disp_matriz[i] & (0x8000 >> j));

    disp_update();
    pthread_mutex_unlock(&lock);
}

void limpiarDisplay()
{
	pthread_mutex_lock(&lock);
    if(texto){
        texto = 0;
        pthread_join(thread_texto_display, NULL);
    }
    limpiarMatriz(disp_matriz);
    actualizarDisplay();
    pthread_mutex_unlock(&lock);
}

void mostrarTexto(char* txt, int pos)
{
    int posicion = CASTEAR_POSICION(pos);
	mensaje_t msj = mensaje(txt, posicion);
    while(renglonBool(msj.renglon)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje(&msj, NO_REPETIR);
        copiarMatrizRenglon(disp_matriz, msj.renglon, msj.posicion);
        actualizarDisplay();
    }
}

void fijarTexto(char* txt, int pos){
    int posicion = CASTEAR_POSICION(pos);
    switch (posicion)
    {
    case POS_MSJ1:
        texto1 = mensaje(txt, posicion);
        break;
    
    default:
        texto2 = mensaje(txt, posicion);
        break;
    }
    if(!texto){
        pthread_create(&ttextodisplay, NULL, thread_texto_display, NULL);
        texto = 1;
    }
}

void fijarMensaje(mensaje_t* msj, int pos){
    int posicion = CASTEAR_POSICION(pos);
    switch (posicion)
    {
    case POS_MSJ1:
        texto1 = *msj;
        break;
    
    default:
        texto2 = *msj;
        break;
    }
    if(!texto){
        pthread_create(&ttextodisplay, NULL, thread_texto_display, NULL);
        texto = 1;
    }
}

void mostrarPosicion(char* posicion, char* nombre, char* puntos){
    limpiarDisplay();
    fijarTexto(posicion, POS_MSJ_RANKING);
    mostrarTexto(nombre, POS_RANKING_2);
    mostrarTexto(puntos, POS_RANKING_2);
}

void mostrarCreditos(char* linea)
{

}

void reconfigurarDisplayON(void)
{
	
}

void reconfigurarDisplayOFF(void)
{

}






/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void* thread_texto_display(void* ptr){
    while(texto){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje(&texto1, REPETIR);
        copiarMatrizRenglon(disp_matriz, texto1.renglon, POS_MSJ1);
        moverMensaje(&texto2, REPETIR);
        copiarMatrizRenglon(disp_matriz, texto2.renglon, POS_MSJ2);
        actualizarDisplay();
    }
}





