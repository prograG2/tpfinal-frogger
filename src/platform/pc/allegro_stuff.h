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

    ALLEGRO_BITMAP* cars_uncut;
    ALLEGRO_BITMAP* car[CAR_TYPE_N];

    ALLEGRO_BITMAP* turtle_uncut;
    ALLEGRO_BITMAP* turtle[TURTLE_FRAMES];

    ALLEGRO_BITMAP* fly;

	ALLEGRO_BITMAP* heart;

	struct
	{
		ALLEGRO_BITMAP* uncut;
		ALLEGRO_BITMAP* option[MENU_STATE_MAX];
		ALLEGRO_BITMAP* background;
	} menu[MENU_WINDOW_MAX];

	ALLEGRO_BITMAP* credits;

	ALLEGRO_BITMAP* icon;

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
 * @brief Reinicializa el display de allegro
 * 
 */
void allegro_reinit_display(void);

/**
 * @brief Desinicializa el display
 * 
 */
void allegro_deinit_display(void);

/**
 * @brief Devuelve la ultima tecla presionada registrada
 * 
 * @return unsigned char ALLEGRO_KEY_CODE
 */
unsigned char allegro_get_last_key(void);

/**
 * @brief Setea una ultima tecla presionada
 * 
 * @param allegro_key_code ALLEGRO_KEY_CODE
 */
void allegro_set_last_key(unsigned char allegro_key_code);

/**
 * @brief Espera a que ocurra un evento y lo devuelve
 * 
 * @return ALLEGRO_EVENT_TYPE 
 */
ALLEGRO_EVENT_TYPE allegro_wait_for_event(void);

/**
 * @brief Devuelve el proximo evento de la cola, si es que existe. De no haber, devuele false.
 * 
 * @return ALLEGRO_EVENT* 
 */
ALLEGRO_EVENT* allegro_get_next_event(void);

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
bool allegro_is_event_queueVacia(void);

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
 * @brief Selecciona musica de ranking. Comienza pausada.
 * 
 */
void allegro_sound_set_stream_ranking(void);

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

/**
 * @brief Selecciona musica de game over. Comienza pausada.
 * 
 */
void allegro_sound_set_stream_game_over(void);

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

/**
 * @brief Aumenta en 0.1 la ganancia de stream
 * 
 */
void allegro_sound_set_stream_gain_up(void);

/**
 * @brief Reduce en 0.1 la ganancia de stream
 * 
 */
void allegro_sound_set_stream_gain_down(void);

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

/**
 * @brief Reproduce efecto de 'menu enter'
 * 
 */
void allegro_sound_play_effect_menu_enter(void);

/**
 * @brief Reproduce efecto de 'new_max_score'
 * 
 */
void allegro_sound_play_effect_new_max_score(void);

/**
 * @brief Reproduce efecto de 'saliendo'
 * 
 */
void allegro_sound_play_effect_exiting(void);

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


/**
 * @brief 
 * 
 */
void allegro_rick_on(void);

/**
 * @brief 
 * 
 */
bool allegro_get_rick_flag(void);

/**
 * @brief 
 * 
 * @param state 
 */
void allegro_set_rick_flag(bool state);

/**
 * @brief 
 * 
 */
void allegro_rick_off(void);

/**
 * @brief 
 * 
 */
void allegro_rick_draw(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _ALLEGRO_STUFF_H_ 