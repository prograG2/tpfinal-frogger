/**
 * @file 	ranking.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo ranking.
 * 			Prototipos de funciones de interaccion con el ranking de jugadores.
 * 			Permite trabajar con el txt correspondiente fácilmente,
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _RANKING_H_
#define _RANKING_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define DEFAULT_PLAYER_NAME "PLAYER"

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa el sistema de ranking
 *
 */
void iniciarRanking(void);

/**
 * @brief Actualiza el ranking de un jugador dado
 *
 * @param name Nombre del jugador
 * @param score Puntos del jugador
 */
void actualizarRanking(char *name, uintmax_t score);

/**
 * @brief Desinicializa el sistema de ranking, actualizando el archivo correspondiente
 *
 */
void desiniciarRanking(void);

/**
 * @brief Verifica si el jugador existe en el ranking
 *
 * @param name Nombre del jugador
 * @return true Existe
 * @return false No existe
 */
bool verificarJugadorRanking(char *name);

/**
 * @brief Devuelve el puntaje de un jugador dado
 *
 * @param name Nombre del jugador
 * @return uintmax_t Score
 */
uintmax_t getJugadorRankingPuntos(char *name);

/**
 * @brief Devuelve cantidad de renglones del ranking
 *
 * @return int Renglones
 */
uint getRankingLineas(void);

/**
 * @brief Devuelve array de nombres de jugadores
 *
 * @return char**
 */
char **getRankingNombres(void);

/**
 * @brief Devuelve array de puntos de jugadores
 *
 * @return uintmax_t*
 */
uintmax_t *getRankingPuntos(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _RANKING_H_
