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
#include <stdbool.h>


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
 * @brief Set the Max Puntos object
 * 
 * @param max 
 */
void setMaxPuntos(uint64_t max);

/**
 * @brief Set the Dificultad object
 * 
 * @param dif 
 */
void setDificultad(int dif);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool tiempoRefrescoEntidades(void);

/**
 * @brief  
 * 
 * @return true 
 * @return false 
 */
bool tiempoLimite(void);

/**
 * @brief Get the Nombre object
 * 
 * @return char* 
 */
char* getNombre(void);

/**
 * @brief Get the Puntos object
 * 
 * @return uint64_t 
 */
uint64_t getPuntos(void);

/**
 * @brief Get the Max Puntos object
 * 
 * @return uint64_t 
 */
uint64_t getMaxPuntos(void);


/**
 * @brief Get the Nivel object
 * 
 * @return int 
 */
int getNivel(void);

/**
 * @brief 
 * 
 */
void inicializarJuego(void);

/**
 * @brief 
 * 
 */
void reiniciarNivel(void);

/**
 * @brief 
 * 
 */

void pausarJuego(void);

/**
 * @brief 
 * 
 */
void refrescar(void);

/**
 * @brief 
 * 
 */
void moverAdelante(void);

/**
 * @brief 
 * 
 */
void moverAtras(void);

/**
 * @brief 
 * 
 */
void moverIzda(void);

/**
 * @brief 
 * 
 */
void moverDcha(void);

/**
 * @brief 
 * 
 */
void respawn(void);

/**
 * @brief 
 * 
 */
void perderVida(void);

/**
 * @brief 
 * 
 */
void actualizarInterfaz(void);

/**
 * @brief 
 * 
 */
void imprimirMapa(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _GAME_H_
