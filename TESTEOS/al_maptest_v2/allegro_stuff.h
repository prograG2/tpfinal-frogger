/**
 * @file allegro_stuff.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _ALLEGRO_STUFF_H_
#define _ALLEGRO_STUFF_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

#include "entities.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FPS 60

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum KEY_STATES
{
    KEY_RELEASED,
    KEY_JUST_PRESSED,
    KEY_PRESSED
};

/**
 * @brief Estructura principal de spritesheets
 * 
 */
typedef struct 
{
    ALLEGRO_BITMAP* frog_uncut;
    ALLEGRO_BITMAP* frog[8];

    ALLEGRO_BITMAP* background;

    ALLEGRO_BITMAP* log;

    ALLEGRO_BITMAP* car[CARS_TYPES];

    /*
    ALLEGRO_BITMAP* ship;
    ALLEGRO_BITMAP* ship_shot[2];
    ALLEGRO_BITMAP* life;

    ALLEGRO_BITMAP* alien[3];
    ALLEGRO_BITMAP* alien_shot;

    ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
    ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

    ALLEGRO_BITMAP* powerup[4];
    */
} sprites_t;

/*
typedef struct
{
    unsigned char type;
    unsigned char state;
} keys_t;
*/




/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

extern sprites_t sprites;


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa "cosas", y sale del programa si hay problemas, avisando dónde estuvo.
 * 
 * @param test Handler//booleano con status de la inicialización.
 * @param description String con la descripción/nombre de la "cosa" a inicializar.
 */
void must_init(bool test, const char *description);

/**
 * @brief Registra cambios en las teclas
 * 
 */
void keyboard_update(void);

/**
 * @brief Verifica el estado de una tecla
 * 
 * @param allegro_key_code Código de allegro para cada tecla
 * @return unsigned char KEY_RELEASED xor KEY_JUST_PRESSED xor KEY_PRESSED
 */
unsigned char keyboard_check_key(unsigned char allegro_key_code);

/**
 * @brief Registra que una tecla ya fue presionada. Agiliza la actualización de teclas.
 * 
 * @param allegro_key_code Código de allegro para cada tecla
 */
void keyboard_set_key(unsigned char allegro_key_code);

/**
 * @brief Inicializaciones de allegro. Si algo falla, lo notifica por consola y finaliza el programa.
 * 
 */
void allegro_inits(void);

/**
 * @brief Desinicializaciones de allegro.
 * 
 */
void allegro_deinits(void);

/**
 * @brief Espera a que ocurra un evento y lo devuelve
 * 
 * @return ALLEGRO_EVENT_TYPE 
 */
ALLEGRO_EVENT_TYPE allegro_wait_for_event(void);

/**
 * @brief Devuelve el evento de allegro
 * 
 * @return ALLEGRO_EVENT 
 */
ALLEGRO_EVENT allegro_get_var_event(void);

/**
 * @brief Devuelve flag de finalización del programa
 * 
 * @return true Finaliza
 * @return false No finaliza
 */
bool allegro_get_var_done(void);

/**
 * @brief Devuelve flag de renderización
 * 
 * @return true Renderiza
 * @return false No renderiza
 */
bool allegro_get_var_redraw(void);

/**
 * @brief Setea flag de finalización del programa
 * 
 * @param state true or false
 */
void allegro_set_var_done(bool state);

/**
 * @brief Setea flag de renderizacion
 * 
 * @param state true or false
 */
void allegro_set_var_redraw(bool state);

/**
 * @brief Devuelve la fuente de allegro
 * 
 * @return ALLEGRO_FONT 
 */
ALLEGRO_FONT* allegro_get_var_font(void);

/**
 * @brief Pone negro el display
 * 
 */
void allegro_clear_display(void);

/**
 * @brief Dibuja la imagen de fondo
 * 
 */
void allegro_draw_background(void);

/**
 * @brief Informa si al cola de eventos está vacía o no
 * 
 * @return true Vacía
 * @return false No vacía
 */
bool allegro_is_event_queue_empty(void);



/*******************************************************************************
 ******************************************************************************/

#endif // _ALLEGRO_STUFF_H_ 