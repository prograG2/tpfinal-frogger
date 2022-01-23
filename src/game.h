/**
 * @file game.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <time.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Set the Nombre object
 * 
 * @param nombre 
 */
void setNombre(char* nombre);

/**
 * @brief Set the Puntos object
 * 
 * @param puntos 
 */
void setPuntos(uint64_t puntos);

/**
 * @brief Set the Max Puntos object
 * 
 * @param max 
 */
void setMaxPuntos(uint64_t max);

/**
 * @brief Set the Max Vidas object
 * 
 */
void setMaxVidas();

/**
 * @brief Set the Tiempo Inicial object
 * 
 * @param tiempo 
 */
void setTiempoInicial(clock_t tiempo);

/**
 * @brief Set the Tiempo Limite object
 * 
 * @param limite 
 */
void setTiempoLimite(clock_t limite);

/**
 * @brief Set the Dificultad object
 * 
 * @param dif 
 */
void setDificultad(int dif);

/**
 * @brief Set the Tiempo object
 * 
 * @param tiempo 
 */
void setTiempo(clock_t tiempo);



/**
 * @brief Get the Nombre object
 * 
 * @return char* 
 */
char* getNombre();

/**
 * @brief Get the Puntos object
 * 
 * @return uint64_t 
 */
uint64_t getPuntos();

/**
 * @brief Get the Max Puntos object
 * 
 * @return uint64_t 
 */
uint64_t getMaxPuntos();

/**
 * @brief Get the Vidas object
 * 
 * @return int 
 */
int getVidas();

/**
 * @brief Get the Nivel object
 * 
 * @return int 
 */
int getNivel();

/**
 * @brief Get the Tiempo Inicial object
 * 
 * @return clock_t 
 */
clock_t getTiempoInicial();

/**
 * @brief Get the Tiempo Limite object
 * 
 * @return clock_t 
 */
clock_t getTiempoLimite();

/**
 * @brief Get the Dificultad object
 * 
 * @return int 
 */
int getDificultad();

/**
 * @brief Get the Agua object
 * 
 * @return int 
 */
int getAgua();



/**
 * @brief 
 * 
 */
void inicializarJuego();

/**
 * @brief 
 * 
 */
void inicializarNivel();

/**
 * @brief 
 * 
 */
void reiniciarNivel();

/**
 * @brief 
 * 
 */
void decrementarVida();

/**
 * @brief 
 * 
 */
void incrementarPuntos(int);

/**
 * @brief 
 * 
 */
void refrescarJugador();

/**
 * @brief 
 * 
 */
void refrescarAutos();

/**
 * @brief 
 * 
 */
void moverAdelante();

/**
 * @brief 
 * 
 */
void moverAtras();

/**
 * @brief 
 * 
 */
void moverIzda();

/**
 * @brief 
 * 
 */
void moverDcha();

/**
 * @brief 
 * 
 */
void respawn();

/**
 * @brief 
 * 
 */
void perderVidaChoque();

/**
 * @brief 
 * 
 */
void perderVidaAgua();

/**
 * @brief 
 * 
 */
void perderVidaTimeout();

/**
 * @brief 
 * 
 */
void llegada();

/**
 * @brief 
 * 
 */
void subirNivel();

/**
 * @brief 
 * 
 */
void actualizarInterfaz();

/**
 * @brief 
 * 
 */
void imprimirMapa();


/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_H_
