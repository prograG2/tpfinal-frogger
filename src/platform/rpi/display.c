/**
 * @file 	bitmap.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Archivo para manejo del display de RPI
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../display.h"
#include "../../ranking.h"

#include "mensajes.h"
#include "bitmap.h"
#include "disdrv.h"

#include <unistd.h>
#include <pthread.h>
#include <string.h>

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

matriz_t disp_matriz;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void *threadTextoDisplay(void *ptr);
static void *threadPresentacion(void *ptr);
static void ulltoa(unsigned long long num, char *str);
static int castear_posicion(int pos);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static const clock_t TIEMPO_SLEEP_DISPLAY = CLOCKS_PER_SEC >> 3;

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_mutex_t lock;
static pthread_t ttextodisplay, tpresentacion;
static mensaje_t texto1, texto2, texto3;
static bool thread_encendido, thread_presentacion_encendido;

static int lines, i;
static char **names;
static unsigned long long *scores;

static char *autores[] = {"ALEJANDRO HEIR", "FRANCO AGGRIPINO", "MATIAS ALVAREZ", "TOMAS CASTRO"};

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool iniciarDisplay()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		return 1;
	}

	disp_init();  // inicializa el display
	disp_clear(); // limpia todo el display

	return 0;
}

void actualizarDisplay()
{
	pthread_mutex_lock(&lock);
	for (int i = DISP_MIN; i <= (DISP_MAX_Y); i++)
		for (int j = DISP_MIN; j <= (DISP_MAX_X); j++)
			disp_write((dcoord_t){j, i}, disp_matriz[i] & (0x8000 >> j));

	disp_update();
	pthread_mutex_unlock(&lock);
}

void limpiarDisplay()
{
	texto1.habilitacion = false;
	texto2.habilitacion = false;
	texto3.habilitacion = false;

	if (thread_encendido)
	{
		thread_encendido = false;
		pthread_join(ttextodisplay, NULL);
	}
	if (thread_presentacion_encendido)
	{
		thread_presentacion_encendido = false;
		pthread_join(tpresentacion, NULL);
	}

	limpiarMatriz(disp_matriz);
	actualizarDisplay();
}

void mostrarTexto(char *txt, int pos)
{
	int posicion = castear_posicion(pos);
	mensaje_t msj = mensaje(txt, posicion, false);
	while (!renglonIzquierdoLibre(&msj))
	{
		usleep(TIEMPO_SLEEP_DISPLAY);
		moverMensaje(&msj);
		copiarMatrizRenglon(disp_matriz, msj.renglon, msj.posicion);
		actualizarDisplay();
	}
}

void dejarTexto(char *txt, int pos, bool repetir)
{
	int posicion = castear_posicion(pos);

	switch (posicion)
	{
	case POS_MSJ1:
		texto1 = mensaje(txt, posicion, repetir);
		break;
	case POS_MSJ2:
		texto2 = mensaje(txt, posicion, repetir);
		break;
	default:
		limpiarDisplay();
		texto3 = mensaje(txt, posicion, repetir);
	}

	if (!thread_encendido)
	{
		thread_encendido = true;
		pthread_create(&ttextodisplay, NULL, threadTextoDisplay, NULL);
	}
}

void cargarRanking(void)
{
	borrarRenglon(texto2.renglon);
	lines = getRankingLineas();
	if (lines <= 0)
		dejarTexto("NINGUNA PARTIDA COMPLETADA AUN", POS_OPCION, true);
	else
	{
		names = getRankingNombres();
		scores = getRankingPuntos();
		i = 0;
	}
}

void mostrarRanking(void)
{
	if (renglonIzquierdoLibre(&texto2) && lines > 0)
	{ // si se acabó lo que tenía para mostrar abajo, busco la siguiente posición
		renglon_t r = {0};
		uintARenglon(i + 1, r);
		copiarMatrizRenglon(disp_matriz, r, POS_MSJ1); // se pone la posición en el renglón de arriba
		actualizarDisplay();

		char score_str[L_MAX], puesto_msj[L_MAX];

		strcpy(puesto_msj, names[i]);
		strcat(puesto_msj, " ");
		ulltoa(scores[i], score_str);
		strcat(puesto_msj, score_str);			 // se arma un string con el nombre de jugador y la puntuación
		dejarTexto(puesto_msj, POS_OPCION, false); // se muestra el string en la posición de abajo hasta que

		if (++i >= lines) // apunto a la siguiente posición
			i = 0;
	}
}

void cargarCreditos()
{
	i = 0;
}

void mostrarCreditos(void)
{
	if (!texto3.habilitacion && !texto2.habilitacion && !thread_presentacion_encendido)
	{
		switch (i)
		{
    case 0:
      dejarTexto("PROGRAMACION TPF 2021 1C", POS_CREDITOS_INTRO, false);
      break;
		case 1:
			limpiarDisplay();
			thread_presentacion_encendido = true;
			pthread_create(&tpresentacion, NULL, threadPresentacion, NULL);
			break;
		case 2:
			pthread_join(tpresentacion, NULL);
      dejarTexto("AA", POS_MSJ_MENU, true);
		default:
			dejarTexto(autores[i-2], POS_OPCION, false);
		}
    if(++i > 5)
      i = 0;
	}
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

static void *threadTextoDisplay(void *ptr)
{
	while (thread_encendido && (texto1.habilitacion || texto2.habilitacion || texto3.habilitacion))
	{
		usleep(TIEMPO_SLEEP_DISPLAY);
		if (texto1.habilitacion)
		{
			moverMensaje(&texto1);
			copiarMatrizRenglon(disp_matriz, texto1.renglon, POS_MSJ1);
		}
		if (texto2.habilitacion)
		{
			moverMensaje(&texto2);
			copiarMatrizRenglon(disp_matriz, texto2.renglon, POS_MSJ2);
		}
		if (texto3.habilitacion)
		{
			moverMensaje(&texto3);
			copiarMatrizRenglon(disp_matriz, texto3.renglon, POS_MSJ3);
		}
		actualizarDisplay();
	}

	thread_encendido = false;
	pthread_exit(NULL);
}

static void *threadPresentacion(void *ptr)
{
	int coordenadas[][2] = {{0, 0}, {4, 1}, {8, 3}, {1, 8}, {5, 9}, {9, 10}, {13, 11}};
	int j;
  char str_presentacion[] = "FROGGER";
	for (j = 0; j < 14 && thread_presentacion_encendido; j++)
	{
		matriz_t letra_matriz;
		charAMatriz(str_presentacion[j % 7], letra_matriz, coordenadas[j % 7]);
		if (j >= 7)
			matrizXor(disp_matriz, letra_matriz);
		else
			matrizOr(disp_matriz, letra_matriz);
		actualizarDisplay();
		usleep(TIEMPO_SLEEP_DISPLAY);
	}

	thread_presentacion_encendido = false;

	return NULL;
}

static void ulltoa(unsigned long long num, char *str)
{
	unsigned long long sum = num;
	int i = 0;
	int digit;
	do
	{
		digit = sum % 10;
		str[i++] = '0' + digit;
		sum /= 10;
	} while (sum);
	str[i--] = '\0';

	int j = 0;
	char ch;
	while (i > j)
	{
		ch = str[i];
		str[i--] = str[j];
		str[j++] = ch;
	}
}

static int castear_posicion(int pos){
  if((pos == POS_CREDITOS_INTRO) || (pos == POS_MSJ_NEW_HI_SCORE))
    return POS_MSJ3;
  if((pos == POS_OPCION) || (pos == POS_CREDITOS))
    return POS_MSJ2;
  return POS_MSJ1;
}