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
#include <string.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

//Altura de la fuente
#define FONT_HEIGHT	20

//Nombres de los stream files
#define SOUND_STREAM_FILE_CREDITS 	"credits_theme"
#define SOUND_STREAM_FILE_MAIN		"main_menu_theme"
#define SOUND_STREAM_FILE_PAUSE		"pause_menu_theme"
#define SOUND_STREAM_FILE_PLAYING	"playing_theme"
#define SOUND_STREAM_FILE_RICK		"rick"

//Extensiones
#define EXTENSION_SOUND_SAMPLE		".wav"
#define EXTENSION_SOUND_STREAM		".opus"

//Local paths
#define PATH_SOUND_STREAMS			"media/sounds/streams/"
#define PATH_SOUND_SAMPLES			"media/sounds/samples/"

//Tamaño de array temporal para formar un path completo
#define PATH_ARRAY_SIZE				60


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
	int font_h;			//altura de un caracter
	int font_w;			//ancho de un caracter

	//variable evento
	ALLEGRO_EVENT event;

	//flag para salir el programa
	bool done;
	//flag para renderizar
	bool redraw;

} allegro_t;

typedef struct
{
	ALLEGRO_AUDIO_STREAM* stream;
	unsigned char stream_state;
    
	struct
	{
		ALLEGRO_SAMPLE* jump;
		ALLEGRO_SAMPLE* crash;
		ALLEGRO_SAMPLE* goal;
		ALLEGRO_SAMPLE* low_time;
		ALLEGRO_SAMPLE* click;
		ALLEGRO_SAMPLE* bonus;
		ALLEGRO_SAMPLE* run_completed;
		ALLEGRO_SAMPLE* drowned;
	} samples;

} sounds_t;

enum SOUND_STREAM_STATES
{
	SOUND_STREAM_STATE_NO_INIT,
	SOUND_STREAM_STATE_INIT,
	SOUND_STREAM_STATE_PAUSE,
	SOUND_STREAM_STATE_PLAY
};

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

//estructura con punteros a sprites
sprites_t sprites;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Copia parte de un spritesheet y lo devuelve como un nuevo bitmap
 *
 * @param source_bmp Puntero al bitmap original
 * @param x top left 'x' coord
 * @param y top left 'y' coord
 * @param w wide
 * @param h heigth
 * @param source_bmp
 * @return ALLEGRO_BITMAP*
 */
static ALLEGRO_BITMAP* sprite_cut(ALLEGRO_BITMAP* source_bmp, int x, int y, int w, int h);

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

/**
 * @brief Inicializa audios
 *
 */
static void audio_init(void);

/**
 * @brief Desinicializa audios
 *
 */
static void audio_deinit(void);

/**
 * @brief Inicialzia el stream (musica)
 * 
 * @param file Nombre del archivo (sin extension, sin path)
 * @param gain Ganancia (1.0 no afecta)
 * @return true Inicializacion correcta
 * @return false Error en la inicializacion
 */
static bool init_audio_stream(const char *file, float gain);

/**
 * @brief Inicializa un sample (efecto)
 * 
 * @param sample Sample a inicializar
 * @param file Nombre del archivo (sin extension, sin path)
 * @return true Inicializacion correcta
 * @return false Error en la inicializacion
 */
static bool init_sample(ALLEGRO_SAMPLE** sample, const char* file);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//variables principales de allegro
static allegro_t allegro_vars;

//arreglo para registrar el estado de cada tecla
static unsigned char key[ALLEGRO_KEY_MAX];

//variable con los sonidos/musicas del juego
static sounds_t sounds;

//nombre del ultimo stream inicializado
static char last_init_stream[30];

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void must_init(bool test, const char *description)
{
	if(!test)
	{
		printf("~no se pudo inicializar %s~\n", description);
		exit(EXIT_FAILURE);
	}
}

void keyboard_update(void)
{
	ALLEGRO_EVENT event = allegro_vars.event;

	switch(event.type)
	{
		case ALLEGRO_EVENT_KEY_CHAR:

			if(!event.keyboard.repeat)
				key[event.keyboard.keycode] = KEY_JUST_PRESSED;

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
	unsigned char state = key[allegro_key_code];

	if(state == KEY_JUST_PRESSED)
		key[allegro_key_code] = KEY_PRESSED;

	return(state);
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
	must_init(al_init_font_addon(), "font addon");
	must_init(al_init_ttf_addon(), "ttf addon");
   
	//timer que actualiza cada 1/60 segundos (60fps)
	allegro_vars.timer = al_create_timer(1.0 / FPS);
	must_init(allegro_vars.timer, "timer");

	//cola de eventos
	allegro_vars.queue = al_create_event_queue();
	must_init(allegro_vars.queue, "queue");

	

	//Inicializa los spritesheets.
	sprites_init();

	allegro_reinit_display();

	//para usar la fuente builtin
	//allegro_vars.font = al_create_builtin_font();
	//allegro_vars.font = al_load_font("media/RobotoRegular.ttf", 20, 0);
	allegro_vars.font = al_load_font("media/fonts/ProFontWindows.ttf", FONT_HEIGHT, 0);
	must_init(allegro_vars.font, "font");
	allegro_vars.font_h = al_get_font_line_height(allegro_vars.font);
	allegro_vars.font_w = al_get_text_width(allegro_vars.font, "a");

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

	//audio
	must_init(al_install_audio(), "audio");
	must_init(al_init_acodec_addon(), "audio codecs");
	must_init(al_reserve_samples(16), "reserve samples");

	audio_init();

	//inicializa timer
	al_start_timer(allegro_vars.timer);

}

void allegro_deinits(void)
{
	sprites_deinit();
	audio_deinit();
	al_destroy_font(allegro_vars.font);
	al_destroy_display(allegro_vars.disp);
	al_destroy_timer(allegro_vars.timer);
	al_destroy_event_queue(allegro_vars.queue);
}

void allegro_reinit_display(void)
{
	if(allegro_vars.disp != NULL)
		al_destroy_display(allegro_vars.disp);

	//creación del display
	allegro_vars.disp = al_create_display(DISPLAY_W, DISPLAY_H);
	must_init(allegro_vars.disp, "display");
	al_set_window_position (allegro_vars.disp, 200, 0);
	al_set_new_window_title ("~ Programación I ~ TP Final ~ Frogger ~");
	//opciones para el display (antialiasing)
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	
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

int allegro_get_var_font_h(void)
{
	return(allegro_vars.font_h);
}

int allegro_get_var_font_w(void)
{
	return(allegro_vars.font_w);
}

void allegro_clear_display(void)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void allegro_draw_background(void)
{
	al_draw_bitmap(sprites.background, 0, 0, 0);
}

void allegro_draw_menu_background(void)
{
	al_draw_bitmap(sprites.menu_background, 0, 0, 0);
}

bool allegro_is_event_queueVacia(void)
{
	return(al_is_event_queue_empty(allegro_vars.queue));
}

#pragma region allegro_sound

#pragma region allegro_sound_set_stream
void allegro_sound_set_stream_credits(void)
{
	must_init(init_audio_stream(SOUND_STREAM_FILE_CREDITS, 1.0),
			"credtis stream");
}

void allegro_sound_set_stream_main_menu(void)
{
	must_init(init_audio_stream(SOUND_STREAM_FILE_MAIN, 1.0),
			"main_menu stream");
}

void allegro_sound_set_stream_pause_menu(void)
{
	must_init(init_audio_stream(SOUND_STREAM_FILE_PAUSE, 1.0),
			"pause_menu stream");
}

void allegro_sound_set_stream_playing(void)
{
	must_init(init_audio_stream(SOUND_STREAM_FILE_PLAYING, 1.0),
			"playing stream");
}

void allegro_sound_set_stream_rick(void)
{
	must_init(init_audio_stream(SOUND_STREAM_FILE_RICK, 1.0),
			"rick stream");
}

#pragma endregion allegro_sound_set_stream

#pragma region allegro_sound_control
void allegro_sound_toggle_stream(void)
{
	if(sounds.stream_state != SOUND_STREAM_STATE_NO_INIT)
	{
		bool state = al_get_audio_stream_playing(sounds.stream);

		must_init(al_set_audio_stream_playing(sounds.stream, !state),
					"set to toggle stream");
					
		if(!state)
			sounds.stream_state = SOUND_STREAM_STATE_PAUSE;
		else
			sounds.stream_state = SOUND_STREAM_STATE_PLAY;
	}
}

void allegro_sound_play_stream(void)
{
	if(sounds.stream_state != SOUND_STREAM_STATE_NO_INIT)
	{
		al_set_audio_stream_playing(sounds.stream, true);
		sounds.stream_state = SOUND_STREAM_STATE_PLAY;
	}
}

void allegro_sound_pause_stream(void)
{
	if(sounds.stream_state != SOUND_STREAM_STATE_NO_INIT)
	{
		al_set_audio_stream_playing(sounds.stream, false);
		sounds.stream_state = SOUND_STREAM_STATE_PAUSE;
	}
}

void allegro_sound_restart_stream(void)
{
	if(sounds.stream_state != SOUND_STREAM_STATE_NO_INIT)
	{
		init_audio_stream(last_init_stream, 1.0);
	}
}

#pragma endregion allegro_sound_control

#pragma region allegro_sound_play_sample
void allegro_sound_play_effect_bonus(void)
{
	al_play_sample(sounds.samples.bonus, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_click(void)
{
	al_play_sample(sounds.samples.click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_crash(void)
{
	al_play_sample(sounds.samples.crash, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_drowned(void)
{
	al_play_sample(sounds.samples.drowned, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_goal(void)
{
	al_play_sample(sounds.samples.goal, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_jump(void)
{
	al_play_sample(sounds.samples.jump, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_low_time(void)
{
	al_play_sample(sounds.samples.low_time, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

void allegro_sound_play_effect_run_completed(void)
{
	al_play_sample(sounds.samples.run_completed, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
}

#pragma endregion allegro_sound_play_sample

#pragma endregion allegro_sound

void allegro_draw_hitbox(int x, int y, int w, int h)
{
	al_draw_rectangle(	x,
						y,
						x + w,
						y + h,
						al_map_rgb(100, 100, 100),
						1);		//grosor
}


/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static ALLEGRO_BITMAP* sprite_cut(ALLEGRO_BITMAP* source_bmp, int x, int y, int w, int h)
{
	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(source_bmp, x, y, w, h);
	must_init(sprite, "sprite cut");
	return sprite;
}

static void sprites_init(void)
{
	int i;
	pair_xy_t temp_xy;
	int temp_w, temp_h;

	//de la rana completo
	sprites.frog_uncut = al_load_bitmap("media/sprites/sprite_frog.png");

	//se particiona el de la rana en sus 8 partes
	for(i = 0; i < FROG_FRAMES; i++)
	{
		temp_xy = getXYFromFrogFrame(i);

		if(!(i%2))	//los sprites pares
		{
			temp_w = SPRITE_SIZE_FROG_STATIC_W;
			temp_h = SPRITE_SIZE_FROG_STATIC_H;
		}
		else if (i == 1 || i == 7)
		{
			temp_w = SPRITE_SIZE_FROG_DYNAMIC_SHORT;
			temp_h = SPRITE_SIZE_FROG_DYNAMIC_LONG;
		}
		else
		{
			temp_w = SPRITE_SIZE_FROG_DYNAMIC_LONG;
			temp_h = SPRITE_SIZE_FROG_DYNAMIC_SHORT;
		}

		sprites.frog[i] = sprite_cut(sprites.frog_uncut, temp_xy.x, temp_xy.y, temp_w, temp_h);
	}

	//el del fondo
	sprites.background = al_load_bitmap("media/sprites/sprite_background.png");

	//el de los troncos
	sprites.log = al_load_bitmap("media/sprites/sprite_log.png");

	/*
	for(i = 0; i < CARS_TYPES; i++)
		sprites.car[i] = al_load_bitmap("sprite_car_0.png");
	*/
	//de los autos
	sprites.car[0] = al_load_bitmap("media/sprites/sprite_car_0.png");

	//el de las tortugas sin recortar
	sprites.turtle_uncut = al_load_bitmap("media/sprites/sprite_turtles.png");

	//se recortan los de la tortuga en sus 11 partes
	for(i = 0; i < TURTLE_FRAMES; i++)
	{
		temp_xy = getXYFromTurtleFrame(i);
		int temp_side;

		if(i <= 7)
			temp_side = TURTLE_FRAME_ZERO_TO_SEVEN_SIDE;
		else if(i <= 9)
			temp_side = TURTLE_FRAME_EIGTH_TO_NINE_SIDE;
		else
			temp_side = TURTLE_FRAME_TEN_SIDE;

		sprites.turtle[i] = sprite_cut(sprites.turtle_uncut, temp_xy.x, temp_xy.y, temp_side, temp_side);
	}


	//el de la mosca
	sprites.fly = al_load_bitmap("media/sprites/sprite_fly.png");

	//el menu completo
	sprites.menu_uncut = al_load_bitmap("media/sprites/sprite_menu.png");

	//el menu dividido //AGREGAR sprite_cut(sprites.turtle_uncut, temp_xy.x, temp_xy.y, temp_side, temp_side);
	sprites.menu[0] = sprite_cut(sprites.menu_uncut, 45, 175, 600, 75);
	sprites.menu[1] = sprite_cut(sprites.menu_uncut, 45, 275, 600, 75);
	sprites.menu[2] = sprite_cut(sprites.menu_uncut, 45, 375, 600, 75);
	sprites.menu[3] = sprite_cut(sprites.menu_uncut, 45, 475, 600, 75);

	//el fonde del menu
	sprites.menu_background = al_load_bitmap("media/sprites/sprite_menu_background.png");
	//corazon
	sprites.heart = al_load_bitmap("media/sprites/minecraft_heart.png");

}

static void sprites_deinit(void)
{
	int i;

	al_destroy_bitmap(sprites.frog_uncut);

	for(i = 0; i < FROG_FRAMES; i++)
		al_destroy_bitmap(sprites.frog[i]);

	al_destroy_bitmap(sprites.background);

	al_destroy_bitmap(sprites.log);

	for(i = 0; i < CARS_TYPES; i++)
		al_destroy_bitmap(sprites.car[i]);

	al_destroy_bitmap(sprites.turtle_uncut);

	for(i = 0; i < TURTLE_FRAMES; i++)
		al_destroy_bitmap(sprites.turtle[i]);

	al_destroy_bitmap(sprites.fly);

	al_destroy_bitmap(sprites.heart);

	al_destroy_bitmap(sprites.menu_uncut);

	for(i = 0; i < 4; i++)
		al_destroy_bitmap(sprites.menu[i]);

	al_destroy_bitmap(sprites.menu_background);

}

static void keyboard_init(void)
{
	memset(key, 0, ALLEGRO_KEY_MAX);
}

static void audio_init(void)
{
	//streams
	sounds.stream_state = SOUND_STREAM_STATE_NO_INIT;

	//efectos de sonido
	must_init(init_sample(&sounds.samples.bonus, "bonus_alert"),
				"effect_bonus sample");

	must_init(init_sample(&sounds.samples.click, "click"),
				"effect_click sample");
	
	must_init(init_sample(&sounds.samples.crash, "crash"),
				"effect_crash sample");

	must_init(init_sample(&sounds.samples.drowned, "fall_in_water"),
				"effect_drowned sample");

	must_init(init_sample(&sounds.samples.goal, "goal_reached"),
				"effect_goal sample");
	
	must_init(init_sample(&sounds.samples.jump, "jump_original"),
				"effect_jump sample");

	must_init(init_sample(&sounds.samples.low_time, "low_time"),
				"effect_low_time sample");
	
	must_init(init_sample(&sounds.samples.run_completed, "run_completed"),
				"effect_run_completed sample");

}

static void audio_deinit(void)
{
	if(sounds.stream_state != SOUND_STREAM_STATE_NO_INIT)
		al_destroy_audio_stream(sounds.stream);

	al_destroy_sample(sounds.samples.bonus);
	al_destroy_sample(sounds.samples.click);
	al_destroy_sample(sounds.samples.crash);
	al_destroy_sample(sounds.samples.drowned);
	al_destroy_sample(sounds.samples.goal);
	al_destroy_sample(sounds.samples.jump);
	al_destroy_sample(sounds.samples.low_time);
	al_destroy_sample(sounds.samples.run_completed);

}

static bool init_audio_stream(const char *file, float gain)
{
	if(file == NULL)
		return false;


	ALLEGRO_AUDIO_STREAM** pt = &sounds.stream;
	unsigned char* state = &sounds.stream_state;

	char path[PATH_ARRAY_SIZE] = PATH_SOUND_STREAMS;

	//analisis de reproduccion y carga de stream "para que no explote todo"
	switch (*state)
	{
		case SOUND_STREAM_STATE_PLAY:
			//pausa
			al_set_audio_stream_playing(*pt, false);

		case SOUND_STREAM_STATE_PAUSE:
			//desacople del mixer
			al_detach_audio_stream(*pt);
			//destruccion
			al_destroy_audio_stream(*pt);
	
		case SOUND_STREAM_STATE_NO_INIT:
			//armado del path del archivo
			strcat(path, file);
			strcat(path, EXTENSION_SOUND_STREAM);

			//carga del stream
			*pt = al_load_audio_stream(path, 2, 2048);
			if(*pt == NULL)
				return false;

			//modo de reproduccion
			al_set_audio_stream_playmode(*pt, ALLEGRO_PLAYMODE_LOOP);

			//ganancia
			al_set_audio_stream_gain(*pt, gain);

			//pausa
			al_set_audio_stream_playing(*pt, false);

			//"para que suene" (acople al mixer)
			al_attach_audio_stream_to_mixer(sounds.stream, al_get_default_mixer());

			//actualiza el nombre del ultimo stream inicializado
			strcpy(last_init_stream, file);
				
			*state = SOUND_STREAM_STATE_PAUSE;
			break;
		
		default:
			break;
	}

	return true;
}

static bool init_sample(ALLEGRO_SAMPLE** sample, const char* file)
{
	if(file == NULL)
		return false;

	char path[PATH_ARRAY_SIZE] = PATH_SOUND_SAMPLES;
	strcat(path, file);
	strcat(path, EXTENSION_SOUND_SAMPLE);

	*sample = al_load_sample(path);

	if(*sample == NULL)
		return false;

	return true;
}

