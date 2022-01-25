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

//Nombres de los sprites
#define SPRITE_HEART				"minecraft_heart"
#define SPRITE_BACKGROUND			"sprite_background"
#define SPRITE_CAR_0				"sprite_car_0"
#define SPRITE_FLY					"sprite_fly"
#define SPRITE_FROG					"sprite_frog"
#define SPRITE_LOG					"sprite_log"
#define SPRITE_TURTLES				"sprite_turtles"
#define SPRITE_MENU_HOME_BACK		"sprite_menu_home_background"
#define SPRITE_MENU_HOME			"sprite_menu_home"
#define SPRITE_MENU_DIFF_BACK		"sprite_menu_home_background"
#define SPRITE_MENU_DIFF			"sprite_menu_home"
#define SPRITE_MENU_PAUSE_BACK		"sprite_menu_home_background"
#define SPRITE_MENU_PAUSE			"sprite_menu_home"
//#define SPRITE_MENU_DIFF_BACK		"sprite_menu_diff_background"
//#define SPRITE_MENU_DIFF			"sprite_menu_diff"
//#define SPRITE_MENU_PAUSE_BACK	"sprite_menu_pause_background"
//#define SPRITE_MENU_PAUSE			"sprite_menu_pause"

//Extensiones
#define EXTENSION_SOUND_SAMPLE		".wav"
#define EXTENSION_SOUND_STREAM		".opus"
#define EXTENSION_SPRITES			".png"

//Local paths
#define PATH_SOUND_STREAMS			"../res/sounds/streams/"
#define PATH_SOUND_SAMPLES			"../res/sounds/samples/"
#define PATH_FONTS					"../res/fonts/"
#define PATH_SPRITES				"../res/sprites/"
#define PATH_GIFS					"../res/gifs/"



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
 * @brief Devuelve puntero a string con el path de un sprite dado
 * 
 * @param file_name Nombre el sprite, sin extension
 * @return char* Puntero al path
 */

/**
 * @brief Devuelve puntero a string con el path de un sprite dado.
 * Permite destruir un string creado con la misma funcion
 * 
 * @param file_name Nombre del sprite, sin extension
 * @param prev_str String previamente creado, de ser necesario.
 * @return char* Puntero al path nuevo
 */
static char *make_sprite_path(char * file_name, char* prev_str);

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

static ALLEGRO_KEYBOARD_STATE key_state;

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

void save_keyboard_state(void)
{
	al_get_keyboard_state(&key_state);
}

bool check_keyboard_copy(unsigned char allegro_key_code)
{
	return(al_key_down(&key_state, allegro_key_code));
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

	char string[60] = PATH_FONTS;
	strcat(string, "ProFontWindows.ttf");
	//para usar la fuente builtin
	//allegro_vars.font = al_create_builtin_font();
	allegro_vars.font = al_load_font(string, FONT_HEIGHT, 0);
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
	allegro_vars.redraw = false;

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

ALLEGRO_EVENT_TYPE allegro_wait_for_event(void)
{
	al_wait_for_event(allegro_vars.queue, &allegro_vars.event);

	return(allegro_vars.event.type);
}

ALLEGRO_EVENT_TYPE allegro_get_next_event(void)
{
	bool flag = al_get_next_event(allegro_vars.queue, &allegro_vars.event);

	if(flag)
		return (allegro_vars.event.type);
	else
		return false;
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

void allegro_draw_menu_background(int window)
{
	al_draw_bitmap(sprites.menu[window].background, 0, 0, 0);
}

bool allegro_is_event_queue_empty(void)
{
	return(al_is_event_queue_empty(allegro_vars.queue));
}

ALLEGRO_EVENT_QUEUE* allegro_get_event_queue(void)
{
	return(allegro_vars.queue);
}

void allegro_set_var_event(ALLEGRO_EVENT event)
{
	allegro_vars.event = event;
}

#pragma region allegro_sound

#pragma region allegro_sound_set_stream
void allegro_sound_set_stream_credits(void)
{
	char file[] = SOUND_STREAM_FILE_CREDITS;

	//si ya estaba inicializado...
	if(strcmp(file, last_init_stream) == 0)
	{
		allegro_sound_pause_stream();
	}
	else
	{
		must_init(init_audio_stream(file, 1.0),
			"credtis stream");
	}
	
}

void allegro_sound_set_stream_main_menu(void)
{
	char file[] = SOUND_STREAM_FILE_MAIN;

	//si ya estaba inicializado...
	if(strcmp(file, last_init_stream) == 0)
	{
		allegro_sound_pause_stream();
	}
	else
	{
		must_init(init_audio_stream(file, 1.0),
			"credtis stream");
	}
}

void allegro_sound_set_stream_pause_menu(void)
{
	char file[] = SOUND_STREAM_FILE_PAUSE;

	//si ya estaba inicializado...
	if(strcmp(file, last_init_stream) == 0)
	{
		allegro_sound_pause_stream();
	}
	else
	{
		must_init(init_audio_stream(file, 1.0),
			"credtis stream");
	}
}

void allegro_sound_set_stream_playing(void)
{
	char file[] = SOUND_STREAM_FILE_PLAYING;

	//si ya estaba inicializado...
	if(strcmp(file, last_init_stream) == 0)
	{
		allegro_sound_pause_stream();
	}
	else
	{
		must_init(init_audio_stream(file, 1.0),
			"credtis stream");
	}
}

void allegro_sound_set_stream_rick(void)
{
	char file[] = SOUND_STREAM_FILE_RICK;

	//si ya estaba inicializado...
	if(strcmp(file, last_init_stream) == 0)
	{
		allegro_sound_pause_stream();
	}
	else
	{
		must_init(init_audio_stream(file, 1.0),
			"credtis stream");
	}
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
	int i, offset;
	pair_xy_t temp_xy;
	int temp_w, temp_h;

	char *path = NULL;

	//de la rana completo
	path = make_sprite_path(SPRITE_FROG, NULL);
	sprites.frog_uncut = al_load_bitmap(path);


	//se particiona el de la rana en sus 8 partes
	for(i = 0; i < FROG_FRAMES; i++)
	{
		temp_xy = geometry_get_pair_xy_frog_frame(i);

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
	path = make_sprite_path(SPRITE_BACKGROUND, path);
	sprites.background = al_load_bitmap(path);

	//el de los troncos
	path = make_sprite_path(SPRITE_LOG, path);
	sprites.log = al_load_bitmap(path);

	/*
	for(i = 0; i < CARS_TYPES; i++)
		sprites.car[i] = al_load_bitmap("sprite_car_0.png");
	*/
	//de los autos
	path = make_sprite_path(SPRITE_CAR_0, path);
	sprites.car[0] = al_load_bitmap(path);

	//el de las tortugas sin recortar
	path = make_sprite_path(SPRITE_TURTLES, path);
	sprites.turtle_uncut = al_load_bitmap(path);

	//se recortan los de la tortuga en sus 11 partes
	for(i = 0; i < TURTLE_FRAMES; i++)
	{
		temp_xy = geometry_get_pair_xy_turtle_frame(i);
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
	path = make_sprite_path(SPRITE_FLY, path);
	sprites.fly = al_load_bitmap(path);

	//corazon
	path = make_sprite_path(SPRITE_HEART, path);
	sprites.heart = al_load_bitmap(path);

	

	//fondo de menu		
	path = make_sprite_path(SPRITE_MENU_HOME_BACK, path);											
	sprites.menu[MENU_WINDOW_HOME].background = al_load_bitmap(path);

	//botones con highlight, sin recortar
	path = make_sprite_path(SPRITE_MENU_HOME, path);
	sprites.menu[MENU_WINDOW_HOME].uncut = al_load_bitmap(path);	
	
	//se recortan los highlight
	for(i = 0, offset = 0; i < MAX_MENU_STATES; i++, offset += MENU_OPTION_DELTA_Y)
	{
		sprites.menu[MENU_WINDOW_HOME].option[i] = sprite_cut(sprites.menu[MENU_WINDOW_HOME].uncut, 
													MENU_OPTION_TOPLEFT_X,
													MENU_OPTION_TOPLEFT_Y + offset, 
													MENU_OPTION_W, 
													MENU_OPTION_H);
	}


	path = make_sprite_path(SPRITE_MENU_DIFF_BACK, path);
	sprites.menu[MENU_WINDOW_DIFFICULTY].background = al_load_bitmap(path);

	path = make_sprite_path(SPRITE_MENU_DIFF, path);
	sprites.menu[MENU_WINDOW_DIFFICULTY].uncut = al_load_bitmap(path);
	
	for(i = 0, offset = 0; i < MAX_MENU_STATES; i++, offset += MENU_OPTION_DELTA_Y)
	{
		sprites.menu[MENU_WINDOW_DIFFICULTY].option[i] = sprite_cut(sprites.menu[MENU_WINDOW_DIFFICULTY].uncut, 
													MENU_OPTION_TOPLEFT_X,
													MENU_OPTION_TOPLEFT_Y + offset, 
													MENU_OPTION_W, 
													MENU_OPTION_H);
	}


	path = make_sprite_path(SPRITE_MENU_PAUSE_BACK, path);
	sprites.menu[MENU_WINDOW_PAUSE].background = al_load_bitmap(path);

	path = make_sprite_path(SPRITE_MENU_PAUSE, path);
	sprites.menu[MENU_WINDOW_PAUSE].uncut = al_load_bitmap(path);
	
	for(i = 0, offset = 0; i < MAX_MENU_STATES; i++, offset += MENU_OPTION_DELTA_Y)
	{
		sprites.menu[MENU_WINDOW_PAUSE].option[i] = sprite_cut(sprites.menu[MENU_WINDOW_PAUSE].uncut, 
													MENU_OPTION_TOPLEFT_X,
													MENU_OPTION_TOPLEFT_Y + offset, 
													MENU_OPTION_W, 
													MENU_OPTION_H);
	}


	free(path);
}

static char *make_sprite_path(char * file_name, char* prev_str)
{
	if(prev_str != NULL)
		free(prev_str);

	char *path = NULL;

	int str_size = sizeof(PATH_SPRITES) + strlen(file_name) + sizeof(EXTENSION_SPRITES) + 1;

	path = malloc(str_size);
	must_init(path, file_name);

	memset(path, 0, str_size);

	strcat(path, PATH_SPRITES);
	strcat(path, file_name);
	strcat(path, EXTENSION_SPRITES);

	return path;
}

static void sprites_deinit(void)
{
	int i, j;

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

	for(i = 0; i < MAX_MENU_WINDOWS; i++)
	{
		al_destroy_bitmap(sprites.menu[i].background);
		al_destroy_bitmap(sprites.menu[i].uncut);

		for(j = 0; j < MAX_MENU_STATES; j++)
		{
			al_destroy_bitmap(sprites.menu[i].option[j]);
		}
	}
	

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

	int str_size = sizeof(PATH_SOUND_STREAMS) + strlen(file) + sizeof(EXTENSION_SOUND_STREAM) + 1;
	char *path = NULL;

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
			path = malloc(str_size);
			must_init(path, file);
			memset(path, 0, str_size);
			strcat(path, PATH_SOUND_STREAMS);
			strcat(path, file);
			strcat(path, EXTENSION_SOUND_STREAM);

			//carga del stream
			*pt = al_load_audio_stream(path, 2, 2048);
			if(*pt == NULL)
				return false;

			free(path);

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

	int str_size = sizeof(PATH_SOUND_SAMPLES) + strlen(file) + sizeof(EXTENSION_SOUND_SAMPLE) + 1;
	char *path = NULL;

	path = malloc(str_size);
	must_init(path, file);
	memset(path, 0, str_size);
	strcat(path, PATH_SOUND_SAMPLES);
	strcat(path, file);
	strcat(path, EXTENSION_SOUND_SAMPLE);

	*sample = al_load_sample(path);

	free(path);

	if(*sample == NULL)
		return false;

	return true;
}
