/**
 * @file entities.c
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

#include "entities.h"
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
	int x;
	int y;
	int moving;
	int facing;
	int steps;
	unsigned char surface;
	int lives;

} frog_t;

typedef struct
{
	int x;
	int y;
	int dx;
	bool on_screen;

} car_t;

typedef struct
{
	int x;
	int y;
	int dx;
	unsigned char route;
	bool on_screen;

} log_t;



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Detecta si un rectángulo está dentro de un tronco
 * 
 * @param i Número de log
 * @param x topleft corner x
 * @param y topleft corner y
 * @param w Ancho
 * @param h Alto
 * @return true Está dentro
 * @return false Está fuera
 */
static bool inside_log(int i, int x, int y, int w, int h);

/**
 * @brief Toma un log y lo spawnea
 * 
 * @param i Número de log
 */
void spawn_log(int i);

/**
 * @brief Alinea y centra la posición de la rana con las celdas del mapa, por desvios sobre troncos.
 * 
 */
void fix_frog_pos(void);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static frog_t frog;
static log_t log[MAX_LOGS];
static car_t car[MAX_CARS];


/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void frog_init(void)
{
	frog.x = CELL_START_FROG_X;
	frog.y = CELL_START_FROG_Y;
	frog.moving = false;
	frog.facing = UP;
	frog.steps = 0;
	frog.surface = CHILL;
	frog.lives = MAX_LIVES;
}

void frog_update(void)
{
	if(!frog.moving)
	{
		if(keyboard_check_key(ALLEGRO_KEY_LEFT) == KEY_JUST_PRESSED)
		{
			frog.facing = LEFT;
			frog.moving = true;
			keyboard_set_key(ALLEGRO_KEY_LEFT);
		}     
		else if(keyboard_check_key(ALLEGRO_KEY_RIGHT) == KEY_JUST_PRESSED)
		{
			frog.facing = RIGHT;
			frog.moving = true;
			keyboard_set_key(ALLEGRO_KEY_RIGHT);
		}     
		else if(keyboard_check_key(ALLEGRO_KEY_UP) == KEY_JUST_PRESSED)
		{
			frog.facing = UP;
			frog.moving = true;
			keyboard_set_key(ALLEGRO_KEY_UP);
		}  
		else if(keyboard_check_key(ALLEGRO_KEY_DOWN) == KEY_JUST_PRESSED)
		{
			frog.facing = DOWN;
			frog.moving = true;
			keyboard_set_key(ALLEGRO_KEY_DOWN);
		}
	}

	else if (frog.moving)
	{
	
		if(frog.facing == LEFT)
			frog.x -= STEP_FRACTION_SIZE;
		else if(frog.facing == RIGHT)
			frog.x += STEP_FRACTION_SIZE;
		else if(frog.facing == UP)
			frog.y -= STEP_FRACTION_SIZE;
		else if(frog.facing == DOWN)
			frog.y += STEP_FRACTION_SIZE;


		if(++frog.steps == STEP_RATIO)
		{
			frog.steps = 0;
			frog.moving = false;

			//fix_frog_pos();	
		}
	}

	//if colision, y otros.

	int i;
	for(i = 0; i < MAX_LOGS; i++)
	{
		if(!log[i].on_screen)
			continue;
		
		if(inside_log(i, frog.x, frog.y, FROG_W, FROG_H))
		{
			//printf("COLLIDE CON %d", i);
			frog.surface = LOG;
			frog.x += log[i].dx;
			break;
		}
	}

	if(frog.x < FROG_MIN_X)
		frog.x = FROG_MIN_X;
	if(frog.x > FROG_MAX_X)
		frog.x = FROG_MAX_X;
	if(frog.y < FROG_MIN_Y)
		frog.y = FROG_MIN_Y;
	if(frog.y > FROG_MAX_Y)
		frog.y = FROG_MAX_Y;


}

void frog_draw(void)
{

	ALLEGRO_BITMAP* tempbitmap;

	if(frog.moving)
	{
		if(frog.facing == UP)
			tempbitmap = sprites.frog[1];
		if(frog.facing == DOWN)
			tempbitmap = sprites.frog[7];
		if(frog.facing == RIGHT)
			tempbitmap = sprites.frog[3];
		if(frog.facing == LEFT)
			tempbitmap = sprites.frog[5];

	}

	else if(!frog.moving)
	{
		if(frog.facing == UP)
			tempbitmap = sprites.frog[0];
		if(frog.facing == DOWN)
			tempbitmap = sprites.frog[6];
		if(frog.facing == RIGHT)
			tempbitmap = sprites.frog[2];
		if(frog.facing == LEFT)
			tempbitmap = sprites.frog[4];

	}


	al_draw_bitmap(tempbitmap, frog.x, frog.y, 0);
	al_draw_rectangle(frog.x, frog.y, frog.x + FROG_W, frog.y + FROG_W, al_map_rgb(100, 100, 100), 1);

}

void logs_init(void)
{
	int i;
	srand(time(NULL));

	for(i = 0; i < MAX_LOGS; i++)
	{
		printf("%d~", get_rand_between(2, 6));
		log[i].route = get_rand_between(2, 6);

		switch (log[i].route)
		{
			case 3:
			case 5:
			case 7:
				log[i].dx = LOGS_BASE_SPEED;
				break;
			
			case 2:
			case 4:
			case 6:
				log[i].dx = -LOGS_BASE_SPEED;
				break;	
			
			default:
				break;
		}

		log[i].on_screen = false;
		log[i].y = CELL_TOPLEFT_Y + log[i].route * CELL_H + LOG_OFFSET_Y;   
	}

}

void logs_update(void)
{
	int i;
	int cont_logs_on_screen;
	static int last_log_on_screen;

	srand(time(NULL));
	int random_val = get_rand_between(1,2);
	
	for(i = 0, cont_logs_on_screen = 0; i < MAX_LOGS; i++)
	{
		if(log[i].on_screen)
		{
			cont_logs_on_screen++;

			log[i].x += log[i].dx;

			if(log[i].dx < 0)
			{
				if(log[i].x <= (-1)*LOG_W)
				{
					cont_logs_on_screen--;
					log[i].on_screen = false;
				}
					
			}

			else if(log[i].dx > 0)
			{
				if(log[i].x >= DISPLAY_W)
				{
					cont_logs_on_screen--;
					log[i].on_screen = false;
				}
					
			}
			
			
		}
			
	}

	//Solo la primera vez
	if(!cont_logs_on_screen)
	{
		spawn_log(0);
		last_log_on_screen = 0;
	}

	else if(cont_logs_on_screen < MAX_LOGS_ON_SCREEN)
	{
	  
		if(log[last_log_on_screen].x > CELL_W * random_val)
		{

			if(last_log_on_screen == MAX_LOGS - 1)
			{
				spawn_log(last_log_on_screen = 0);
			}

			else
			{
				spawn_log(++last_log_on_screen);
			}
		}
		
	}
	
	cont_logs_on_screen = 0;
}

void logs_draw(void)
{
	int i;

	for(i = 0; i < MAX_LOGS; i++)
	{
		if(log[i].on_screen)
		{
			al_draw_bitmap(sprites.log, log[i].x, log[i].y, 0);

			al_draw_rectangle(log[i].x, log[i].y, log[i].x + LOG_W, log[i].y + LOG_H, al_map_rgb(100, 100, 100), 1);
		}
			
	}
}

int frog_get_x(void)
{
	return(frog.x);
}

int frog_get_y(void)
{
	return(frog.y);
}

int log_get_x(int i)
{
	return(log[i].x);
}

int log_get_y(int i)
{
	return(log[i].y);
}


/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static bool inside_log(int i, int x, int y, int w, int h)
{
	return(inside(  log[i].x, log[i].y, log[i].x + LOG_W, log[i].y + LOG_H,
					x, y, x + w, y + h));
}

void spawn_log(int i)
{

	if(log[i].dx < 0)
	{
		log[i].x = DISPLAY_W;
	}

	else if(log[i].dx > 0)
	{
		log[i].x = (-1)*LOG_W ;
	}
    
    log[i].on_screen = true;
}

void fix_frog_pos(void)
{
	//coordenadas topleft, sin offset
	//x entre (0) y (DISPLAY_W - CELL_W)
	//y entre (CELL_H) y (DISPLAY_H - CELL_H)
	int x = (frog.x - FROG_OFFSET_X), y = (frog.y - FROG_OFFSET_Y);

	//coordenadas topleft "correctas"
	int x_values[COLS], y_values[ROWS];

	int i;

	for(i = 0; i < COLS; i++)
		x_values[i] = i * CELL_W;
	for(i = 1; i < ROWS; i++)
		y_values[i] = i * CELL_H;

	int temp_a, temp_b;

	for(i = 0; i < COLS; i++)
	{
		temp_a = x - x_values[i];

		if(temp_a > 0)
			continue;
		if(temp_a == 0)
			break;

		temp_b = x_values[i-1] - x;

		
		if((i-1) >= 0)
		{	
			//"si está más cerca de la columna 'i' que de la 'i+1"
			if(temp_a <= temp_b)
				frog.x = x_values[i-1] + FROG_OFFSET_X;
			else
				frog.x = x_values[i] + FROG_OFFSET_X;
		}
		
		break;
	}
	
	for(i = 1; i < ROWS; i++)
	{
		temp_a = y - y_values[i];

		if(temp_a > 0)
			continue;
		if(temp_a == 0)
			break;

		temp_b = y_values[i-1] - y;

		//"si está más cerca de la fila 'i' que de la 'i+1"
		if(temp_a <= temp_b)
			frog.y = y_values[i-1] + FROG_OFFSET_Y;
		else
			frog.y = y_values[i] + FROG_OFFSET_Y;

		break;
	}
}

 