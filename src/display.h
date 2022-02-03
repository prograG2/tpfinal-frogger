/**
 * @file 	display.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo display
 * 			Vinculo entre la fsm y las plataformas en lo que respecta
 * 			a la visualizacion del juego.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

// Posiciones de mensajes
enum posiciones_mensajes
{
	POS_MSJ_MENU,
	POS_MSJ_DIFICULTAD,
	POS_MSJ_RANKING,
	POS_MSJ_NOMBRE,
	POS_MSJ_PASAR,
	POS_MSJ_PAUSA,
	POS_MSJ_NEW_HI_SCORE,
	POS_MSJ_GAME_OVER,
	POS_OPCION,
	POS_RANKING_2,
	POS_CREDITOS
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa el display de la plataforma
 *
 * @return true Exito
 * @return false Error
 */
bool iniciarDisplay();

/**
 * @brief Actualiza el display de la plataforma
 *
 */
void actualizarDisplay();

/**
 * @brief Limpia el display de la plataforma
 *
 */
void limpiarDisplay();

/**
 * @brief Muestra un texto dado en una posicion dada (retiene el flujo)
 *
 * @param txt Texto
 * @param pos Posicion
 */
void mostrarTexto(char *txt, int pos);

/**
 * @brief Deja el texto en la posición data (no retiene)
 *
 * @param txt
 * @param pos
 * @param repetir
 */
void dejarTexto(char *txt, int pos, bool repetir);

/**
 * @brief Inicia muestreo de ranking en la plataforma
 *
 * @param txt
 */
void cargarRanking(void);

/**
 * @brief Bucle que muestra el ranking. Finaliza desde dentro, y hace que finalice el thread de ranking.
 *
 */
void mostrarRanking(void);

/**
 * @brief Inicializa los cretidos en la plataforma
 *
 */
void cargarCreditos(void);

/**
 * @brief Bucle que muestra los creditos. Finaliza desde dentro, y hace que finalice el thread de ranking.
 *
 * @return true No finaliz
 * @return false Finaliza
 */
void mostrarCreditos(void);

/**
 * @brief Reconfigura el display de la plataforma y lo habilita.
 *
 */
void reconfigurarDisplayON(void);

/**
 * @brief Reconfigura el display de la plataforma y lo deshabilita.
 *
 */
void reconfigurarDisplayOFF(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _DISPLAY_H_
