/**
 * @file ranking.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-30
 * 
 * @copyright Copyright (c) 2022
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

#define DEFAULT_PLAYER_NAME	"PLAYER"


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



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
void actualizarRanking(char *name, uint64_t score);

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
 * @return ulong Score
 */
ulong getJugadorRankingPuntos(char *name);

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
 * @return uint64_t* 
 */
ulong *getRankingPuntos(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _RANKING_H_
