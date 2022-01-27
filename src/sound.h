/**
 * @file sound.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _SOUND_H_
#define _SOUND_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

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
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool iniciarSonido(void);

/**
 * @brief 
 * 
 */
void destruirSonido(void);


/**
 * @brief 
 * 
 */
void reproducir_musica_menu_ppal(void);

/**
 * @brief 
 * 
 */
void reproducir_musica_ranking(void);

/**
 * @brief 
 * 
 */
void reproducir_musica_creditos(void);

/**
 * @brief 
 * 
 */
void reproducir_musica_jugando(void);

/**
 * @brief 
 * 
 */
void reproducir_musica_menu_pausa(void);


/**
 * @brief 
 * 
 */
void reproducir_efecto_seleccion(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_salto(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_impacto(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_ahogado(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_poco_tiempo(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_meta(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_nivel_completo(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_nuevo_max_score(void);

/**
 * @brief 
 * 
 */
void reproducir_efecto_game_over(void);






/*******************************************************************************
 ******************************************************************************/

#endif // _SOUND_H_
