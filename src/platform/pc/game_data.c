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

#define INITIAL_RUN_TIME_LEFT   100



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
	int lives;			
	int score;		

	struct
	{
		int number;		    //numero de run actual
		int time_left;		//tiempo restante en la run
	} run;

	long frames;
	int timer_in_sec;

	int difficulty;

	char name[MAX_NAME_CHAR];

	unsigned char flag;

	bool goals[MAX_GOALS];

} data_t;

enum DATA_FLAGS
{
	DATA_FLAG_STARTING,
	DATA_FLAG_NEXT_RUN
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
 * @brief Verifica si todos los goals estan completos
 * 
 * @return true Si
 * @return false No
 */
static bool are_all_goals_full(void);

/**
 * @brief Dibuja "ranas facing down" en los puntos de llegada ya alcanzados
 * 
 */
static void draw_reached_goals(void);


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

	text_color = al_map_rgb(255,255,255);

	data_init();

}

void game_data_update(void)
{
	data_update();

}

void game_data_draw(void)
{
	hud_draw();
	draw_reached_goals();
}

int game_data_get_lives(void)
{
	return(data.lives);
}

void game_data_subtract_live(void)
{
	data.lives--;
}

int game_data_get_score(void)
{
	return(data.score);
}

void game_data_add_score(int add)
{
	if(add > 0)
		data.score += add;
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

long game_data_get_frames(void)
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

	else if(letter >= ALLEGRO_KEY_A && letter <= ALLEGRO_KEY_Z)
	{
		if(strlen(data.name) < MAX_NAME_CHAR)
		{
			letter += '@';
			strncat(data.name, &letter, 1);
			length++;
		}

		

	}	

	/*
	if(length > 0)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(100,100,100), 10, DISPLAY_H/2, 0,
					"Nombre del jugador: %s", data.name);
		
		al_flip_display();	
	}
	*/
	
}

char *game_data_get_name(void)
{
	return(&data.name);
}

bool game_data_get_goal_state(unsigned int goal)
{
	if(goal < MAX_GOALS)
		return data.goals[goal];
}

void game_data_set_goal(unsigned int goal)
{
	if(goal < MAX_GOALS)
		data.goals[goal] = true;
}

void game_data_reset_goals(void)
{
	int i;
	for(i = 0; i < MAX_GOALS; i++)
		data.goals[i] = false;
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
	data.run.time_left = INITIAL_RUN_TIME_LEFT;
	data.score = 0;
	data.timer_in_sec = 0;

	data.flag = DATA_FLAG_STARTING;

	game_data_reset_goals();
}

static void data_update(void)
{
	//diferencia entre el tiempo actual y el de referencia
	data.timer_in_sec = time(NULL) - time_ref;

	data.frames++;

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
		1, char_h + 2,              //Para que quede abaj de la puntuacion en pantalla.
		0,
		"Run: %02d",                    //2 cifras. No me acuerdo si esta bien asi.
		data.run.number);


	//Dibuja vidas.
	for(int i = 0; i < data.lives; i++)         //No se si la rana tiene 'frog.lives' pero aca va el equivalente.
		al_draw_bitmap(
			sprites.heart,
			//DISPLAY_W - SPRITE_SIZE_HEART * (data.lives - i), 1,         //Arriba a la derecha. 'LIFE_W' depende de la imagen que usemos.
			al_get_text_width(allegro_get_var_font(), "Score: xxxxxx") + 3*char_w + SPRITE_SIZE_HEART * (data.lives - i - 1), 2*char_w,
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
		
}

static bool are_all_goals_full(void)
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


 