/**
 * @file 	game.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * 			
 * @brief 	Header del modulo game
 * 			Vinculo entre la fsm y las plataformas en lo que respecta
 * 			a la informacion del jugador y el progreso del juego.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Confirma el nombre del jugador
 * 
 * @param nombre 
 */
void setNombre(char* nombre);


/**
 * @brief Setea los puntos maximos del jugador
 * 
 * @param max 
 */
void setMaxPuntos(unsigned long long max);

/**
 * @brief Setea la dificultad a usar
 * 
 * @param dif 
 */
void setDificultad(int dif);

/**
 * @brief Chequea si es tiempo de refrescar entidades según la plataforma
 * 
 * @return true 
 * @return false 
 */
bool tiempoRefrescoEntidades(void);

/**
 * @brief Devuelve el nombre del jugador
 * 
 * @return char* 
 */
char* getNombre(void);

/**
 * @brief Devuelve el puntaje del jugador
 * 
 * @return unsigned long long 
 */
unsigned long long getPuntos(void);

/**
 * @brief Devuelve el puntaje máximo del jugador
 * 
 * @return unsigned long long 
 */
unsigned long long getMaxPuntos(void);

/**
 * @brief Devuelve el nivel//run del jugador
 * 
 * @return int 
 */
int getNivel(void);

/**
 * @brief Rutina que se ejecuta al comenzar a jugar, luego de ingresar el nombre
 * 
 */
void inicializarJuego(void);

/**
 * @brief Configuraciones para reiniciar el nivel
 * 
 */
void reiniciarNivel(void);

/**
 * @brief Pausa el juego
 * 
 */
void pausarJuego(void);

/**
 * @brief Saca el juego de pausa
 * 
 */
void reanudarJuego(void);

/**
 * @brief Actualizaciones relativas a actualizar las entidades
 * 
 */
void refrescar(void);

/**
 * @brief Avanza el jugador
 * 
 */
void moverAdelante(void);

/**
 * @brief Retrocede el jugador
 * 
 */
void moverAtras(void);

/**
 * @brief Mueve el jugador a la izquierda
 * 
 */
void moverIzda(void);

/**
 * @brief Mueve el jugador a la derecha
 * 
 */
void moverDcha(void);

/**
 * @brief Respawnea el jugador
 * 
 */
void respawn(void);

/**
 * @brief Resta una vida
 * 
 */
void perderVida(void);

/**
 * @brief Actualizaciones relativas a lo visual
 * 
 */
void actualizarInterfaz(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_H_
