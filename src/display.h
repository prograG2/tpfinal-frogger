/**
 * @file display.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
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

enum posiciones_mensajes{POS_MSJ_MENU, POS_MSJ_DIFICULTAD, POS_MSJ_RANKING, POS_MSJ_NOMBRE, POS_MSJ_PASAR, POS_MSJ_PAUSA, POS_MSJ_NEW_HI_SCORE, POS_MSJ_GAME_OVER, POS_OPCION, POS_RANKING_2, POS_CREDITOS};


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
 * @brief 
 * 
 * @return int 
 */
int iniciarDisplay();

/**
 * @brief 
 * 
 */
void actualizarDisplay();

/**
 * @brief 
 * 
 */
void limpiarDisplay();

/**
 * @brief 
 * 
 * @param txt 
 * @param pos 
 */
void mostrarTexto(char* txt, int pos);

/**
 * @brief 
 * 
 * @param txt 
 * @param pos 
 */
void dejarTexto(char* txt, int pos, bool repetir);

/**
 * @brief 
 * 
 * @param posicion 
 * @param nombre 
 * @param puntos 
 */
void mostrarPosicion(char* posicion, char* nombre, char* puntos);

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
 * @brief Construct a new finalizar Creditos object
 * 
 */
void finalizarCreditos(void);

/**
 * @brief Construct a new reconfigurar Display object
 * 
 */
void reconfigurarDisplayON(void);

/**
 * @brief 
 * 
 */
void reconfigurarDisplayOFF(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _DISPLAY_H_
