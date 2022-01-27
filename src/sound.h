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

enum musica{MUSICA_MENU_PPAL, MUSICA_RANKING, MUSICA_CREDITOS, MUSICA_JUGANDO, MUSICA_MENU_PAUSA, MUSICA_GAME_OVER, SIZEOF_MUSICA}
enum efectos{EFECTO_SELECCION, EFECTO_SALTO, EFECTO_IMPACTO, EFECTO_AHOGADO, EFECTO_POCO_TIEMPO, EFECTO_META, EFECTO_NIVEL_COMPLETO, EFECTO_NUEVO_MAX_SCORE, EFECTO_GAME_OVER, EFECTO_MENU_ENTER, SIZEOF_EFECTOS}

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
void pausar_musica(void);

/**
 * @brief 
 * 
 * @param
 */
void reproducir_musica(int musica);

/**
 * @brief 
 * 
 * @param
 */
void reproducir_efecto(int efecto);




/*******************************************************************************
 ******************************************************************************/

#endif // _SOUND_H_
