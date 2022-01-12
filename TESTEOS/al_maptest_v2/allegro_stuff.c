/**
 * @file allegro_stuff.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "allegro_stuff.h"
#include "geometry.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
	////timer que actualiza cada 1/60 segundos (60fps)
	ALLEGRO_TIMER* timer;

	//cola de eventos
	ALLEGRO_EVENT_QUEUE* queue;

	//display
	ALLEGRO_DISPLAY* disp;

	//fuente builtin
	ALLEGRO_FONT* font;
	
	//variable evento
	ALLEGRO_EVENT event;	

	//flag para salir el programa
	bool done;
	//flag para renderizar
	bool redraw;
	
} allegro_t;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

sprites_t sprites;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Copia parte de un spritesheet y lo devuelve como un nuevo bitmap
 * 
 * @param x top left 'x' coord
 * @param y top left 'y' coord
 * @param w wide
 * @param h heigth
 * @return ALLEGRO_BITMAP* 
 */
static ALLEGRO_BITMAP* sprite_cut(int x, int y, int w, int h);

/**
 * @brief Inicializa los sprites a usar
 * 
 */
static void sprites_init(void);

/**
 * @brief Destruye los sprites a usar
 * 
 */
static void sprites_deinit(void);

/**
 * @brief Inicializa variable de tecla
 * 
 */
static void keyboard_init(void);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//variables principales de allegro
static allegro_t allegro_vars;

static unsigned char key[ALLEGRO_KEY_MAX];


/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void must_init(bool test, const char *description)
{
	if(test) return;

	printf("~no se pudo inicializar %s~\n", description);
	exit(1);
}

void keyboard_update(void)
{
	ALLEGRO_EVENT event = allegro_vars.event;

	switch(event.type)
	{
		case ALLEGRO_EVENT_KEY_CHAR:
			
			if(!event.keyboard.repeat)
				key[event.keyboard.keycode] = KEY_JUST_PRESSED;
			else
				key[event.keyboard.keycode] = KEY_PRESSED;

			break;

		case ALLEGRO_EVENT_KEY_UP:
			key[event.keyboard.keycode] = KEY_RELEASED;

			break;

		default:
			break;
	}
	
}

unsigned char keyboard_check_key(unsigned char allegro_key_code)
{
	return(key[allegro_key_code]);
}

void keyboard_set_key(unsigned char allegro_key_code)
{
	key[allegro_key_code] = KEY_PRESSED;
}

void allegro_inits(void)
{
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_install_mouse(), "mouse");
	must_init(al_init_image_addon(), "image");

	//timer que actualiza cada 1/60 segundos (60fps)
	allegro_vars.timer = al_create_timer(1.0 / FPS);
	must_init(allegro_vars.timer, "timer");

	//cola de eventos
	allegro_vars.queue = al_create_event_queue();
	must_init(allegro_vars.queue, "queue");

	//opciones para el display (antialiasing)
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	//Inicializa los spritesheets.
	sprites_init();

	//creación del display
	allegro_vars.disp = al_create_display(DISPLAY_W, DISPLAY_H);
	must_init(allegro_vars.disp, "display");
	al_set_window_position (allegro_vars.disp, 200, 0);
	al_set_new_window_title ("~ Programación I ~ TP Final ~ Frogger ~");
	
	//para usar la fuente builtin
	allegro_vars.font = al_create_builtin_font();
	must_init(allegro_vars.font, "font");

	//para dibujar figuras primitivas (círculos, rectángulos, líneas, rellenos o no, etc.)
	must_init(al_init_primitives_addon(), "primitives");

	//registra eventos posibles
	al_register_event_source(allegro_vars.queue, al_get_keyboard_event_source());
	al_register_event_source(allegro_vars.queue, al_get_display_event_source(allegro_vars.disp));
	al_register_event_source(allegro_vars.queue, al_get_timer_event_source(allegro_vars.timer));
	al_register_event_source(allegro_vars.queue, al_get_mouse_event_source());  

	//flag para salir el programa
	allegro_vars.done = false;	
	//flag para renderizar	
	allegro_vars.redraw = true;		

	//inicializa teclado
	keyboard_init();

	//inicializa timer
	al_start_timer(allegro_vars.timer);

}

void allegro_deinits(void)
{
	sprites_deinit();
	al_destroy_font(allegro_vars.font);
	al_destroy_display(allegro_vars.disp);
	al_destroy_timer(allegro_vars.timer);
	al_destroy_event_queue(allegro_vars.queue);
}

ALLEGRO_EVENT_TYPE allegro_wait_for_event(void)
{
	al_wait_for_event(allegro_vars.queue, &allegro_vars.event);
	
	return(allegro_vars.event.type);
}

ALLEGRO_EVENT allegro_get_var_event(void)
{
	return(allegro_vars.event);
}

bool allegro_get_var_done(void)
{
	return(allegro_vars.done);
}

bool allegro_get_var_redraw(void)
{
	return(allegro_vars.redraw);
}

void allegro_set_var_done(bool state)
{
	allegro_vars.done = state;
}

void allegro_set_var_redraw(bool state)
{
	allegro_vars.redraw = state;
}

ALLEGRO_FONT* allegro_get_var_font(void)
{
	return(allegro_vars.font);
}

void allegro_clear_display(void)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void allegro_draw_background(void)
{
	al_draw_bitmap(sprites.background, 0, 0, 0);
}

bool allegro_is_event_queue_empty(void)
{
	return(al_is_event_queue_empty(allegro_vars.queue));
}

/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static ALLEGRO_BITMAP* sprite_cut(int x, int y, int w, int h)
{
	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites.frog_uncut, x, y, w, h);
	must_init(sprite, "sprite cut");
	return sprite;
}

static void sprites_init(void)
{
	sprites.frog_uncut = al_load_bitmap("sprite_frog.png");

	sprites.frog[0] = sprite_cut(16, 16, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
	sprites.frog[1] = sprite_cut(79, 15, SPRITE_SIZE_FROG_DYNAMIC_SHORT, SPRITE_SIZE_FROG_DYNAMIC_LONG);
	sprites.frog[2] = sprite_cut(16, 79, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
	sprites.frog[3] = sprite_cut(65, 79, SPRITE_SIZE_FROG_DYNAMIC_LONG, SPRITE_SIZE_FROG_DYNAMIC_SHORT);
	sprites.frog[4] = sprite_cut(14, 141, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
	sprites.frog[5] = sprite_cut(76, 141, SPRITE_SIZE_FROG_DYNAMIC_LONG, SPRITE_SIZE_FROG_DYNAMIC_SHORT);
	sprites.frog[6] = sprite_cut(16, 204, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
	sprites.frog[7] = sprite_cut(79, 190, SPRITE_SIZE_FROG_DYNAMIC_SHORT, SPRITE_SIZE_FROG_DYNAMIC_LONG);

	sprites.background = al_load_bitmap("sprite_background.png");

	sprites.log = al_load_bitmap("sprite_log.png");
}

static void sprites_deinit(void)
{
	int i;

	al_destroy_bitmap(sprites.frog_uncut);

	for(i = 0; i < 8; i++)
	{
		al_destroy_bitmap(sprites.frog[i]);
	}

	al_destroy_bitmap(sprites.background);

	al_destroy_bitmap(sprites.log);
	
}

static void keyboard_init(void)
{
	memset(key, 0, ALLEGRO_KEY_MAX);
}

 