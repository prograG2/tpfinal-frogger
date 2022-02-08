/**
 * @file 	game_data.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo game_data. Inicializa, actualiza y muestra los datos
 * 			del juego en PC.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "game_data.h"
#include <stdio.h>
#include <time.h>
#include "geometry.h"
#include "allegro_stuff.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MAX_NAME_CHAR 20

#define MAX_LIVES 3

#define SCORE_PER_GOAL 500		// puntaje por llegar a la meta
#define SCORE_PER_GOAL_COIN 750 // puntaje por llegar a la meta con coin
#define SCORE_PER_RUN 1000		// puntaje por completar una run

#define INITIAL_RUN_TIME_LEFT 60 //tiempo inicial de una partida
#define RUN_TIME_LEFT_REDUCE_FACTOR_A 2 //reduccion A
#define RUN_TIME_LEFT_REDUCE_LIMIT_A 5 //por cuantas runs usar la reduccion A
#define RUN_TIME_LEFT_REDUCE_FACTOR_B 5 //reduccion B
#define RUN_TIME_LEFT_REDUCE_UNTIL 10 //tiempo mínimo a tener

#define EXTRA_TIME_PER_GOAL 10		 // 10s extras por llegar a una meta
#define EXTRA_TIME_PER_BONUS_GOAL 15 // 15s extras por llegar a una meta con coin

#define TIME_LEFT_WARNING 10 // warning 10s antes del timeout

#define HUD_EXTRA_INFO_TIMING 120 // frames que duran los mensajes emergentes
#define HUD_EXTRA_INFO_RATE 1	  // "velocidad" de desplazamiento de mensajes

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
	int lives;
	unsigned long long score;
	unsigned long long score_max;

	struct
	{
		int number;	   // numero de run actual
		int time_left; // tiempo restante en la run
		int time;	   // tiempo de la run actual
		long time_ref; // referencia de tiempo global de la run
	} run;

	unsigned long frames;
	int timer_in_sec;

	int difficulty;

	char name[MAX_NAME_CHAR];

	unsigned char flag;

	bool goals[MAX_GOALS];

} data_t;

enum DATA_FLAGS
{
	DATA_FLAG_STARTING,
	DATA_FLAG_NEXT_RUN,
	DATA_FLAG_TIME_EXCEEDED,
	DATA_FLAG_GAME_OVER
};

// Tipos de mensajes emergentes en el HUD
enum HUD_EXTRAS
{
	HUD_EXTRA_TIME,
	HUD_EXTRA_SCORE,
	HUD_EXTRA_RUN,
	HUD_EXTRAS_MAX
};

// Estructura para el manejo de mensajes emergentes en el HUD
static struct
{
	bool flag;	 // Activado ó no
	int value;	 // Valor extra a mostrar
	int timer;	 // Contador interno para dejar de mostrar
	int shifter; // Contador interno para desplazar el mensaje verticalmente
} hud_extra_stuff[HUD_EXTRAS_MAX];

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa datos internos
 *
 */
static void data_init(void);

/**
 * @brief Actualiza datos internos
 *
 */
static void data_update(void);

/**
 * @brief Dibuja el HUD (datos in-game)
 *
 */
static void hud_draw(void);

/**
 * @brief Dibuja "ranas facing down" en los puntos de llegada ya alcanzados
 *
 */
static void draw_reached_goals(void);

/**
 * @brief Configura variables para comenzar otra run
 *
 */
static void next_run(void);

/**
 * @brief Configura el HUD para mostrar mensaje emergente de tiempo ganado
 *
 * @param extra Tiempo extra
 */
static void trigger_show_adding_time(int extra);

/**
 * @brief Configura el HUD para mostrar mensaje emergente de score ganado
 * 
 * @param extra Score extra
 */
static void trigger_show_adding_score(int extra);

/**
 * @brief Configura el HUD para mostrar mensaje emergente de run incrementada
 * 
 */
static void trigger_show_adding_run(void);

/**
 * @brief Muestra tiempo extra en el HUD
 * 
 */
static void draw_extra_time(void);

/**
 * @brief Muestra score extra en el HUD
 * 
 */
static void draw_extra_score(void);

/**
 * @brief Muestra run ganada en el HUD
 * 
 */
static void draw_extra_run(void);

/**
 * @brief Reduce el nuevo tiempo inicial de un run al superar una
 * 
 */
static void progress_run_time_left(void);

/**
 * @brief Checkea si queda un solo goal por completar
 * 
 * @return true Si
 * @return false No
 */
static bool is_last_goal(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Datos internos del juego
static data_t data;

// Referencia temporal del inicio del juego
static long time_ref;

static int char_h; // altura de un caracter
static int char_w; // ancho de un caracter

static ALLEGRO_COLOR text_color;

// Flag para triggear sonido de poco tiempo
static bool flag_low_time_warning;

// Auxiliar para hacer acciones en los cambios de segundos
static int last_loop_time;

// Tiempo restante inicial de una nueva run. Se puede modificar externamente
static int new_run_time_left;

// Auxiliar para mostrar el score gradualmente en el HUD
static unsigned long long score_display;

// Score maximo no actualizado en game over
static unsigned long long max_score_no_updated;

/*******************************************************************************
 *******************************************************************************
            GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void game_data_init(void)
{
	time_ref = time(NULL);

	char_h = allegro_get_var_font_h();
	char_w = allegro_get_var_font_w();

	text_color = al_map_rgb(255, 255, 255);

	flag_low_time_warning = false;

	new_run_time_left = INITIAL_RUN_TIME_LEFT;

	score_display = 0;

	int i;
	for(i = 0; i < HUD_EXTRAS_MAX; i++)
		hud_extra_stuff[i].flag = false;

	data_init();
}

void game_data_update(void)
{
	data_update();

	if (data.flag == DATA_FLAG_NEXT_RUN)
	{
		next_run();
		data.flag = DATA_FLAG_STARTING;
	}

	if (data.run.time_left == TIME_LEFT_WARNING && !flag_low_time_warning)
	{
		allegro_sound_play_effect_low_time();

		flag_low_time_warning = true;
	}
	else if (data.run.time_left < TIME_LEFT_WARNING)
		flag_low_time_warning = false;

	if (max_score_no_updated != data.score_max)
		max_score_no_updated = data.score_max;

	if (data.run.time_left == 0)
	{
		// data.flag = DATA_FLAG_TIME_EXCEEDED;
		game_data_subtract_live();
		allegro_sound_play_effect_no_time();
		data.flag = DATA_FLAG_GAME_OVER;
	}

	if (data.lives == 0)
	{
		data.flag = DATA_FLAG_GAME_OVER;
	}
	
}

void game_data_draw(void)
{
	hud_draw();
	draw_reached_goals();
}

int game_data_get_lives(void)
{
	return (data.lives);
}

void game_data_subtract_live(void)
{
	data.lives--;
}

unsigned long long game_data_get_score(void)
{
	return (data.score);
}

void game_data_add_score(void)
{
	unsigned long long adder = SCORE_PER_GOAL + 250*(game_data_get_diff() - 1);

	data.score += adder;
	if(!is_last_goal())
		trigger_show_adding_score(adder);
}

void game_data_add_score_bonus(void)
{
	unsigned long long adder = SCORE_PER_GOAL_COIN + 250*(game_data_get_diff() - 1);

	data.score += adder;
	if(!is_last_goal())
		trigger_show_adding_score(adder);
}

void game_data_set_score_max(unsigned long long score)
{
	data.score_max = score;
}

unsigned long long game_data_get_score_max(void)
{
	return data.score_max;
}

int game_data_get_run_number(void)
{
	return (data.run.number);
}

void game_data_next_run(void)
{
	data.flag = DATA_FLAG_NEXT_RUN;
}

int game_data_get_run_time_left(void)
{
	return (data.run.time_left);
}

void game_data_add_run_time_goal(void)
{
	data.run.time_left += EXTRA_TIME_PER_GOAL;
	
	if(!is_last_goal())
		trigger_show_adding_time(EXTRA_TIME_PER_GOAL);
}

void game_data_add_run_time_goal_bonus(void)
{
	data.run.time_left += EXTRA_TIME_PER_BONUS_GOAL;

	if(!is_last_goal())
		trigger_show_adding_time(EXTRA_TIME_PER_BONUS_GOAL);
}

unsigned long game_data_get_frames(void)
{
	return (data.frames);
}

int game_data_get_timer_in_sec(void)
{
	return (data.timer_in_sec);
}

void game_data_set_diff(int diff)
{
	data.difficulty = diff;
}

int game_data_get_diff(void)
{
	return (data.difficulty);
}

void game_data_clear_name(void)
{
	memset(data.name, 0, MAX_NAME_CHAR);
}

void game_data_overwrite_name(char *name)
{
	int i;
	for(i = 0; name[i] != '\0'; i++)
		data.name[i] = name[i];

	//strcpy(data.name, name);
}

void game_data_add_name_letter(char letter)
{
	int length = strlen(data.name);

	if ((letter == ALLEGRO_KEY_BACKSPACE) && (length > 0))
	{
		data.name[length - 1] = 0;
	}

	else if (letter >= ALLEGRO_KEY_A && letter <= ALLEGRO_KEY_Z && length < MAX_NAME_CHAR)
	{
		letter += '@';
		data.name[length] = letter;
		data.name[length + 1] = 0;
	}
}

char *game_data_get_name(void)
{
	return (data.name);
}

bool game_data_get_goal_state(unsigned int goal)
{
	return data.goals[goal];
}

void game_data_set_goal(unsigned int goal)
{
	data.goals[goal] = true;
}

void game_data_reset_goals(void)
{
	int i;
	for (i = 0; i < MAX_GOALS; i++)
		data.goals[i] = false;
}

bool game_data_get_game_over_flag(void)
{
	if (data.flag == DATA_FLAG_GAME_OVER)
		return true;
	else
		return false;
}

bool game_data_are_goals_full(void)
{
	bool state = true;

	int i;
	for (i = 0; i < MAX_GOALS; i++)
	{
		// si alguno esa vacio...
		if (!data.goals[i])
		{
			state = false;
			break;
		}
	}

	return state;
}

unsigned long long game_data_get_old_max_score(void)
{
	return max_score_no_updated;
}

/*******************************************************************************
 *******************************************************************************
            LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void data_init(void)
{
	data.frames = 0;
	data.lives = MAX_LIVES;
	data.run.number = 0;
	data.run.time_left = new_run_time_left;
	data.run.time = 0;
	data.run.time_ref = time(NULL);
	data.score = 0;
	data.timer_in_sec = 0;

	data.flag = DATA_FLAG_STARTING;

	last_loop_time = 0;

	game_data_reset_goals();
}

static void data_update(void)
{

	// diferencia entre el tiempo actual y el de referencia
	data.timer_in_sec = time(NULL) - time_ref;
	data.frames++;

	data.run.time = time(NULL) - data.run.time_ref;

	if (data.run.time > last_loop_time)
	{
		data.run.time_left--;
		last_loop_time++;
	}
	last_loop_time = data.run.time;
}

static void hud_draw(void)
{
	// Dibuja la puntuacion en pantalla.

	int i;

	// Graduacion del score a mostrar para que vaya incrementando de apoco
	if (score_display != data.score)
	{
		int shifter;

		for (i = 2, shifter = 0; i > 0; i--)
		{
			shifter = 1 << i;
			if (score_display <= (data.score - shifter))
				score_display += shifter;
		}
	}

	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		1, 1, // Arriba a la izquierda.
		0,
		"Score: %06lld", // 6 cifras (por ahi es mucho).
		score_display);

	draw_extra_score();

	// Dibuja el numero de vuelta.
	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		1, CELL_H - char_h - 5, // Para que quede abaj de la puntuacion en pantalla.
		0,
		"Run: %02d", // 2 cifras. No me acuerdo si esta bien asi.
		data.run.number);

	draw_extra_run();

	// Segundos.
	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		al_get_text_width(allegro_get_var_font(), "Score: xxxxxx") + 3 * char_w, 1,
		0,
		"Played Time: %04d",
		data.timer_in_sec);

	// Tiempo restante
	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		al_get_text_width(allegro_get_var_font(), "Score: xxxxxx") + 3 * char_w,
		CELL_H - char_h - 5,
		0,
		"Time Left: %03d",
		data.run.time_left);

	draw_extra_time();

	// Dibuja vidas.
	for (int i = 0; i < data.lives; i++) // No se si la rana tiene 'frog.lives' pero aca va el equivalente.
		al_draw_bitmap(
			sprites.heart,
			DISPLAY_W - 100 + SPRITE_SIZE_HEART * (data.lives - i - 1),
			(CELL_H - char_h - 5) / 2,
			0);
}

static void draw_reached_goals(void)
{
	int i;
	for (i = 0; i < MAX_GOALS; i++)
	{
		// si algun goal fue alcanzado...
		if (data.goals[i])
			al_draw_bitmap(sprites.frog[6],
						   goal_cols[i] * CELL_W + FROG_OFFSET_X - 1,
						   CELL_H + FROG_OFFSET_Y + GOAL_ROW_OFFSET_Y_FIX,
						   0);
	}
}

static void next_run(void)
{
	data.run.number++;

	progress_run_time_left();
	data.run.time_left = new_run_time_left;

	data.run.time = 0;
	data.run.time_ref = time(NULL);

	unsigned long long adder = SCORE_PER_RUN + 250*(game_data_get_diff() - 1);

	data.score += adder;
	trigger_show_adding_score(adder);

	last_loop_time = 0;

	flag_low_time_warning = false;

	trigger_show_adding_run();

	game_data_reset_goals();
}

static void trigger_show_adding_time(int extra)
{
	hud_extra_stuff[HUD_EXTRA_TIME].flag = true;
	hud_extra_stuff[HUD_EXTRA_TIME].value = extra;
	hud_extra_stuff[HUD_EXTRA_TIME].timer = 1;
	hud_extra_stuff[HUD_EXTRA_TIME].shifter = 0;
}

static void trigger_show_adding_score(int extra)
{
	hud_extra_stuff[HUD_EXTRA_SCORE].flag = true;
	hud_extra_stuff[HUD_EXTRA_SCORE].value = extra;
	hud_extra_stuff[HUD_EXTRA_SCORE].timer = 1;
	hud_extra_stuff[HUD_EXTRA_SCORE].shifter = 0;
}

static void trigger_show_adding_run()
{
	hud_extra_stuff[HUD_EXTRA_RUN].flag = true;
	hud_extra_stuff[HUD_EXTRA_RUN].value = 1;
	hud_extra_stuff[HUD_EXTRA_RUN].timer = 1;
	hud_extra_stuff[HUD_EXTRA_RUN].shifter = 0;
}

static void draw_extra_time(void)
{
	if (hud_extra_stuff[HUD_EXTRA_TIME].flag)
	{
		al_draw_textf(
			allegro_get_var_font(),
			text_color,
			al_get_text_width(allegro_get_var_font(), "Score: xxxxxx") + 3 * char_w +
				al_get_text_width(allegro_get_var_font(), "Time left: "),
			CELL_H - char_h - 5 + hud_extra_stuff[HUD_EXTRA_TIME].shifter,
			0,
			"%+3d",
			hud_extra_stuff[HUD_EXTRA_TIME].value);

		hud_extra_stuff[HUD_EXTRA_TIME].shifter += HUD_EXTRA_INFO_RATE;

		if (!(hud_extra_stuff[HUD_EXTRA_TIME].timer++ % HUD_EXTRA_INFO_TIMING))
			hud_extra_stuff[HUD_EXTRA_TIME].flag = false;
	}
}

static void draw_extra_score(void)
{
	if (hud_extra_stuff[HUD_EXTRA_SCORE].flag)
	{
		al_draw_textf(
			allegro_get_var_font(),
			text_color,
			1 + al_get_text_width(allegro_get_var_font(), "Score: "),
			1 + hud_extra_stuff[HUD_EXTRA_SCORE].shifter,
			0,
			"%+6d",
			hud_extra_stuff[HUD_EXTRA_SCORE].value);

		hud_extra_stuff[HUD_EXTRA_SCORE].shifter += HUD_EXTRA_INFO_RATE;

		if (!(hud_extra_stuff[HUD_EXTRA_SCORE].timer++ % HUD_EXTRA_INFO_TIMING))
			hud_extra_stuff[HUD_EXTRA_SCORE].flag = false;
	}
}

static void draw_extra_run(void)
{
	if (hud_extra_stuff[HUD_EXTRA_RUN].flag)
	{
		al_draw_textf(
			allegro_get_var_font(),
			text_color,
			1 + al_get_text_width(allegro_get_var_font(), "Run: "),
			CELL_H - char_h - 5 + hud_extra_stuff[HUD_EXTRA_RUN].shifter,
			0,
			"%+2d",
			hud_extra_stuff[HUD_EXTRA_RUN].value);

		hud_extra_stuff[HUD_EXTRA_RUN].shifter += HUD_EXTRA_INFO_RATE;

		if (!(hud_extra_stuff[HUD_EXTRA_RUN].timer++ % HUD_EXTRA_INFO_TIMING))
			hud_extra_stuff[HUD_EXTRA_RUN].flag = false;
	}
}

static void progress_run_time_left(void)
{

	//Si la run es menor a la evaluada...
	if(data.run.number <= RUN_TIME_LEFT_REDUCE_LIMIT_A)
	{
		new_run_time_left -= RUN_TIME_LEFT_REDUCE_FACTOR_A;
		trigger_show_adding_time(-RUN_TIME_LEFT_REDUCE_FACTOR_A);
	}

	//Si el tiempo restante actual es mayor al mínimo establecido...
	else if(new_run_time_left > RUN_TIME_LEFT_REDUCE_UNTIL)
	{
		new_run_time_left -= RUN_TIME_LEFT_REDUCE_FACTOR_B;
		trigger_show_adding_time(-RUN_TIME_LEFT_REDUCE_FACTOR_B);
	}
	
}

static bool is_last_goal(void)
{
	int i, j;
	for(i = 0, j = 0; i < MAX_GOALS; i++)
	{
		if(data.goals[i])
			j++;
	}
	//Si es el ultimo goal...
	if(j == MAX_GOALS)
		return true;
	else
		return false;
}