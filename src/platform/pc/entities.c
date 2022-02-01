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
#include "game_data.h" 


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

//#define DEBUG_ENTITIES_TEXT

#define LOGS_SPAWN_MIN			1
#define LOGS_SPAWN_MAX			3
#define LOGS_SPAWN_FRAMES		60
#define LOGS_BASE_SPEED			2
#define LOGS_MAX_USED			7
#define LOGS_EXTRA_SEPARATOR	LOG_W/2

#define CARS_SPAWN_MIN			1
#define CARS_SPAWN_MAX			4
#define CARS_SPAWN_FRAMES		60
#define CARS_BASE_SPEED			2
#define CARS_MAX_USED			7
#define CARS_EXTRA_SEPARATOR	CAR_W*2

#define TURTLES_MIN_PER_PACK	1
#define	TURTLES_MAX_PER_PACK	2
#define TURTLES_SPAWN_FRAMES	60	//cada cuantos frames spawnean
#define TURTLES_SPAWN_MIN		1	//minimas a spawnear de una
#define TURTLES_SPAWN_MAX		2	//maximas a spawnear de una
#define TURTLES_MAX_USED		7	//maximas en pantalla
#define TURTLES_BASE_SPEED		2	
#define TURTLES_FRAME_TIMEOUT_SURFACE		10	//cuanto "tiempo" dura un frame dibujado antes de pasar al siguiente
#define TURTLES_FRAME_TIMEOUT_GOING_DOWN	50	//tiempo por frame al sumergirse
#define TURTLES_FRAME_TIMEOUT_WATER			20	//tiempo por frame para mostrarse bajo el agua
#define TURTLES_FRAME_TIMEOUT_GOING_UP		10	//tiempo por frame para mostrarse saliendo del agua
#define TURTLES_SURFACE_FRAMES_MIN		80	//minimo "tiempo" en superficie
#define TURTLES_SURFACE_FRAMES_MAX		500	//maximo "tiempo" en superficie
#define TURTLES_WATER_FRAMES_MIN		60	//minimo "tiempo" bajo el agua
#define TURTLES_WATER_FRAMES_MAX		100 //maximo "tiempo" bajo el agua
#define TURTLES_EXTRA_SEPARATOR			TURTLE_SIDE*2

#define FLY_SPAWN_FRAMES_MIN	300	//mínimo tiempo para respawnear mosca
#define	FLY_SPAWN_FRAMES_MAX	600	//maximo tiempo para respawnear mosca
#define FLY_DESPAWN_FRAMES_MIN	700	//mínimo tiempo para sacar mosca
#define	FLY_DESPAWN_FRAMES_MAX	900	//maximo tiempo para sacar mosca
#define FLY_FRAMES_TO_WARN_A	250	//frames previos al despawneo cuando empieza a titilar
#define FLY_FRAMES_TO_WARN_B	100
#define FLY_WARNING_FRAMES_A	20	//blink rate
#define FLY_WARNING_FRAMES_B	10


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
	unsigned char state;
	unsigned char next_action;

} frog_t;

typedef struct
{
    int x;              //Posicion del auto
	int y;
    int lane;           //Carril del auto.
	int dx;				//Velocidad del auto.
    CAR_TYPE type;		//Tipo de auto.
	int length;			//Largo del auto.
	bool fast;
    bool used;          //Marca disponibilidad en el array.
} car_t;

typedef struct
{
	int x;
	int y;
	int lane;
	int dx;
	bool used;

} log_t;

typedef struct
{
	int x;							//coordenada x
	int y;							//coordenada y
	int lane;						//carril
	int dx;							//velocidad
	bool used;						//flag de usada o no
	unsigned char turtles_in_pack;	//cantidad de tortugas en el paquete

	struct
	{
		unsigned char frame;			//contador que indica en qué frame de la animación se está (de 1 a TURTLES_FRAMES)
		unsigned int timeout;			//timeout interno para cambiar de frame
		unsigned int cont;				//contador interno de frames de juego ejecutados
	} fx;
		
	int wide;						//ancho del paquete, proporcional a turtles_in_pack y a TURTLES_SIDE
	unsigned char state;			//estado (enum TURTLE_STATES)
} turtle_pack_t;

typedef struct
{
	int x;
	int y;
	bool used;						//flag de usada o no
	struct
	{
		unsigned int timeout;		//Para spawneo y despawneo
		unsigned int blink_timer;	//Para titilar mosca antes de sacarla
		unsigned int cont;			//contador interno de frames de juego ejecutados
		bool flag;					//Para indicar si debe parpadear o no
	} fx;
		
} fly_t;


enum TURTLE_STATES
{
	TURTLE_STATE_SURFACE,
	TURTLE_STATE_GOING_DOWN,
	TURTLE_STATE_WATER,
	TURTLE_STATE_GOING_UP
};


enum FROG_STATES
{
	FROG_STATE_ROAD,
	FROG_STATE_WATER,
	FROG_STATE_LOG,
	FROG_STATE_TURTLE,
	FROG_STATE_GOAL,
	FROG_STATE_GOAL_FLY,		//meta con mosca
	FROG_STATE_CRASH_CAR,
	FROG_STATE_CRASH_WALL,
	FROG_STATE_BOUNCING_WALL	//rebota contra algun borde
};


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa la rana
 *
 */
static void frog_init(void);

/**
 * @brief Actualiza posicionamiento de la rana
 *
 */
static void frog_update(void);

/**
 * @brief Dibuja la rana
 *
 */
static void frog_draw(void);

/**
 * @brief Inicializa troncos
 *
 */
static void logs_init(void);

/**
 * @brief Actualiza troncos
 *
 */
static void logs_update(void);

/**
 * @brief Dibuja troncos
 *
 */
static void logs_draw(void);

/**
 * @brief Inicializa autos
 *
 */
static void cars_init(void);

/**
 * @brief Actualiza autos
 *
 */
static void cars_update(void);

/**
 * @brief Dibuja autos
 *
 */
static void cars_draw(void);

/**
 * @brief Inicializacion de tortugas
 *
 */
static void turtles_init(void);

/**
 * @brief Actualizacion de tortugas
 *
 */
static void turtles_update(void);

/**
 * @brief Dibujo de tortugas
 *
 */
static void turtles_draw(void);

/**
 * @brief Inicializacion de mosca
 *
 */
static void fly_init(void);

/**
 * @brief Actualizacion de mosca
 *
 */
static void fly_update(void);

/**
 * @brief Dibujo de mosca
 *
 */
static void fly_draw(void);

/**
 * @brief Alinea y centra la posición de la rana con las celdas del mapa, por desvios sobre troncos.
 *
 */
//static void fix_frog_pos(void);

/**
 * @brief Alinea coordenadaY de la rana con las celdas del mapa, por desvios varios.
 * 
 */
static void fix_frog_coord_y(void);

/**
 * @brief Verifica si la rana llego a un punto de llegada valido 
 * 
 * Verifica en terminos de coordenada X y en terminos de si el punto de llegada es repetido
 * 
 * @return true Llegó
 * @return false No llegó
 */
static bool is_frog_in_goal(void);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//Rana
static frog_t frog;

//Array de troncos
static log_t log[LOGS_MAX_USED];

//Array de autos
static car_t car[CARS_MAX_USED];

//Array de paquetes de tortugas
static turtle_pack_t turtle_pack[TURTLES_MAX_USED];

//Mosca
static fly_t fly;

//Contador de frames ejecutados
static unsigned long game_frames;

//Carriles variables.
static unsigned char normal_diff_lane;
static unsigned char hard_diff_lane_1;
static unsigned char hard_diff_lane_2;


/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void entities_init(void)
{
	frog_init();
	logs_init();
	cars_init();
	turtles_init();
	fly_init();

	game_frames = 0;
}

void entities_update()
{
	game_frames = game_data_get_frames();

	frog_update();
	logs_update();
	cars_update();
	turtles_update();
	fly_update();
}

void entities_draw()
{
	logs_draw();
	cars_draw();
	turtles_draw();
	fly_draw();

	//"frog siempre a lo ultimo, para que se vea"
	frog_draw();
}

void entities_move_frog(unsigned char direction)
{
	if(direction == DIRECTION_DOWN || direction == DIRECTION_LEFT ||
		direction == DIRECTION_UP || direction == DIRECTION_RIGHT)
	{
		frog.next_action = direction;
	}
}



/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/





static void frog_init(void)
{
	frog.x = CELL_START_FROG_X;
	frog.y = CELL_START_FROG_Y;
	frog.moving = false;
	frog.facing = DIRECTION_UP;
	frog.steps = 0;
	frog.state = FROG_STATE_ROAD;
	frog.next_action = DIRECTION_NONE;
}

static void frog_update(void)
{
	int i;

	bool interaction_flag = false;

	if(!frog.moving)
	{
		if(frog.next_action == DIRECTION_DOWN || frog.next_action == DIRECTION_LEFT ||
			frog.next_action == DIRECTION_UP || frog.next_action == DIRECTION_RIGHT)
		{
			frog.facing = frog.next_action;
			frog.moving = true;
			frog.next_action = DIRECTION_NONE;
			allegro_sound_play_effect_jump();
		}

	}

	else if (frog.moving)
	{

		if(frog.facing == DIRECTION_LEFT)
			frog.x -= STEP_FRACTION_SIZE;
		else if(frog.facing == DIRECTION_RIGHT)
			frog.x += STEP_FRACTION_SIZE;
		else if(frog.facing == DIRECTION_UP)
			frog.y -= STEP_FRACTION_SIZE;
		else if(frog.facing == DIRECTION_DOWN)
			frog.y += STEP_FRACTION_SIZE;

		if(++frog.steps >= STEP_RATIO)
		{
			frog.steps = 0;
			frog.moving = false;

			fix_frog_coord_y();
		}
	}


	//donde esta parada
	if(!frog.moving)
	{
		unsigned int y_no_offset = frog.y - FROG_OFFSET_Y;

		//en alguna fila de descanso o de autos
		if(y_no_offset >= CELL_H * (lanes_cars[0] - 1) && y_no_offset <= DISPLAY_H - CELL_H)
			frog.state = FROG_STATE_ROAD;

		//en alguna fila de agua. Luego se actualiza si es sobre tronco o turtle
		else if(y_no_offset >= CELL_H * 2 && y_no_offset <= CELL_H * (lanes_cars[0] - 1))
			frog.state = FROG_STATE_WATER;

		//choque contra alguno de los muros superiores, o llegada bien a un goal
		else if (y_no_offset < CELL_H * 2)
		{
			if(!is_frog_in_goal())
			{
				frog.state = FROG_STATE_CRASH_WALL;
			}

			else
			{
				frog.state = FROG_STATE_GOAL;

				//colision con fly
				if(fly.used)
				{
					if(collideShort(	fly.x,
										fly.y,
										FLY_SIDE,
										FLY_SIDE,
										frog.x,
										frog.y,
										FROG_W,
										FROG_H))
					{
						frog.state = FROG_STATE_GOAL_FLY;
						fly.used = false;
					}
				}

				
			}

			interaction_flag = true;
		}
			
			
		/*---*/

		

		if(!interaction_flag)
		{
			//colision con autos
			for(i = 0; i < CARS_MAX_USED; i++)
			{
				if(!car[i].used)
					continue;
				
				if(collideShort(	car[i].x,
									car[i].y,
									car[i].length,
									CAR_H,
									frog.x,
									frog.y,
									FROG_W,
									FROG_H))
				{
					frog.state = FROG_STATE_CRASH_CAR;
					interaction_flag = true;
					break;	//no puede chocar con 2 autos a la vez
				}
			}
		}		
		
	}

	if(!interaction_flag)
	{
		//esta en algun tronco?
		for(i = 0; i < LOGS_MAX_USED; i++)
		{
			if(!log[i].used)
				continue;

			if(insideShortScaled(	log[i].x,
									log[i].y,
									LOG_W,
									LOG_H,
									frog.x,
									frog.y,
									FROG_W,
									FROG_H,
									INSERTION_FACTOR))
			{
				frog.x += log[i].dx;
				frog.state = FROG_STATE_LOG;
				interaction_flag = true;
				break;		//no puede estar en 2 troncos a la vez
			}
		}
	}
	
	if(!interaction_flag)
	{
		//esta en algun turtle_pack?
		for(i = 0; i < TURTLES_MAX_USED; i++)
		{
			//Omite si el pack no esta usado o si esta bajo agua
			if(!turtle_pack[i].used || turtle_pack[i].state == TURTLE_STATE_WATER)
				continue;

			if(insideShortScaled(	turtle_pack[i].x,
									turtle_pack[i].y,
									turtle_pack[i].wide,
									TURTLE_SIDE,
									frog.x,
									frog.y,
									FROG_W,
									FROG_H,
									INSERTION_FACTOR))
			{
				frog.x += turtle_pack[i].dx;
				frog.state = FROG_STATE_TURTLE;
				interaction_flag = true;
				break;		//no puede estar en 2 packs a la vez
			}
		}
	}
	

	//revision de limites
	if(frog.x < FROG_MIN_X)
		frog.x = FROG_MIN_X;
	else if(frog.x > FROG_MAX_X)
		frog.x = FROG_MAX_X;
	else if(frog.y < FROG_MIN_Y)
		frog.y = FROG_MIN_Y;
	else if(frog.y > FROG_MAX_Y)
		frog.y = FROG_MAX_Y;

	switch (frog.state)
	{
		case FROG_STATE_WATER:
			game_data_subtract_live();
			allegro_sound_play_effect_drowned();
			frog_init();
			break;
		
		case FROG_STATE_CRASH_CAR:
			game_data_subtract_live();
			allegro_sound_play_effect_crash();
			frog_init();

			break;
		
		case FROG_STATE_CRASH_WALL:
			game_data_subtract_live();
			allegro_sound_play_effect_crash();
			frog_init();

			break;
		
		case FROG_STATE_GOAL:
			game_data_add_run_time_goal();
			game_data_add_score();
			allegro_sound_play_effect_goal();
			frog_init();
			
			break;
			
		case FROG_STATE_GOAL_FLY:
			game_data_add_run_time_goal_bonus();
			game_data_add_score_bonus();
			allegro_sound_play_effect_bonus();
			frog_init();

			break;
		
		default:
			break;
	}

#ifdef DEBUG_ENTITIES_TEXT
	if(!(game_frames % 10))
		printf("state: %d ~~ y_no_offset: %d\n", frog.state, frog.y - FROG_OFFSET_Y);
#endif

}

static void frog_draw(void)
{

	ALLEGRO_BITMAP* tempbitmap = NULL;

	if(frog.moving)
	{
		if(frog.facing == DIRECTION_UP)
			tempbitmap = sprites.frog[1];
		if(frog.facing == DIRECTION_DOWN)
			tempbitmap = sprites.frog[7];
		if(frog.facing == DIRECTION_RIGHT)
			tempbitmap = sprites.frog[3];
		if(frog.facing == DIRECTION_LEFT)
			tempbitmap = sprites.frog[5];

	}

	else if(!frog.moving)
	{
		if(frog.facing == DIRECTION_UP)
			tempbitmap = sprites.frog[0];
		if(frog.facing == DIRECTION_DOWN)
			tempbitmap = sprites.frog[6];
		if(frog.facing == DIRECTION_RIGHT)
			tempbitmap = sprites.frog[2];
		if(frog.facing == DIRECTION_LEFT)
			tempbitmap = sprites.frog[4];

	}

	al_draw_bitmap(tempbitmap, frog.x, frog.y, 0);

#ifdef DEBUG_ENTITIES_TEXT	
	//hitbox
	allegro_draw_hitbox(frog.x, frog.y, FROG_W, FROG_H);
	//coordenadas rana
    al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, 0, 0, "X: %d Y: %d", frog.x, frog.y);
#endif

}

static void logs_init(void)
{
	int i;
	for(i = 0; i < LOGS_MAX_USED; i++)
		log[i].used = false;

}

static void logs_update(void)
{
	//se busca spawnear entre LOGS_SPAWN_MIN y LOGS_SPAWN_MAX autos cada LOGS_SPAWN_FRAMES frames
	int new_quota = ((game_frames % LOGS_SPAWN_FRAMES) ? 0 : get_rand_between(LOGS_SPAWN_MIN, LOGS_SPAWN_MAX));

	int i, used;

	//cuento cuantos troncos usados hay
	for(i = 0, used = 0; i < LOGS_MAX_USED; i++)
		used += log[i].used;

    for(i = 0; i < LOGS_MAX_USED; i++)
    {
        //Spawneo de troncos
        if(!log[i].used && new_quota > 0 && used < LOGS_MAX_USED)           //Lugar libre?
        {

			//Asigno carril.
			log[i].lane = lanes_logs[get_rand_between(0, LANES_LOG_TOTAL-1)];

			//Coordenada 'y' en funcion del carril
			log[i].y = CELL_H * log[i].lane + LOG_OFFSET_Y;

			//Velocidad
			//log[i].dx = lanes_logs[LANES_LOG_TOTAL-1] - log[i].lane + 1;
			//log[i].dx = map_int(log[i].lane, 0, lanes_logs[LANES_LOG_TOTAL-1], 1, 3);
			log[i].dx = LOGS_BASE_SPEED;

			//en pares...
			if(!(log[i].lane % 2))
			{
				//coordenada de inicio
				log[i].x = -LOG_W;
			}

			//en impares...
			else
			{
				//coordenada de inicio
				log[i].x = DISPLAY_W;

				//hacia el otro lado
				log[i].dx *= (-1);
			}

			int p;
			bool check;		//para confirmar asignacion de lane
			for(p = 0, check = true; p < LOGS_MAX_USED; p++)
			{
				//si no es el mismo tronco, y ese otro esta usado, y coinciden en lane...
				if(p != i && log[p].used && log[p].lane == log[i].lane)
				{
					//si colisiona con algun otro tronco...
					if	(collide(
									log[i].x - LOGS_EXTRA_SEPARATOR,
									log[i].y,
									log[i].x + LOG_W + LOGS_EXTRA_SEPARATOR,
									log[i].y + LOG_H,
									log[p].x,
									log[p].y,
									log[p].x + LOG_W,
									log[p].y + LOG_H
								)
						)
					{
						//no spawnea
						check = false;
						break;
					}
				}

			}

			//si se puede spawnear...
			if(check)
			{
				//Pasa a usado
				log[i].used = true;
				used++;
				new_quota--;
			}

			//si no se puede spawnear...
			else
			{

			}

        }

		//si el tronco esta usado...
		else if(log[i].used)
		{
			//desplaza
			log[i].x += log[i].dx;

			//chequea si llego a los limites
			if((log[i].dx > 0 && log[i].x >= DISPLAY_W) || (log[i].dx < 0 && log[i].x <= -LOG_W))
			{
				log[i].used = false;
				used--;
			}
				

			//printf("~log%d lane%d dx%d~\n", i, log[i].lane, log[i].dx);

		}

    }

}

static void logs_draw(void)
{
	int i;

	for(i = 0; i < LOGS_MAX_USED; i++)
	{
		if(log[i].used)
		{
			al_draw_bitmap(sprites.log, log[i].x, log[i].y, 0);

#ifdef DEBUG_ENTITIES_TEXT	
			//hitbox
			allegro_draw_hitbox(log[i].x, log[i].y, LOG_W, LOG_H);
#endif
		}

	}

#ifdef DEBUG_ENTITIES_TEXT	
	//coordenadas
	int space;
	for(i = 0, space = 20; i < LOGS_MAX_USED; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, log[i].x, log[i].y);
	}
#endif

}

static void cars_init(void)
{
	int i;
	//Inicio array de autos desocupando.
	for(i = 0; i < CARS_MAX_USED; i++)
        car[i].used = false;

	switch (game_data_get_diff())
	{
		case DIFFICULTIES_EASY:
			break;
		
		case DIFFICULTIES_NORMAL:
			normal_diff_lane = get_rand_between(lanes_cars[0], lanes_cars[LANES_CAR_TOTAL - 1]);
			break;

		case DIFFICULTIES_HARD:
			hard_diff_lane_1 = get_rand_between(lanes_cars[0], lanes_cars[2]);
			hard_diff_lane_2 = get_rand_between(lanes_cars[3], lanes_cars[4]);
			break;
	}

}

static void cars_update(void)
{
	//se busca spawnear entre CARS_SPAWN_MIN y CARS_SPAWN_MAX autos cada CARS_SPAWN_FRAMES frames
	int new_quota = ((game_frames % CARS_SPAWN_FRAMES) ? 0 : get_rand_between(CARS_SPAWN_MIN, CARS_SPAWN_MAX));

	int i, used;

	//cuento cuantos autos usados hay
	for(i = 0, used = 0; i < CARS_MAX_USED; i++)
		used += car[i].used;

    for(i = 0; i < CARS_MAX_USED; i++)
    {
        //Spawneo de autos.
        if(!car[i].used && new_quota > 0 && used < CARS_MAX_USED)	//Lugar libre?
        {
			//Asigno carril.
			car[i].lane = lanes_cars[get_rand_between(0, LANES_CAR_TOTAL-1)];

			//Coordenada 'y' en funcion del carril
			car[i].y = CELL_H * car[i].lane + CAR_OFFSET_Y;

			//Velocidad menor en rutas mas alejadas
			car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED;
			//car[i].dx = CARS_BASE_SPEED;

			//Asigno tipos.
			car[i].type = get_rand_between(0, CAR_TYPE_N - 1);

			//Defino los largos correspondientes,
			switch(car[i].type)
            {
				case CAR_POLICE:
				case CAR_YELLOW:
                case CAR_BLUE: 
                    car[i].length = CAR_W;
                    break;
                case TRUCK_FIRE:
                    car[i].length = CAR_TRUCK_FIRE_W;
                    break;
                case TRUCK:
                    car[i].length = CAR_TRUCK_W;
                    break;
                default:
                    break;
            }

			//Inicializo el flag.
			car[i].fast = 0;

			//en pares...
			if(!(car[i].lane % 2))
			{
				//coordenada de inicio
				car[i].x = -car[i].length;
			}

			//en impares...
			else
			{
				//coordenada de inicio
				car[i].x = DISPLAY_W;

				//hacia el otro lado
				car[i].dx *= (-1);
			}

			int p;
			bool check;		//para confirmar asignacion de lane
			for(p = 0, check = true; p < CARS_MAX_USED; p++)
			{
				//si no es el mismo auto, y ese otro esta usado, y coinciden en lane...
				if(p != i && car[p].used && car[p].lane == car[i].lane)
				{
					//si colisiona con algun otro auto...
					if	(collide(
									car[i].x - CARS_EXTRA_SEPARATOR,
									car[i].y,
									car[i].x + car[i].length + CARS_EXTRA_SEPARATOR,		//Es el mas largo.
									car[i].y + CAR_H,
									car[p].x,
									car[p].y,
									car[p].x + car[p].length,
									car[p].y + CAR_H
								)
						)
					{
						//no spawnea
						check = false;
						break;
					}
				}

			}

			//si se puede spawnear...
			if(check)
			{
				//Pasa a usado
				car[i].used = true;
				used++;
				new_quota--;
			}

			//si no se puede spawnear...
			else
			{

			}

        }

		//si el auto esta usado...
		else if(car[i].used)
		{
			//Desplazamiento
			car[i].x += car[i].dx;

			//chequea si llego a los limites
			if((car[i].dx > 0 && car[i].x >= DISPLAY_W) || (car[i].dx < 0 && car[i].x <= -car[i].length))
			{
				car[i].used = false;
				used--;
			}
				

			//printf("~car%d lane%d dx%d~\n", i, car[i].lane, car[i].dx);

		}

    }

	for(i = 0; i < CARS_MAX_USED; i++)
	{
		if(car[i].used)
		{
			//Carril con velocidad variable
			switch (game_data_get_diff())
			{
				case DIFFICULTIES_EASY:
					break;

				case DIFFICULTIES_NORMAL:
					if(car[i].lane == normal_diff_lane)
					{
						if(!(game_frames % FPS))
						{
							if(car[i].fast == 0)
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED + 1;
								if(car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 1;
							}
							else
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED;
								if(car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 0;
							}
						}
					}
					break;
				case DIFFICULTIES_HARD:
					if((car[i].lane == hard_diff_lane_1) || (car[i].lane == hard_diff_lane_2))
					{
						if(!(game_frames % FPS))
						{
							if(car[i].fast == 0)
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED + 1;
								if(car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 1;
							}
							else
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED;
								if(car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 0;
							}
						}
					}
				default:
					break;
			}			
		}
	}
}

static void cars_draw()
{
	int i;
	bool flag;

	ALLEGRO_BITMAP* temp_bitmap = NULL;

	for(i = 0; i < CARS_MAX_USED; i++)
    {
        if(car[i].used)
		{
			if(car[i].dx < 0)
				flag = ALLEGRO_FLIP_HORIZONTAL;
			else
				flag = 0;

			temp_bitmap = sprites.car[car[i].type];

			//Dibujo los autos en sus carriles.
			al_draw_bitmap(temp_bitmap, car[i].x, car[i].y, flag);

#ifdef DEBUG_ENTITIES_TEXT	
			//Dibujo hitbox
			allegro_draw_hitbox(car[i].x, car[i].y, car[i].length, CAR_H);
#endif
		}


    }

#ifdef DEBUG_ENTITIES_TEXT	
	//coordenadas
	int space;
	for(i = 0, space = 200; i < CARS_MAX_USED; i++, space += 20)
	{
		//al_draw_textf(allegro_get_var_font(), al_map_rgb(255, 255, 255), 0, space, 0, "N°:%d X:%d Y:%d dx:%d", i, car[i].x, car[i].y, car[i].dx);
		al_draw_textf(allegro_get_var_font(), al_map_rgb(255, 255, 255), 0, space, 0, "Lane:%d dx:%d", car[i].lane, car[i].dx);
	}
#endif
}

static void turtles_init(void)
{
	int i;
	for(i = 0; i < TURTLES_MAX_USED; i++)
	{
		turtle_pack[i].used = false;
	}
}

static void turtles_update(void)
{
	int new_quota = ((game_frames % TURTLES_SPAWN_FRAMES) ? 0 : get_rand_between(TURTLES_SPAWN_MIN, TURTLES_SPAWN_MAX));

	int i, used;

	for(i = 0, used = 0; i < TURTLES_MAX_USED; i++)
	{
		if(turtle_pack[i].used)
			used++;
	}

    for(i = 0; i < TURTLES_MAX_USED; i++)
    {
        //Spawneo de turtle_packs
        if(!turtle_pack[i].used && new_quota > 0 && used < TURTLES_MAX_USED)       //Lugar libre?
        {

			//defino tortugas en el pack
			turtle_pack[i].turtles_in_pack = get_rand_between(TURTLES_MIN_PER_PACK, TURTLES_MAX_PER_PACK);

			//calculo ancho del pack
			turtle_pack[i].wide = TURTLE_SIDE * turtle_pack[i].turtles_in_pack;

			//Asigno carril.
			turtle_pack[i].lane = lanes_turtles[get_rand_between(0, LANES_TURTLE_TOTAL-1)];

			//Coordenada 'y' en funcion del carril
			turtle_pack[i].y = CELL_H * turtle_pack[i].lane;

			//Velocidad
			//turtle_pack[i].dx = lanes_turtles[LANES_TURTLE_TOTAL- turtle_pack[i].lane + 1];
			turtle_pack[i].dx = TURTLES_BASE_SPEED;

			//en pares...
			if(!(turtle_pack[i].lane % 2))
			{
				//coordenada de inicio
				turtle_pack[i].x = -turtle_pack[i].wide;
			}

			//en impares...
			else
			{
				//coordenada de inicio
				turtle_pack[i].x = DISPLAY_W;

				//hacia el otro lado
				turtle_pack[i].dx *= (-1);
			}

			int p;
			bool check;		//para confirmar asignacion de lane
			for(p = 0, check = true; p < TURTLES_MAX_USED; p++)
			{
				//si no es el mismo pack, y ese otro esta usado, y coinciden en lane...
				if(p != i && turtle_pack[p].used && turtle_pack[p].lane == turtle_pack[i].lane)
				{
					//si colisiona con algun otro pack...
					if	(collide(
									turtle_pack[i].x - TURTLES_EXTRA_SEPARATOR,
									turtle_pack[i].y,
									turtle_pack[i].x + turtle_pack[i].wide + TURTLES_EXTRA_SEPARATOR,
									turtle_pack[i].y + TURTLE_SIDE,
									turtle_pack[p].x,
									turtle_pack[p].y,
									turtle_pack[p].x + turtle_pack[p].wide,
									turtle_pack[p].y + TURTLE_SIDE
								)
						)
					{
						//no spawnea
						check = false;
						break;
					}
				}

			}

			//si se puede spawnear...
			if(check)
			{
				//Pasa a usado
				turtle_pack[i].used = true;
				used++;

				//se inicializa el contador de frames
				turtle_pack[i].fx.frame = 0;
				turtle_pack[i].fx.cont = 1;
				turtle_pack[i].fx.timeout = 0;
				//fuera del agua
				turtle_pack[i].state = TURTLE_STATE_SURFACE;

				new_quota--;
			}

			//si no se puede spawnear...
			else
			{

			}

        }

		//si el pack esta usado...
		else if(turtle_pack[i].used)
		{
			//desplaza
			turtle_pack[i].x += turtle_pack[i].dx;


			switch (turtle_pack[i].state)
			{
				case TURTLE_STATE_SURFACE:
					if(!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_SURFACE))
						turtle_pack[i].fx.frame++;

					//si no esta inicializado, inicializo timeout
					if(!turtle_pack[i].fx.timeout)
						turtle_pack[i].fx.timeout = get_rand_between(TURTLES_SURFACE_FRAMES_MIN, TURTLES_SURFACE_FRAMES_MAX);
					
					//pasa a agua
					if(!(turtle_pack[i].fx.cont % turtle_pack[i].fx.timeout))
					{
						turtle_pack[i].state = TURTLE_STATE_GOING_DOWN;
						turtle_pack[i].fx.frame = 7;
						turtle_pack[i].fx.timeout = 0;
						turtle_pack[i].fx.cont = 1;
					}

					//Reinicia animacion
					else if(turtle_pack[i].fx.frame == 7)
						turtle_pack[i].fx.frame = 0;

					break;

				case TURTLE_STATE_GOING_DOWN:
					if(!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_GOING_DOWN))
						turtle_pack[i].fx.frame++;

					if(turtle_pack[i].fx.frame == 9)
					{
						turtle_pack[i].state = TURTLE_STATE_WATER;
						turtle_pack[i].fx.cont = 1;
					}

					break;

				case TURTLE_STATE_WATER:
					if(!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_WATER))
						turtle_pack[i].fx.frame++;

					//si no esta inicializado, inicializo timeout
					if(!turtle_pack[i].fx.timeout)
						turtle_pack[i].fx.timeout = get_rand_between(TURTLES_WATER_FRAMES_MIN, TURTLES_WATER_FRAMES_MAX);
					
					//pasa a fuera
					if(!(turtle_pack[i].fx.cont % turtle_pack[i].fx.timeout))
					{
						turtle_pack[i].state = TURTLE_STATE_GOING_UP;
						turtle_pack[i].fx.frame = 10;
						turtle_pack[i].fx.timeout = 0;
						turtle_pack[i].fx.cont = 1;
					}

					//Reinicia animacion
					else if(turtle_pack[i].fx.frame == 11)
						turtle_pack[i].fx.frame = 9;

					break;

				case TURTLE_STATE_GOING_UP:
					if(!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_GOING_UP))
						turtle_pack[i].fx.frame--;

					if(turtle_pack[i].fx.frame == 7)
					{
						turtle_pack[i].fx.frame = 6;
						turtle_pack[i].state = TURTLE_STATE_SURFACE;
						turtle_pack[i].fx.cont = 1;
					}

					break;
				
				default:
					break;
			}


			//chequea si llego a los limites
			if((turtle_pack[i].dx > 0 && turtle_pack[i].x >= DISPLAY_W) || (turtle_pack[i].dx < 0 && turtle_pack[i].x <= -turtle_pack[i].wide))
			{
				turtle_pack[i].used = false;
				used--;
			}				

			//printf("~turtle_pack%d lane%d dx%d~\n", i, turtle_pack[i].lane, turtle_pack[i].dx);

		}

    }

}

static void turtles_draw(void)
{
	int i, j, flag;
	for(i = 0; i < TURTLES_MAX_USED; i++)
    {
        if(turtle_pack[i].used)
		{
			for(j = 0; j < turtle_pack[i].turtles_in_pack; j++)
			{
				if(turtle_pack[i].dx < 0)
					flag = ALLEGRO_FLIP_HORIZONTAL;
				else
					flag = 0;

				al_draw_bitmap(sprites.turtle[turtle_pack[i].fx.frame], turtle_pack[i].x + TURTLE_SIDE * j, turtle_pack[i].y, flag);
			}

#ifdef DEBUG_ENTITIES_TEXT	
			//Dibujo hitbox
			allegro_draw_hitbox(turtle_pack[i].x, turtle_pack[i].y, turtle_pack[i].wide, TURTLE_SIDE);
#endif
		}


    }

#ifdef DEBUG_ENTITIES_TEXT	
	//coordenadas
	int space;
	for(i = 0, space = 350; i < TURTLES_MAX_USED; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, turtle_pack[i].x, turtle_pack[i].y);
	}
#endif
}

static void fly_init(void)
{
	fly.used = false;
	fly.y = CELL_H + FLY_OFFSET_XY + GOAL_ROW_OFFSET_Y_FIX;

	fly.fx.blink_timer = 0;
	fly.fx.timeout = 0;
	fly.fx.flag = false;
	fly.fx.cont = 1;
}

static void fly_update(void)
{
	if(!fly.used)
	{
		//si no esta inicializado, inicializo timeout para spawneo
		if(!fly.fx.timeout)
			fly.fx.timeout = get_rand_between(FLY_SPAWN_FRAMES_MIN, FLY_SPAWN_FRAMES_MAX);

		if(!(fly.fx.cont % fly.fx.timeout))
		{
			//calculo de coordenada x para alguno de los puntos de llegada
			int temp_goal = get_rand_between(0, MAX_GOALS - 1);
			
			//si el goal está libre...
			if(!game_data_get_goal_state(temp_goal))
			{
				fly.x = CELL_W * goal_cols[temp_goal] + FLY_OFFSET_XY;
				//marcado como usado
				fly.used = true;
				//desinicializo el timeout
				fly.fx.timeout = 0;
				fly.fx.blink_timer = 0;
				fly.fx.cont = 1;
			}

			//si no, cuando pasa otro timeout se intenta de nuevo
			else
			{

			}
			
		}

	}

	else
	{
		//timeout para despawneo
		if(!fly.fx.timeout)
			fly.fx.timeout = get_rand_between(FLY_DESPAWN_FRAMES_MIN, FLY_DESPAWN_FRAMES_MAX);

		if(++fly.fx.blink_timer > fly.fx.timeout - FLY_FRAMES_TO_WARN_A)
		{
			if(fly.fx.blink_timer > fly.fx.timeout - FLY_FRAMES_TO_WARN_B)
			{
				if(!(fly.fx.cont % FLY_WARNING_FRAMES_B))
					fly.fx.flag = !fly.fx.flag;
			}
			else
			{
				if(!(fly.fx.cont % FLY_WARNING_FRAMES_A))
					fly.fx.flag = !fly.fx.flag;
			}

		}

		//si se puede despawnear
		if(!(fly.fx.cont % fly.fx.timeout))
		{
			//mosca no usada
			fly.used = false;

			//desinicializo timeout
			fly.fx.timeout = 0;

			//saco el blinking
			fly.fx.flag = false;

			fly.fx.cont = 1;
		}
	}

	fly.fx.cont++;

}

static void fly_draw(void)
{
	if(fly.used)
	{
		//Si no está el flag, dibujo sprite normalmente
		if(!fly.fx.flag)
			al_draw_bitmap(sprites.fly, fly.x, fly.y, 0);

	}

#ifdef DEBUG_ENTITIES_TEXT	

	//hitbox
	allegro_draw_hitbox(fly.x, fly.y, FLY_SIDE, FLY_SIDE);

	//coordenadas
	int space = 500;
	al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "Mosca ~ X:%d Y:%d", fly.x, fly.y);
#endif
}

/*
static void fix_frog_pos(void)
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
*/

static void fix_frog_coord_y(void)
{
	int y = (frog.y - FROG_OFFSET_Y);

	int y_values[ROWS];

	int i;

	//Carga valores "correctos" de y
	for(i = 1; i < ROWS - 1; i++)
		y_values[i] = i * CELL_H;

	int temp_a, temp_b;
	for(i = 1; i < ROWS - 1; i++)
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

static bool is_frog_in_goal(void)
{
	bool state = false;
	int x = frog.x;

	int i, x_col;
	for(i = 0; i < MAX_GOALS; i++)
	{
		//Coordenada top left del punto de llegada
		x_col = goal_cols[i]*CELL_W;

		//Calculo para ver si entro bien o no
		if(		(x > x_col - GOAL_ROW_MARGIN_TO_REACH) 
								&& 
				((x + FROG_W) < x_col + CELL_W + GOAL_ROW_MARGIN_TO_REACH))
		{
			//coodenada X aceptable
			state = true;
			break;
		}
	}

	//Si coincide en coordenada y el goal esta libre...
	if(state && !game_data_get_goal_state(i))
	{
		//marca el goal como completo
		game_data_set_goal(i);
	}
	else
	{
		//no llego a un goal valido
		state = false;
	}
		

	return state;
}
