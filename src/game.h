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
 * @brief Get the Vidas object
 * 
 * @return int 
 */
int getVidas(void);

/**
 * @brief Get the Nivel object
 * 
 * @return int 
 */
int getNivel(void);

/**
 * @brief Get the Tiempo Inicial object
 * 
 * @return clock_t 
 */
clock_t getTiempoInicial(void);

/**
 * @brief Get the Tiempo Limite object
 * 
 * @return clock_t 
 */
clock_t getTiempoLimite(void);

/**
 * @brief Get the Dificultad object
 * 
 * @return int 
 */
int getDificultad(void);

/**
 * @brief Get the Agua object
 * 
 * @return int 
 */
int getAgua(void);



/**
 * @brief 
 * 
 */
void inicializarJuego(void);

/**
 * @brief 
 * 
 */
void inicializarNivel(void);

/**
 * @brief 
 * 
 */
void reiniciarNivel(void);

/**
 * @brief 
 * 
 */
void decrementarVida(void);

 
/**
 * @brief 
 * 
 * @param pt 
 */
void incrementarPuntos(int pt);

/**
 * @brief 
 * 
 */
void refrescar(void);

/**
 * @brief 
 * 
 */
void refrescarJugador(void);

/**
 * @brief 
 * 
 */
void refrescarAutos(void);

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
void perderVidaChoque(void);

/**
 * @brief 
 * 
 */
void perderVidaAgua(void);

/**
 * @brief 
 * 
 */
void perderVidaTimeout(void);

/**
 * @brief 
 * 
 */
void llegada(void);

/**
 * @brief 
 * 
 */
void subirNivel(void);

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
