/**
 * @file 	entities.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo entities. Se encarga de la creacion, actualización
 * 			y muestreo de las entitades implementadas en PC.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
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

#define LOGS_SPAWN_MIN 1
#define LOGS_SPAWN_MAX 3
#define LOGS_SPAWN_FRAMES 60
#define LOGS_BASE_SPEED 1
#define LOGS_MAX_USED 8
#define LOGS_EXTRA_SEPARATOR LOG_W / 2

#define CARS_SPAWN_MIN 2
#define CARS_SPAWN_FRAMES 60
#define CARS_BASE_SPEED 1
#define CARS_MAX_USED 15
#define CAR_SPEED_INCREASE 2
#define CAR_WAIT_INCREASE 1
#define CARS_EXTRA_SEPARATOR CAR_W * 2

#define TURTLES_MIN_PER_PACK 1
#define TURTLES_MAX_PER_PACK 3
#define TURTLES_SPAWN_FRAMES 60 // cada cuantos frames spawnean
#define TURTLES_SPAWN_MIN 1		// minimas a spawnear de una
#define TURTLES_SPAWN_MAX 3		// maximas a spawnear de una
#define TURTLES_MAX_USED 8		// maximas en pantalla
#define TURTLES_BASE_SPEED 2
#define TURTLES_FRAME_TIMEOUT_SURFACE 10	// cuanto "tiempo" dura un frame dibujado antes de pasar al siguiente
#define TURTLES_FRAME_TIMEOUT_GOING_DOWN 50 // tiempo por frame al sumergirse
#define TURTLES_FRAME_TIMEOUT_WATER 20		// tiempo por frame para mostrarse bajo el agua
#define TURTLES_FRAME_TIMEOUT_GOING_UP 10	// tiempo por frame para mostrarse saliendo del agua
#define TURTLES_SURFACE_FRAMES_MIN 60		// minimo "tiempo" en superficie
#define TURTLES_SURFACE_FRAMES_MAX 600		// maximo "tiempo" en superficie
#define TURTLES_WATER_FRAMES_MIN 60			// minimo "tiempo" bajo el agua
#define TURTLES_WATER_FRAMES_MAX 200		// maximo "tiempo" bajo el agua
#define TURTLES_EXTRA_SEPARATOR TURTLE_SIDE * 2

#define COIN_SPAWN_FRAMES_MIN 300	// mínimo tiempo para respawnear coin
#define COIN_SPAWN_FRAMES_MAX 600	// maximo tiempo para respawnear coin
#define COIN_DESPAWN_FRAMES_MIN 700 // mínimo tiempo para sacar coin
#define COIN_DESPAWN_FRAMES_MAX 900 // maximo tiempo para sacar coin
#define COIN_FRAME_RATE 10			// cada cuanto gira la coin
#define COIN_FRAMES_TO_WARN_A 250	// frames previos al despawneo cuando empieza a titilar
#define COIN_FRAMES_TO_WARN_B 100
#define COIN_WARNING_FRAMES_A 20 // blink rate
#define COIN_WARNING_FRAMES_B 10

#define SPRITE_DEAD_TIMEOUT 80 // frames que permanece en pantalla el sprite de muerte

#define SPRITE_SPLASH_RATE 10 // cada cuanto avanza un frame la animacion

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
	int x; // Posicion del auto
	int y;
	int lane;	   // Carril del auto.
	int dx;		   // Velocidad del auto.
	CAR_TYPE type; // Tipo de auto.
	int length;	   // Largo del auto.
	int count;
	bool fast;
	bool used; // Marca disponibilidad en el array.
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
	int x;						   // coordenada x
	int y;						   // coordenada y
	int lane;					   // carril
	int dx;						   // velocidad
	bool used;					   // flag de usada o no
	unsigned char turtles_in_pack; // cantidad de tortugas en el paquete

	struct
	{
		unsigned char frame;  // contador que indica en qué frame de la animación se está (de 1 a TURTLES_FRAMES)
		unsigned int timeout; // timeout interno para cambiar de frame
		unsigned int cont;	  // contador interno de frames de juego ejecutados
	} fx;

	int wide;			 // ancho del paquete, proporcional a turtles_in_pack y a TURTLES_SIDE
	unsigned char state; // estado (enum TURTLE_STATES)
} turtle_pack_t;

typedef struct
{
	int x;
	int y;
	bool used; // flag de usada o no
	struct
	{
		unsigned int frame_cont;  // contador de frame a mostrar
		unsigned int timeout;	  // Para spawneo y despawneo
		unsigned int blink_timer; // Para titilar coin antes de sacarla
		unsigned int cont;		  // contador interno de frames de juego ejecutados
		bool flag;				  // Para indicar si debe parpadear o no
	} fx;

} coin_t;

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
	FROG_STATE_GOAL_COIN, // meta con coin
	FROG_STATE_CRASH_CAR,
	FROG_STATE_CRASH_WALL,
	FROG_STATE_BOUNCING_WALL // rebota contra algun borde
};

// Estructur para administrar el sprite de muerte
static struct
{
	bool flag;			// para indicar graficar
	unsigned int timer; // contador para permanecer en pantalla
	unsigned int x;
	unsigned int y;
} corpse_fx;

// Estructura para administrar el efecto de caida en agua
static struct
{
	bool flag;				 // usado o no
	unsigned int frame_cont; // contador de frame a mostrar
	unsigned int cont;		 // contador de ejecucion
	unsigned int x;			 // X topleft
	unsigned int y;			 // Y topleft

} splash_fx;

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
 * @brief Inicializacion de coin
 *
 */
static void coin_init(void);

/**
 * @brief Actualizacion de coin
 *
 */
static void coin_update(void);

/**
 * @brief Dibujo de coin
 *
 */
static void coin_draw(void);

/**
 * @brief Alinea y centra la posición de la rana con las celdas del mapa, por desvios sobre troncos.
 *
 */
// static void fix_frog_pos(void);

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

/**
 * @brief Configura sprite de muerte para que se muestre
 *
 * @param x Coordenada topleft X de rana
 * @param y Coordenada topleft Y de rana
 */
static void corpse_init(int x, int y);

/**
 * @brief Updates para sacar el sprite de muerte
 *
 */
static void corpse_update(void);

/**
 * @brief Dibuja el sprite de muerte
 *
 */
static void corpse_draw(void);

/**
 * @brief Configura sprites de splash para que se muestre
 *
 * @param x Coordenada topleft X de rana
 * @param y Coordenada topleft Y de rana
 */
static void splash_init(int x, int y);

/**
 * @brief Actualiza los frames del splash
 *
 */
static void splash_update(void);

/**
 * @brief Dibuja el splash
 *
 */
static void splash_draw(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Rana
static frog_t frog;

// Array de troncos
static log_t log[LOGS_MAX_USED];

// Array de autos
static car_t car[CARS_MAX_USED];

// Array de paquetes de tortugas
static turtle_pack_t turtle_pack[TURTLES_MAX_USED];

// Coin
static coin_t coin;

// Contador de frames ejecutados
static unsigned long game_frames;

// Carriles variables.
static unsigned char normal_diff_lane;
static unsigned char hard_diff_lane_1;
static unsigned char hard_diff_lane_2;

// Maximo de autos spawneados.

static unsigned char cars_spawn_max;

// Flag muestra tutorial

static bool tutorial_flag;
/*******************************************************************************
 *******************************************************************************
            GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void entities_init(void)
{
	tutorial_flag = false;
	frog_init();
	logs_init();
	cars_init();
	turtles_init();
	coin_init();

	game_frames = 0;

	corpse_fx.flag = false;

	splash_fx.flag = false;
}

void entities_update()
{
	game_frames = game_data_get_frames();
	
	frog_update();
	logs_update();
	cars_update();
	turtles_update();
	coin_update();

	corpse_update();
	splash_update();
}

void entities_draw()
{
	logs_draw();
	cars_draw();
	turtles_draw();
	coin_draw();

	splash_draw();
	corpse_draw();

	//"frog siempre a lo ultimo, para que se vea"
	frog_draw();
}

void entities_move_frog(unsigned char direction)
{
	if(tutorial_flag){
		if (direction == DIRECTION_DOWN || direction == DIRECTION_LEFT ||
			direction == DIRECTION_UP || direction == DIRECTION_RIGHT)
		{
			frog.next_action = direction;
		}
	}
}

void entities_set_tutorial(void){
	tutorial_flag = true;
}

bool entities_get_tutorial(void){
	return tutorial_flag;
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

				//colision con coin
				if(coin.used)
				{
					if(collideShort(	coin.x,
										coin.y,
										SPRITE_COIN_SIDE,
										SPRITE_COIN_SIDE,
										frog.x,
										frog.y,
										FROG_W,
										FROG_H))
					{
						frog.state = FROG_STATE_GOAL_COIN;
						coin.used = false;
					}
				}

				
			}

			interaction_flag = true;
		}
			
	}

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

			splash_init(frog.x, frog.y);

			frog_init();
			
			
			break;
		
		case FROG_STATE_CRASH_CAR:
			game_data_subtract_live();
			allegro_sound_play_effect_crash();

			corpse_init(frog.x, frog.y);

			frog_init();

			break;
		
		case FROG_STATE_CRASH_WALL:
			game_data_subtract_live();
			allegro_sound_play_effect_crash();

			corpse_init(frog.x, frog.y);

			frog_init();

			break;
		
		case FROG_STATE_GOAL:
			game_data_add_run_time_goal();
			game_data_add_score();
			allegro_sound_play_effect_goal();
			
			frog_init();
			
			break;
			
		case FROG_STATE_GOAL_COIN:
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

	ALLEGRO_BITMAP *tempbitmap = NULL;

	if (frog.moving)
	{
		if (frog.facing == DIRECTION_UP)
			tempbitmap = sprites.frog[1];
		if (frog.facing == DIRECTION_DOWN)
			tempbitmap = sprites.frog[7];
		if (frog.facing == DIRECTION_RIGHT)
			tempbitmap = sprites.frog[3];
		if (frog.facing == DIRECTION_LEFT)
			tempbitmap = sprites.frog[5];
	}

	else if (!frog.moving)
	{
		if (frog.facing == DIRECTION_UP)
			tempbitmap = sprites.frog[0];
		if (frog.facing == DIRECTION_DOWN)
			tempbitmap = sprites.frog[6];
		if (frog.facing == DIRECTION_RIGHT)
			tempbitmap = sprites.frog[2];
		if (frog.facing == DIRECTION_LEFT)
			tempbitmap = sprites.frog[4];
	}

	al_draw_bitmap(tempbitmap, frog.x, frog.y, 0);

#ifdef DEBUG_ENTITIES_TEXT
	// hitbox
	allegro_draw_hitbox(frog.x, frog.y, FROG_W, FROG_H);
	// coordenadas rana
	al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, 0, 0, "X: %d Y: %d", frog.x, frog.y);
#endif
}

static void logs_init(void)
{
	int i;
	for (i = 0; i < LOGS_MAX_USED; i++)
		log[i].used = false;
}

static void logs_update(void)
{
	// se busca spawnear entre LOGS_SPAWN_MIN y LOGS_SPAWN_MAX autos cada LOGS_SPAWN_FRAMES frames
	int new_quota = ((game_frames % LOGS_SPAWN_FRAMES) ? 0 : get_rand_between(LOGS_SPAWN_MIN, LOGS_SPAWN_MAX));

	int i, used;

	// cuento cuantos troncos usados hay
	for (i = 0, used = 0; i < LOGS_MAX_USED; i++)
		used += log[i].used;

	for (i = 0; i < LOGS_MAX_USED; i++)
	{
		// Spawneo de troncos
		if (!log[i].used && new_quota > 0 && used < LOGS_MAX_USED) // Lugar libre?
		{

			// Asigno carril.
			int temp_rand_log_lane = get_rand_between(0, LANES_LOG_TOTAL - 1);
			log[i].lane = lanes_logs[temp_rand_log_lane];

			// Coordenada 'y' en funcion del carril
			log[i].y = CELL_H * log[i].lane + LOG_OFFSET_Y;

			// Velocidad
			// log[i].dx = lanes_logs[LANES_LOG_TOTAL-1] - log[i].lane + 1;
			// log[i].dx = map_int(log[i].lane, 0, lanes_logs[LANES_LOG_TOTAL-1], 1, 3);
			log[i].dx = log[i].lane - (temp_rand_log_lane + 2) + LOGS_BASE_SPEED;

			// en pares...
			if (!(log[i].lane % 2))
			{
				// coordenada de inicio
				log[i].x = -LOG_W;
			}

			// en impares...
			else
			{
				// coordenada de inicio
				log[i].x = DISPLAY_W;

				// hacia el otro lado
				log[i].dx *= (-1);
			}

			int p;
			bool check; // para confirmar asignacion de lane
			for (p = 0, check = true; p < LOGS_MAX_USED; p++)
			{
				// si no es el mismo tronco, y ese otro esta usado, y coinciden en lane...
				if (p != i && log[p].used && log[p].lane == log[i].lane)
				{
					// si colisiona con algun otro tronco...
					if (collide(
							log[i].x - LOGS_EXTRA_SEPARATOR,
							log[i].y,
							log[i].x + LOG_W + LOGS_EXTRA_SEPARATOR,
							log[i].y + LOG_H,
							log[p].x,
							log[p].y,
							log[p].x + LOG_W,
							log[p].y + LOG_H))
					{
						// no spawnea
						check = false;
						break;
					}
				}
			}

			// si se puede spawnear...
			if (check)
			{
				// Pasa a usado
				log[i].used = true;
				used++;
				new_quota--;
			}

			// si no se puede spawnear...
			else
			{
			}
		}

		// si el tronco esta usado...
		else if (log[i].used)
		{
			// desplaza
			log[i].x += log[i].dx;

			// chequea si llego a los limites
			if ((log[i].dx > 0 && log[i].x >= DISPLAY_W) || (log[i].dx < 0 && log[i].x <= -LOG_W))
			{
				log[i].used = false;
				used--;
			}

			// printf("~log%d lane%d dx%d~\n", i, log[i].lane, log[i].dx);
		}
	}
}

static void logs_draw(void)
{
	int i;

	for (i = 0; i < LOGS_MAX_USED; i++)
	{
		if (log[i].used)
		{
			al_draw_bitmap(sprites.log, log[i].x, log[i].y, 0);

#ifdef DEBUG_ENTITIES_TEXT
			// hitbox
			allegro_draw_hitbox(log[i].x, log[i].y, LOG_W, LOG_H);
#endif
		}
	}

#ifdef DEBUG_ENTITIES_TEXT
	// coordenadas
	int space;
	for (i = 0, space = 20; i < LOGS_MAX_USED; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, log[i].x, log[i].y);
	}
#endif
}

static void cars_init(void)
{
	int i;
	// Inicio array de autos desocupando.
	for (i = 0; i < CARS_MAX_USED; i++)
		car[i].used = false;

	switch (game_data_get_diff())
	{
	case DIFFICULTIES_EASY:
		cars_spawn_max = 3;
		break;

	case DIFFICULTIES_NORMAL:
		normal_diff_lane = get_rand_between(lanes_cars[0], lanes_cars[LANES_CAR_TOTAL - 1]);
		cars_spawn_max = 4;
		break;

	case DIFFICULTIES_HARD:
		hard_diff_lane_1 = get_rand_between(lanes_cars[0], lanes_cars[2]);
		hard_diff_lane_2 = get_rand_between(lanes_cars[3], lanes_cars[4]);
		cars_spawn_max = 5;
		break;
	}
}

static void cars_update(void)
{
	// se busca spawnear entre CARS_SPAWN_MIN y cars_spawn_max autos cada CARS_SPAWN_FRAMES frames
	int new_quota = ((game_frames % CARS_SPAWN_FRAMES) ? 0 : get_rand_between(CARS_SPAWN_MIN, cars_spawn_max));

	int i, used;

	// cuento cuantos autos usados hay
	for (i = 0, used = 0; i < CARS_MAX_USED; i++)
		used += car[i].used;

	for (i = 0; i < CARS_MAX_USED; i++)
	{
		// Spawneo de autos.
		if (!car[i].used && new_quota > 0 && used < CARS_MAX_USED) // Lugar libre?
		{
			// Asigno carril.
			car[i].lane = lanes_cars[get_rand_between(0, LANES_CAR_TOTAL - 1)];

			// Coordenada 'y' en funcion del carril
			car[i].y = CELL_H * car[i].lane + CAR_OFFSET_Y;

			// Velocidad menor en rutas mas alejadas
			car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED;
			// car[i].dx = CARS_BASE_SPEED;

			// Asigno tipos.
			car[i].type = get_rand_between(0, CAR_TYPE_N - 1);

			// Defino los largos correspondientes,
			switch (car[i].type)
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

			// Inicializo el contador;
			car[i].count = 0;

			// Inicializo el flag.
			car[i].fast = 0;

			// en pares...
			if (!(car[i].lane % 2))
			{
				// coordenada de inicio
				car[i].x = -car[i].length;
			}

			// en impares...
			else
			{
				// coordenada de inicio
				car[i].x = DISPLAY_W;

				// hacia el otro lado
				car[i].dx *= (-1);
			}

			int p;
			bool check; // para confirmar asignacion de lane
			for (p = 0, check = true; p < CARS_MAX_USED; p++)
			{
				// si no es el mismo auto, y ese otro esta usado, y coinciden en lane...
				if (p != i && car[p].used && car[p].lane == car[i].lane)
				{
					// si colisiona con algun otro auto...
					if (collide(
							car[i].x - CARS_EXTRA_SEPARATOR,
							car[i].y,
							car[i].x + car[i].length + CARS_EXTRA_SEPARATOR, // Es el mas largo.
							car[i].y + CAR_H,
							car[p].x,
							car[p].y,
							car[p].x + car[p].length,
							car[p].y + CAR_H))
					{
						// no spawnea
						check = false;
						break;
					}
				}
			}

			// si se puede spawnear...
			if (check)
			{
				// Pasa a usado
				car[i].used = true;
				used++;
				new_quota--;
			}

			// si no se puede spawnear...
			else
			{
			}
		}

		// si el auto esta usado...
		else if (car[i].used)
		{
			// Carril con velocidad variable
			if (car[i].count < CAR_WAIT_INCREASE)
			{
				switch (game_data_get_diff())
				{
				case DIFFICULTIES_EASY:
					break;

				case DIFFICULTIES_NORMAL:
					if (car[i].lane == normal_diff_lane)
					{
						if (!(game_frames % FPS))
						{
							if (car[i].fast == 0)
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED + CAR_SPEED_INCREASE;
								if (car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 1;
							}
							else
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED;
								if (car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 0;
							}
						}
					}
					break;
				case DIFFICULTIES_HARD:
					if ((car[i].lane == hard_diff_lane_1) || (car[i].lane == hard_diff_lane_2))
					{
						if (!(game_frames % FPS))
						{
							if (car[i].fast == 0)
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED + CAR_SPEED_INCREASE;
								if (car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 1;
							}
							else
							{
								car[i].dx = car[i].lane - (MAX_LANES - LANES_CAR_TOTAL) + CARS_BASE_SPEED;
								if (car[i].lane % 2)
									car[i].dx *= (-1);
								car[i].fast = 0;
							}
						}
					}
				default:
					break;
				}
			}
			else
				car[i].count++;

			// Desplazamiento
			car[i].x += car[i].dx;

			// chequea si llego a los limites
			if ((car[i].dx > 0 && car[i].x >= DISPLAY_W) || (car[i].dx < 0 && car[i].x <= -car[i].length))
			{
				car[i].used = false;
				used--;
			}

			// printf("~car%d lane%d dx%d~\n", i, car[i].lane, car[i].dx);
		}
	}
}

static void cars_draw()
{
	int i;
	bool flag;

	ALLEGRO_BITMAP *temp_bitmap = NULL;

	for (i = 0; i < CARS_MAX_USED; i++)
	{
		if (car[i].used)
		{
			if (car[i].dx < 0)
				flag = ALLEGRO_FLIP_HORIZONTAL;
			else
				flag = 0;

			temp_bitmap = sprites.car[car[i].type];

			// Dibujo los autos en sus carriles.
			al_draw_bitmap(temp_bitmap, car[i].x, car[i].y, flag);

#ifdef DEBUG_ENTITIES_TEXT
			// Dibujo hitbox
			allegro_draw_hitbox(car[i].x, car[i].y, car[i].length, CAR_H);
#endif
		}
	}

#ifdef DEBUG_ENTITIES_TEXT
	// coordenadas
	int space;
	for (i = 0, space = 200; i < CARS_MAX_USED; i++, space += 20)
	{
		// al_draw_textf(allegro_get_var_font(), al_map_rgb(255, 255, 255), 0, space, 0, "N°:%d X:%d Y:%d dx:%d", i, car[i].x, car[i].y, car[i].dx);
		al_draw_textf(allegro_get_var_font(), al_map_rgb(255, 255, 255), 0, space, 0, "Lane:%d dx:%d", car[i].lane, car[i].dx);
	}
#endif
}

static void turtles_init(void)
{
	int i;
	for (i = 0; i < TURTLES_MAX_USED; i++)
	{
		turtle_pack[i].used = false;
	}
}

static void turtles_update(void)
{
	int new_quota = ((game_frames % TURTLES_SPAWN_FRAMES) ? 0 : get_rand_between(TURTLES_SPAWN_MIN, TURTLES_SPAWN_MAX));

	int i, used;

	for (i = 0, used = 0; i < TURTLES_MAX_USED; i++)
	{
		if (turtle_pack[i].used)
			used++;
	}

	for (i = 0; i < TURTLES_MAX_USED; i++)
	{
		// Spawneo de turtle_packs
		if (!turtle_pack[i].used && new_quota > 0 && used < TURTLES_MAX_USED) // Lugar libre?
		{

			// defino tortugas en el pack
			turtle_pack[i].turtles_in_pack = get_rand_between(TURTLES_MIN_PER_PACK, TURTLES_MAX_PER_PACK);

			// calculo ancho del pack
			turtle_pack[i].wide = TURTLE_SIDE * turtle_pack[i].turtles_in_pack;

			// Asigno carril.
			turtle_pack[i].lane = lanes_turtles[get_rand_between(0, LANES_TURTLE_TOTAL - 1)];

			// Coordenada 'y' en funcion del carril
			turtle_pack[i].y = CELL_H * turtle_pack[i].lane;

			// Velocidad
			// turtle_pack[i].dx = lanes_turtles[LANES_TURTLE_TOTAL- turtle_pack[i].lane + 1];
			turtle_pack[i].dx = TURTLES_BASE_SPEED;

			// en pares...
			if (!(turtle_pack[i].lane % 2))
			{
				// coordenada de inicio
				turtle_pack[i].x = -turtle_pack[i].wide;
			}

			// en impares...
			else
			{
				// coordenada de inicio
				turtle_pack[i].x = DISPLAY_W;

				// hacia el otro lado
				turtle_pack[i].dx *= (-1);
			}

			int p;
			bool check; // para confirmar asignacion de lane
			for (p = 0, check = true; p < TURTLES_MAX_USED; p++)
			{
				// si no es el mismo pack, y ese otro esta usado, y coinciden en lane...
				if (p != i && turtle_pack[p].used && turtle_pack[p].lane == turtle_pack[i].lane)
				{
					// si colisiona con algun otro pack...
					if (collide(
							turtle_pack[i].x - TURTLES_EXTRA_SEPARATOR,
							turtle_pack[i].y,
							turtle_pack[i].x + turtle_pack[i].wide + TURTLES_EXTRA_SEPARATOR,
							turtle_pack[i].y + TURTLE_SIDE,
							turtle_pack[p].x,
							turtle_pack[p].y,
							turtle_pack[p].x + turtle_pack[p].wide,
							turtle_pack[p].y + TURTLE_SIDE))
					{
						// no spawnea
						check = false;
						break;
					}
				}
			}

			// si se puede spawnear...
			if (check)
			{
				// Pasa a usado
				turtle_pack[i].used = true;
				used++;

				// se inicializa el contador de frames
				turtle_pack[i].fx.frame = 0;
				turtle_pack[i].fx.cont = 1;
				turtle_pack[i].fx.timeout = 0;
				// fuera del agua
				turtle_pack[i].state = TURTLE_STATE_SURFACE;

				new_quota--;
			}

			// si no se puede spawnear...
			else
			{
			}
		}

		// si el pack esta usado...
		else if (turtle_pack[i].used)
		{
			// desplaza
			turtle_pack[i].x += turtle_pack[i].dx;

			switch (turtle_pack[i].state)
			{
			case TURTLE_STATE_SURFACE:
				if (!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_SURFACE))
					turtle_pack[i].fx.frame++;

				// si no esta inicializado, inicializo timeout
				if (!turtle_pack[i].fx.timeout)
					turtle_pack[i].fx.timeout = get_rand_between(TURTLES_SURFACE_FRAMES_MIN, TURTLES_SURFACE_FRAMES_MAX);

				// pasa a agua
				if (!(turtle_pack[i].fx.cont % turtle_pack[i].fx.timeout))
				{
					turtle_pack[i].state = TURTLE_STATE_GOING_DOWN;
					turtle_pack[i].fx.frame = 7;
					turtle_pack[i].fx.timeout = 0;
					turtle_pack[i].fx.cont = 1;
				}

				// Reinicia animacion
				else if (turtle_pack[i].fx.frame == 7)
					turtle_pack[i].fx.frame = 0;

				break;

			case TURTLE_STATE_GOING_DOWN:
				if (!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_GOING_DOWN))
					turtle_pack[i].fx.frame++;

				if (turtle_pack[i].fx.frame == 9)
				{
					turtle_pack[i].state = TURTLE_STATE_WATER;
					turtle_pack[i].fx.cont = 1;
				}

				break;

			case TURTLE_STATE_WATER:
				if (!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_WATER))
					turtle_pack[i].fx.frame++;

				// si no esta inicializado, inicializo timeout
				if (!turtle_pack[i].fx.timeout)
					turtle_pack[i].fx.timeout = get_rand_between(TURTLES_WATER_FRAMES_MIN, TURTLES_WATER_FRAMES_MAX);

				// pasa a fuera
				if (!(turtle_pack[i].fx.cont % turtle_pack[i].fx.timeout))
				{
					turtle_pack[i].state = TURTLE_STATE_GOING_UP;
					turtle_pack[i].fx.frame = 10;
					turtle_pack[i].fx.timeout = 0;
					turtle_pack[i].fx.cont = 1;
				}

				// Reinicia animacion
				else if (turtle_pack[i].fx.frame == 11)
					turtle_pack[i].fx.frame = 9;

				break;

			case TURTLE_STATE_GOING_UP:
				if (!(turtle_pack[i].fx.cont++ % TURTLES_FRAME_TIMEOUT_GOING_UP))
					turtle_pack[i].fx.frame--;

				if (turtle_pack[i].fx.frame == 7)
				{
					turtle_pack[i].fx.frame = 6;
					turtle_pack[i].state = TURTLE_STATE_SURFACE;
					turtle_pack[i].fx.cont = 1;
				}

				break;

			default:
				break;
			}

			// chequea si llego a los limites
			if ((turtle_pack[i].dx > 0 && turtle_pack[i].x >= DISPLAY_W) || (turtle_pack[i].dx < 0 && turtle_pack[i].x <= -turtle_pack[i].wide))
			{
				turtle_pack[i].used = false;
				used--;
			}

			// printf("~turtle_pack%d lane%d dx%d~\n", i, turtle_pack[i].lane, turtle_pack[i].dx);
		}
	}
}

static void turtles_draw(void)
{
	int i, j, flag;
	for (i = 0; i < TURTLES_MAX_USED; i++)
	{
		if (turtle_pack[i].used)
		{
			for (j = 0; j < turtle_pack[i].turtles_in_pack; j++)
			{
				if (turtle_pack[i].dx < 0)
					flag = ALLEGRO_FLIP_HORIZONTAL;
				else
					flag = 0;

				al_draw_bitmap(sprites.turtle[turtle_pack[i].fx.frame], turtle_pack[i].x + TURTLE_SIDE * j, turtle_pack[i].y, flag);
			}

#ifdef DEBUG_ENTITIES_TEXT
			// Dibujo hitbox
			allegro_draw_hitbox(turtle_pack[i].x, turtle_pack[i].y, turtle_pack[i].wide, TURTLE_SIDE);
#endif
		}
	}

#ifdef DEBUG_ENTITIES_TEXT
	// coordenadas
	int space;
	for (i = 0, space = 350; i < TURTLES_MAX_USED; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, turtle_pack[i].x, turtle_pack[i].y);
	}
#endif
}

static void coin_init(void)
{
	coin.used = false;
	coin.y = CELL_H + SPRITE_COIN_OFFSET_XY + GOAL_ROW_OFFSET_Y_FIX;

	coin.fx.blink_timer = 0;
	coin.fx.timeout = 0;
	coin.fx.flag = false;
	coin.fx.cont = 1;
}

static void coin_update(void)
{
	if (!coin.used)
	{
		// si no esta inicializado, inicializo timeout para spawneo
		if (!coin.fx.timeout)
			coin.fx.timeout = get_rand_between(COIN_SPAWN_FRAMES_MIN, COIN_SPAWN_FRAMES_MAX);

		if (!(coin.fx.cont % coin.fx.timeout))
		{
			// calculo de coordenada x para alguno de los puntos de llegada
			int temp_goal = get_rand_between(0, MAX_GOALS - 1);

			// si el goal está libre...
			if (!game_data_get_goal_state(temp_goal))
			{
				allegro_sound_play_effect_coin_drop();

				coin.x = CELL_W * goal_cols[temp_goal] + SPRITE_COIN_OFFSET_XY - 1;
				// marcado como usado
				coin.used = true;
				// desinicializo el timeout
				coin.fx.timeout = 0;

				coin.fx.blink_timer = 0;
				coin.fx.cont = 1;
				coin.fx.frame_cont = 0;
			}

			// si no, cuando pasa otro timeout se intenta de nuevo
			else
			{
			}
		}
	}

	else
	{
		// timeout para despawneo
		if (!coin.fx.timeout)
			coin.fx.timeout = get_rand_between(COIN_DESPAWN_FRAMES_MIN, COIN_DESPAWN_FRAMES_MAX);

		if (++coin.fx.blink_timer > coin.fx.timeout - COIN_FRAMES_TO_WARN_A)
		{
			if (coin.fx.blink_timer > coin.fx.timeout - COIN_FRAMES_TO_WARN_B)
			{
				if (!(coin.fx.cont % COIN_WARNING_FRAMES_B))
					coin.fx.flag = !coin.fx.flag;
			}
			else
			{
				if (!(coin.fx.cont % COIN_WARNING_FRAMES_A))
					coin.fx.flag = !coin.fx.flag;
			}
		}

		if (!(game_frames % COIN_FRAME_RATE))
		{
			if (++coin.fx.frame_cont == SPRITE_COIN_FRAMES)
				coin.fx.frame_cont = 0;
		}

		// si se puede despawnear
		if (!(coin.fx.cont % coin.fx.timeout))
		{
			// coin no usada
			coin.used = false;

			// desinicializo timeout
			coin.fx.timeout = 0;

			// saco el blinking
			coin.fx.flag = false;

			coin.fx.cont = 1;
		}
	}

	coin.fx.cont++;
}

static void coin_draw(void)
{
	if (coin.used)
	{
		// Si no está el flag, dibujo sprite normalmente
		if (!coin.fx.flag)
			al_draw_bitmap(sprites.coin.frame[coin.fx.frame_cont], coin.x, coin.y, 0);
	}

#ifdef DEBUG_ENTITIES_TEXT

	// hitbox
	allegro_draw_hitbox(coin.x, coin.y, COIN_SIDE, COIN_SIDE);

	// coordenadas
	int space = 500;
	al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "Coin ~ X:%d Y:%d", coin.x, coin.y);
#endif
}

static void fix_frog_coord_y(void)
{
	int y = (frog.y - FROG_OFFSET_Y);

	int y_values[ROWS];

	int i;

	// Carga valores "correctos" de y
	for (i = 1; i < ROWS - 1; i++)
		y_values[i] = i * CELL_H;

	int temp_a, temp_b;
	for (i = 1; i < ROWS - 1; i++)
	{
		temp_a = y - y_values[i];

		if (temp_a > 0)
			continue;
		if (temp_a == 0)
			break;

		temp_b = y_values[i - 1] - y;

		//"si está más cerca de la fila 'i' que de la 'i+1"
		if (temp_a <= temp_b)
			frog.y = y_values[i - 1] + FROG_OFFSET_Y;
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
	for (i = 0; i < MAX_GOALS; i++)
	{
		// Coordenada top left del punto de llegada
		x_col = goal_cols[i] * CELL_W;

		// Calculo para ver si entro bien o no
		if ((x > x_col - GOAL_ROW_MARGIN_TO_REACH) &&
			((x + FROG_W) < x_col + CELL_W + GOAL_ROW_MARGIN_TO_REACH))
		{
			// coodenada X aceptable
			state = true;
			break;
		}
	}

	// Si coincide en coordenada y el goal esta libre...
	if (state && !game_data_get_goal_state(i))
	{
		// marca el goal como completo
		game_data_set_goal(i);
	}
	else
	{
		// no llego a un goal valido
		state = false;
	}

	return state;
}

static void corpse_init(int x, int y)
{
	corpse_fx.flag = true;
	corpse_fx.timer = 1;
	corpse_fx.x = x - FROG_OFFSET_X + SPRITE_DEAD_OFFSET;
	corpse_fx.y = y - FROG_OFFSET_Y + SPRITE_DEAD_OFFSET;
}

static void corpse_update(void)
{
	if (corpse_fx.flag)
	{
		if (!(corpse_fx.timer++ % SPRITE_DEAD_TIMEOUT))
			corpse_fx.flag = false;
	}
}

static void corpse_draw(void)
{
	if (corpse_fx.flag)
		al_draw_bitmap(sprites.dead, corpse_fx.x, corpse_fx.y, 0);
}

static void splash_init(int x, int y)
{
	splash_fx.flag = true;
	splash_fx.cont = 1;
	splash_fx.frame_cont = 0;
	splash_fx.x = x - FROG_OFFSET_X + SPRITE_SPLASH_OFFSET_X;
	splash_fx.y = y - FROG_OFFSET_Y + SPRITE_SPLASH_OFFSET_Y;
}

static void splash_update(void)
{
	if (splash_fx.flag)
	{
		if (!(splash_fx.cont % SPRITE_SPLASH_RATE))
		{
			if (++splash_fx.frame_cont == SPRITE_SPLASH_FRAMES)
			{
				splash_fx.frame_cont = 0;
				splash_fx.flag = false;
			}
		}

		splash_fx.cont++;
	}
}

static void splash_draw(void)
{
	if (splash_fx.flag)
		al_draw_bitmap(sprites.splash.frame[splash_fx.frame_cont], splash_fx.x, splash_fx.y, 0);
}
