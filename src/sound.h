/**
 * @file 	sound.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo sound
 * 			Vinculo entre la fsm y las plataformas en lo que respecta
 * 			al sonido.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _SOUND_H_
#define _SOUND_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Musicas a usar
enum musica
{
    MUSICA_MENU_PPAL,
    MUSICA_RANKING,
    MUSICA_CREDITOS,
    MUSICA_JUGANDO,
    MUSICA_MENU_PAUSA,
    MUSICA_GAME_OVER,
    SIZEOF_MUSICA
};

// Efectos a usar
enum efectos
{
    EFECTO_SELECCION,
    EFECTO_SALTO,
    EFECTO_IMPACTO,
    EFECTO_AHOGADO,
    EFECTO_POCO_TIEMPO,
    EFECTO_META,
    EFECTO_NIVEL_COMPLETO,
    EFECTO_NUEVO_MAX_SCORE,
    EFECTO_MENU_ENTER,
    EFECTO_SALIENDO,
    EFECTO_SIN_TIEMPO,
    SIZEOF_EFECTOS
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa el sonido de la plataforma
 *
 * @return true Exito
 * @return false Error
 */
bool iniciarSonido(void);

/**
 * @brief Desinicializa el sonido de la plataforma
 *
 */
void destruirSonido(void);

/**
 * @brief Pausa la musica actual
 *
 */
void pausarMusica(void);

/**
 * @brief Pone a reproducir una musica dada
 *
 * @param int enum musica
 */
void reproducirMusica(int musica);

/**
 * @brief Pone a reproducir un efecto dado
 *
 * @param int num efectos
 */
void reproducirEfecto(int efecto);

/*******************************************************************************
 ******************************************************************************/

#endif // _SOUND_H_
