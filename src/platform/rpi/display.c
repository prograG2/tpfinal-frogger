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

Matriz disp_matriz;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 * @param ptr 
 * @return void* 
 */
static void* threadTextoDisplay(void* ptr);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_mutex_t lock;

static pthread_t ttextodisplay;

static mensaje_t texto1, texto2;

static int texto;

/*creditos*/
static FILE* pFile;
static char linea[100];
static int puesto_int = 1;
static char puesto[2], *nombre, *puntos;
/*creditos*/

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
    if(texto){
        texto = 0;
        pthread_join(ttextodisplay, NULL);
    }
    limpiarMatriz(disp_matriz);
    actualizarDisplay();
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
        texto = 1;
        pthread_create(&ttextodisplay, NULL, threadTextoDisplay, NULL);
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
        pthread_create(&ttextodisplay, NULL, threadTextoDisplay, NULL);
        texto = 1;
    }
}

void mostrarPosicion(char* posicion, char* nombre, char* puntos){
    limpiarDisplay();
    fijarTexto(posicion, POS_MSJ_RANKING);
    mostrarTexto(nombre, POS_RANKING_2);
    mostrarTexto(puntos, POS_RANKING_2);
}

void cargarRanking(FILE* txt)
{
	pFile = txt;
	puesto_int = 1;
}

bool mostrarRanking(void)
{
	while(fgets(linea, 100, pFile) != NULL)
	{
		char* pch = strtok(linea," ");
		nombre = pch;
		ulltoa(puesto_int++, puesto);
		pch = strtok(NULL, " ");
		puntos = pch;
		mostrarPosicion(puesto, nombre, puntos);
	}
	
	//termina de mostrarlos una vez, y sale.
	return false;
}

void finalizarRanking(void)
{

}

void cargarCreditos(void)
{

}

bool mostrarCreditos(void)
{
	/*
	FILE* pFile;
	char linea[100];

	pFile = fopen ("credits.txt" , "r");
	if (pFile == NULL){
		perror ("credits.txt: Error opening file");
		return NULL;
	}
	
		while((fgets(linea, 100, pFile)) != NULL && (p2CurrentState == viendo_creditos))
		{
			mostrarCreditos(linea);

			fixHighCpuUsage();
		}
	}
	*/

	//termina de mostrarlos una vez, y sale.
	return false;
}

void finalizarCreditos(void)
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

static void* threadTextoDisplay(void* ptr){
    while(texto){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje(&texto1, REPETIR);
        copiarMatrizRenglon(disp_matriz, texto1.renglon, POS_MSJ1);
        moverMensaje(&texto2, REPETIR);
        copiarMatrizRenglon(disp_matriz, texto2.renglon, POS_MSJ2);
        actualizarDisplay();
    }

    return NULL;
}





