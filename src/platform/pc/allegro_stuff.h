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
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdio.h>

#include "entities.h"
#include "geometry.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FPS 60

#define CHECK_KEY(key) (keyboard_check_key(key) == KEY_JUST_PRESSED)
//#define CHECK_KEY(key)	(keyboard_check_key(key))

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum KEY_STATES
{
    KEY_RELEASED,
    KEY_JUST_PRESSED,
    KEY_PRESSED
};

typedef struct
{
	
} sprites_menu_t;

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

    ALLEGRO_BITMAP* turtle_uncut;
    ALLEGRO_BITMAP* turtle[TURTLE_FRAMES];

    ALLEGRO_BITMAP* fly;

	ALLEGRO_BITMAP* heart;

	struct
	{
		ALLEGRO_BITMAP* uncut;
		ALLEGRO_BITMAP* option[MAX_MENU_STATES];
		ALLEGRO_BITMAP* background;
	} menu[MAX_MENU_WINDOWS];
    

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


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

//estructura con punteros a sprites
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
 * @brief Guarda el estado del teclado en el momento de la invocacion
 * 
 */
void save_keyboard_state(void);

/**
 * @brief Verifica si se presionó una tecla, consultando en la copia del teclado
 * 
 * @param allegro_key_code Tecla a consultar
 * @return true 
 * @return false 
 */
bool check_keyboard_copy(unsigned char allegro_key_code);

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
 * @brief Devuelve el proximo evento de la cola, si es que existe. De no haber, devuele false.
 * 
 * @return ALLEGRO_EVENT_TYPE 
 */
ALLEGRO_EVENT_TYPE allegro_get_next_event(void);

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
 * @brief Devuelve el alto de un caracter de la funete usada
 * 
 * @return int alto
 */
int allegro_get_var_font_h(void);

/**
 * @brief Devuelve ancho de un caracter de la fuente usada
 * 
 * @return int ancho
 */
int allegro_get_var_font_w(void);

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
 * @brief Dibuja imagen de fondo de un menu dado (sin highlight en ninguna opcion)
 * 
 * @param window enum MENU_WINDOWS
 */
void allegro_draw_menu_background(int window);

/**
 * @brief Informa si al cola de eventos está vacía o no
 * 
 * @return true Vacía
 * @return false No vacía
 */
bool allegro_is_event_queue_empty(void);

/**
 * @brief Devuelve puntero a la cola de eventos
 * 
 */
ALLEGRO_EVENT_QUEUE* allegro_get_event_queue(void);

/**
 * @brief Carga un evento de allegro
 * 
 * @param event 
 */
void allegro_set_var_event(ALLEGRO_EVENT event);

#pragma region allegro_sound

#pragma region allegro_sound_set_stream
/**
 * @brief Selecciona musica de creditos. Comienza pausada.
 * 
 */
void allegro_sound_set_stream_credits(void);

/**
 * @brief Selecciona musica de menu. Comienza pausada.
 * 
 */
void allegro_sound_set_stream_main_menu(void);

/**
 * @brief Selecciona musica de pausa. Comienza pausada.
 * 
 */
void allegro_sound_set_stream_pause_menu(void);

/**
 * @brief Selecciona musica de jugando. Comienza pausada.
 * 
 */
void allegro_sound_set_stream_playing(void);

/**
 * @brief 
 * 
 */
void allegro_sound_set_stream_rick(void);

#pragma endregion allegro_sound_set_stream

#pragma region allegro_sound_control
/**
 * @brief Cambia estado de reproduccion de la musica actual, si hay alguna seleccionada.
 * 
 */
void allegro_sound_toggle_stream(void);

/**
 * @brief Reproduce la musica actual, si hay alguna seleccionada.
 * 
 */
void allegro_sound_play_stream(void);

/**
 * @brief Pausa la musica actual, si hay alguna seleccionada.
 * 
 */
void allegro_sound_pause_stream(void);

/**
 * @brief Reinicia la musica actual, si hay alguna seleccionada.
 * 
 */
void allegro_sound_restart_stream(void);

#pragma endregion allegro_sound_control

#pragma region allegro_sound_play_sample
/**
 * @brief Reproduce efecto de bonus
 * 
 */
void allegro_sound_play_effect_bonus(void);

/**
 * @brief Reproduce efecto de click (seleccion de menu//aceptar//etc.)
 * 
 */
void allegro_sound_play_effect_click(void);

/**
 * @brief Reproduce efecto de choque
 * 
 */
void allegro_sound_play_effect_crash(void);

/**
 * @brief Reproduce efecto de ahogado (toco agua)
 * 
 */
void allegro_sound_play_effect_drowned(void);

/**
 * @brief Reproduce efecto de 'llego a la meta'
 * 
 */
void allegro_sound_play_effect_goal(void);

/**
 * @brief Reproduce efecto de salto
 * 
 */
void allegro_sound_play_effect_jump(void);

/**
 * @brief Reproduce efecto de 'queda poco tiempo'
 * 
 */
void allegro_sound_play_effect_low_time(void);

/**
 * @brief Reproduce efecto de 'run completada' (llego 5 veces a la meta)
 * 
 */
void allegro_sound_play_effect_run_completed(void);

#pragma endregion allegro_sound_play_sample

#pragma endregion allegro_sound

/**
 * @brief Dibuja un contorno rectangular
 * 
 * @param x Topleft x
 * @param y Topleft y
 * @param w Ancho
 * @param h Largo
 */
void allegro_draw_hitbox(int x, int y, int w, int h);


/*******************************************************************************
 ******************************************************************************/

#endif // _ALLEGRO_STUFF_H_ 