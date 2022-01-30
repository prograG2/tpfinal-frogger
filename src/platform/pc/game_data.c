/**
 * @file game_data.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
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

#define MAX_NAME_CHAR		20

#define MAX_LIVES           3

#define SCORE_PER_GOAL		500		//puntaje por llegar a la meta
#define SCORE_PER_GOAL_FLY	750		//puntaje por llegar a la meta con mosca
#define SCORE_PER_RUN		1000	//puntaje por completar una run

#define INITIAL_RUN_TIME_LEFT   	15		

#define EXTRA_TIME_PER_GOAL			10		//10s extras por llegar a una meta
#define EXTRA_TIME_PER_BONUS_GOAL	15		//15s extras por llegar a una meta con fly

#define TIME_LEFT_WARNING			10		//warning 10s antes del timeout



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
	int lives;			
	int score;		
	int score_max;

	struct
	{
		int number;		    //numero de run actual
		int time_left;		//tiempo restante en la run
		int time;			//tiempo de la run actual
		long time_ref;		//referencia de tiempo global de la run
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
	DATA_FLAG_TIME_EXCEEDED
};


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


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
 * @brief Cambia el tiempo inicial de una run nueva
 * 
 * @param time_left Tiempo inicial a setear
 */
static void set_new_run_time_left(int time_left);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//Datos internos del juego
static data_t data;

//Referencia temporal del inicio del juego
static long time_ref;

static int char_h;	//altura de un caracter
static int char_w;	//ancho de un caracter

static ALLEGRO_COLOR text_color;

static bool flag_low_time_warning;

static int last_loop_time;

static int new_run_time_left;


/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void gamedataInicializar(void)
{
	time_ref = time(NULL);

	char_h = allegro_get_var_font_h();
	char_w = allegro_get_var_font_w();

	text_color = al_map_rgb(255,255,255);

	flag_low_time_warning = false;

	new_run_time_left = INITIAL_RUN_TIME_LEFT;

	data_init();

}

void gamedataActualizar(void)
{
	data_update();

	if(data.flag == DATA_FLAG_NEXT_RUN)
	{
		next_run();
		data.flag = DATA_FLAG_STARTING;
	}

	if(data.run.time_left < 0)
	{
		data.flag = DATA_FLAG_TIME_EXCEEDED;
	}

	if(data.run.time_left == TIME_LEFT_WARNING && !flag_low_time_warning)
	{
		allegro_sound_play_effect_low_time();

		flag_low_time_warning = true;
	}
	else if(data.run.time_left < TIME_LEFT_WARNING)
		flag_low_time_warning = false;
		


}

void gameDataRenderizar(void)
{
	hud_draw();
	draw_reached_goals();
}

int getVidas(void)
{
	return(data.lives);
}

void quitarVida(void)
{
	data.lives--;
}

int getScore(void)
{
	return(data.score);
}

void game_data_add_score(void)
{

	data.score += SCORE_PER_GOAL;
}

void game_data_add_score_bonus(void)
{

	data.score += SCORE_PER_GOAL_FLY;
}

void game_data_set_score_max(int score)
{
	data.score_max = score;
}

int game_data_get_score_max(void)
{
	return data.score_max;
}

int game_data_get_run_number(void)
{
	return(data.run.number);
}

void game_data_next_run(void)
{
	data.flag = DATA_FLAG_NEXT_RUN;
}

int game_data_get_run_time_left(void)
{
	return(data.run.time_left);
}

void game_data_add_run_time_goal(void)
{
	data.run.time_left += EXTRA_TIME_PER_GOAL;
}

void game_data_add_run_time_goal_bonus(void)
{
	data.run.time_left += EXTRA_TIME_PER_BONUS_GOAL;
}

unsigned long game_data_get_frames(void)
{
	return(data.frames);
}

int game_data_get_timer_in_sec(void)
{
	return(data.timer_in_sec);
}

void game_data_set_diff(int diff)
{
	data.difficulty = diff;
}

int game_data_get_diff(void)
{
	return(data.difficulty);
}

void game_data_clear_name(void)
{
	memset(data.name, 0, MAX_NAME_CHAR);
}

void game_data_add_name_letter(char letter)
{
	int length = strlen(data.name);

	if((letter == ALLEGRO_KEY_BACKSPACE) && (length > 0))
	{
		data.name[length - 1] = 0;
	}

	else if(letter >= ALLEGRO_KEY_A && letter <= ALLEGRO_KEY_Z && length < MAX_NAME_CHAR)
	{
		letter += '@';
		data.name[length] = letter;
		data.name[length + 1] = 0;
	}	
	
}

char *game_data_get_name(void)
{
	return(data.name);
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
	for(i = 0; i < MAX_GOALS; i++)
		data.goals[i] = false;
}

bool game_data_get_time_left_flag(void)
{
	if(data.flag == DATA_FLAG_TIME_EXCEEDED)
	{
		data.flag = DATA_FLAG_STARTING;
		return true;
	}
		
	else
		return false;
}

bool game_data_are_goals_full(void)
{
	bool state = true;

	int i;
	for(i = 0; i < MAX_GOALS; i++)
	{
		//si alguno esa vacio...
		if(!data.goals[i])
		{
			state = false;
			break;
		}
	}
	
	return state;
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
	

	//diferencia entre el tiempo actual y el de referencia
	data.timer_in_sec = time(NULL) - time_ref;
	data.frames++;


	data.run.time = time(NULL) - data.run.time_ref;

	if(data.run.time > last_loop_time)
	{
		data.run.time_left--;
		last_loop_time++;
	}
	last_loop_time = data.run.time;

	
}

static void hud_draw(void)
{
	//Dibuja la puntuacion en pantalla.

	int i;
	static int score_display;

	//Graduacion del score a mostrar para que vaya incrementando de apoco
	if(score_display != data.score)
	{	
		int shifter;

		for(i = 2, shifter = 0; i > 0; i--)
		{
			shifter = 1 << i;
			if(score_display <= (data.score - shifter))
				score_display += shifter;
		}

	}

	al_draw_textf(
		allegro_get_var_font(),
		text_color,        //Negro porque por ahora sigue el fondo blanco, sino recomiendo amarillo (255, 255, 51).
		1, 1,                       //Arriba a la izquierda.
		0,
		"Score: %06d",                    //6 cifras (por ahi es mucho).
		score_display);

	//Dibuja el numero de vuelta.
	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		1, CELL_H - char_h - 5,              //Para que quede abaj de la puntuacion en pantalla.
		0,
		"Run: %02d",                    //2 cifras. No me acuerdo si esta bien asi.
		data.run.number);


	//Dibuja vidas.
	for(int i = 0; i < data.lives; i++)         //No se si la rana tiene 'frog.lives' pero aca va el equivalente.
		al_draw_bitmap(
			sprites.heart,
			//DISPLAY_W - SPRITE_SIZE_HEART * (data.lives - i), 1,         //Arriba a la derecha. 'LIFE_W' depende de la imagen que usemos.
			al_get_text_width(allegro_get_var_font(), "Score: xxxxxx") + 3*char_w + SPRITE_SIZE_HEART * (data.lives - i - 1),
			CELL_H - char_h - 5,
			0);
			
	if(!data.lives)
		al_draw_text(
			allegro_get_var_font(),
			al_map_rgb(255, 255, 51),       //Amarillo, es el color que mas se ditingue en general.
			DISPLAY_W / 2, DISPLAY_H / 2,
			ALLEGRO_ALIGN_CENTER,           //Para que se dibuje en el medio.
			"G A M E  O V E R");

	//Segundos.
	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		al_get_text_width(allegro_get_var_font(), "Score: xxxxxx") + 3*char_w, 1,
		0,
		"Played Time: %04d",
		data.timer_in_sec);

	//Tiempo restante
	al_draw_textf(
		allegro_get_var_font(),
		text_color,
		DISPLAY_W - 300,
		CELL_H - char_h - 5,
		0,
		"Time Left: %03d",
		data.run.time_left);
		
}

static void draw_reached_goals(void)
{
	int i;
	for(i = 0; i < MAX_GOALS; i++)
	{
		//si algun goal fue alcanzado...
		if(data.goals[i])
			al_draw_bitmap(sprites.frog[6],
							goal_cols[i]*CELL_W + FROG_OFFSET_X - 1,
							CELL_H + FROG_OFFSET_Y + GOAL_ROW_OFFSET_Y_FIX,
							0);
	}
}

static void next_run(void)
{
	data.run.number++;
	data.run.time_left = new_run_time_left;
	data.run.time = 0;
	data.run.time_ref = time(NULL);

	last_loop_time = 0;

	flag_low_time_warning = false;

	game_data_reset_goals();
}

static void set_new_run_time_left(int time_left)
{
	new_run_time_left = time_left;
}



 