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

#define LOGS_SPAWN_MIN			1
#define LOGS_SPAWN_MAX			2
#define LOGS_SPAWN_FRAMES		60
#define LOGS_BASE_SPEED			2
#define LOGS_MAX_USED			4

#define CARS_SPAWN_MIN			1
#define CARS_SPAWN_MAX			2
#define CARS_SPAWN_FRAMES		60
#define CARS_BASE_SPEED			2
#define CARS_MAX_USED			4	

#define TURTLES_MIN_PER_PACK	2
#define	TURTLES_MAX_PER_PACK	3
#define TURTLES_SPAWN_FRAMES	60
#define TURTLES_SPAWN_MIN		1
#define TURTLES_SPAWN_MAX		2
#define TURTLES_MAX_USED		3	
#define TURTLES_BASE_SPEED		2
#define TURTLES_FRAME_TIMEOUT	10	//cuanto "tiempo" dura un frame dibujado antes de pasar al siguiente
#define	TURTLES_SURFACE_TIMEOUT	250	//cuanto dura sobra el agua
#define TURTLES_WATER_TIMEOUT	200	//cuanto dura bajo el agua

#define FLY_SPAWN_FRAMES_MIN	300	//mínimo tiempo para respawnear mosca
#define	FLY_SPAWN_FRAMES_MAX	600	//maximo tiempo para respawnear mosca
#define FLY_DESPAWN_FRAMES_MIN	600	//mínimo tiempo para sacar mosca
#define	FLY_DESPAWN_FRAMES_MAX	900	//maximo tiempo para sacar mosca


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
    int x;              //Posicion del auto 
	int y;
    int lane;           //Carril del auto.
	int dx;
    unsigned char type;
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
	unsigned char frame;			//contador que indica en qué frame de la animación se está (de 1 a TURTLES_FRAMES)
	int wide;						//ancho del paquete, proporcional a turtles_in_pack y a TURTLES_SIDE
	long timer;						//contador interno para cambiar de frame
	unsigned char state;			//estado (enum TURTLE_STATES) 
} turtle_pack_t;

typedef struct
{
	int x;
	int y;
	unsigned char goal;				//punto de llegada, entre 1 y MAX_GOALS
	bool used;						//flag de usada o no
	int timer;						//timer interno, para spawneo y despawneo
} fly_t;

enum TURTLE_STATES
{
	SURFACE,
	WATER
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
static void spawn_log(int i);

/**
 * @brief Alinea y centra la posición de la rana con las celdas del mapa, por desvios sobre troncos.
 * 
 */
static void fix_frog_pos(void);


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
static log_t log[MAX_LOGS];

//Array de autos
static car_t car[MAX_CARS];

//Array de paquetes de tortugas
static turtle_pack_t turtle_pack[MAX_TURTLE_PACKS];

//Mosca
static fly_t fly;

//Contador de frames ejecutados
static long frames;


/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void entities_init(void)
{
	frames = 0;

	frog_init();
	logs_init();
	cars_init();
	turtles_init();
	fly_init();
}

void entities_update()
{
	frames++;

	srand(time(NULL));

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
	frog.facing = UP;
	frog.steps = 0;
	//frog.surface = CHILL;
	frog.lives = MAX_LIVES;
}

static void frog_update(void)
{
	int i;

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

	//colision con troncos
	for(i = 0; i < MAX_LOGS; i++)
	{
		if(!log[i].used)
			continue;
		
		if(inside_log(i, frog.x, frog.y, FROG_W, FROG_H))
		{
			//printf("COLLIDE CON %d", i);
			//frog.surface = LOG;
			frog.x += log[i].dx;
			break;
		}
	}

	//colision con turtle_packs
	for(i = 0; i < MAX_TURTLE_PACKS; i++)
	{
		if(!turtle_pack[i].used)
			continue;
		
		if(inside(	turtle_pack[i].x,
					turtle_pack[i].y,
					turtle_pack[i].x + turtle_pack[i].wide,
					turtle_pack[i].y + TURTLE_SIDE,
					frog.x,
					frog.y,
					frog.x + FROG_W,
					frog.y + FROG_H))
		{
			frog.x += turtle_pack[i].dx;
			break;
		}
	}


	//revision de limites
	if(frog.x < FROG_MIN_X)
		frog.x = FROG_MIN_X;
	if(frog.x > FROG_MAX_X)
		frog.x = FROG_MAX_X;
	if(frog.y < FROG_MIN_Y)
		frog.y = FROG_MIN_Y;
	if(frog.y > FROG_MAX_Y)
		frog.y = FROG_MAX_Y;


}

static void frog_draw(void)
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

	//hitbox
	al_draw_rectangle(frog.x, frog.y, frog.x + FROG_W, frog.y + FROG_W, al_map_rgb(100, 100, 100), 1);

	//coordenadas rana
            al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, 0, 0, "X: %d Y: %d", frog.x, frog.y);

}

static void logs_init(void)
{
	int i;
	for(i = 0; i < MAX_LOGS; i++)
		log[i].used = false;

}

static void logs_update(void)
{
	//se busca spawnear entre LOGS_SPAWN_MIN y LOGS_SPAWN_MAX autos cada LOGS_SPAWN_FRAMES frames
	int new_quota = ((frames % LOGS_SPAWN_FRAMES) ? 0 : get_rand_between(LOGS_SPAWN_MIN, LOGS_SPAWN_MAX));

	int i, used;

	//cuento cuantos troncos usados hay
	for(i = 0, used = 0; i < MAX_LOGS; i++)
		used += log[i].used;

    for(i = 0; i < MAX_LOGS; i++)
    {
        //Spawneo de troncos
        if(!log[i].used && new_quota > 0 && used <= LOGS_MAX_USED)           //Lugar libre?
        {

			//Asigno carril.
			log[i].lane = lanes_logs[get_rand_between(0, LANES_LOG_TOTAL-1)];
			
			//Coordenada 'y' en funcion del carril	
			log[i].y = CELL_H * log[i].lane + LOG_OFFSET_Y;	

			//Velocidad
			log[i].dx = lanes_logs[LANES_LOG_TOTAL-1] - log[i].lane + 1;
			//log[i].dx = map_int(log[i].lane, 0, lanes_logs[LANES_LOG_TOTAL-1], 1, 3);

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
			for(p = 0, check = true; p < MAX_LOGS; p++)
			{
				//si no es el mismo tronco, y ese otro esta usado, y coinciden en lane...
				if(p != i && log[p].used && log[p].lane == log[i].lane)
				{
					//si colisiona con algun otro tronco...
					if	(collide(
									log[i].x,
									log[i].y,
									log[i].x + LOG_W,
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
				log[i].used = false;

			//printf("~log%d lane%d dx%d~\n", i, log[i].lane, log[i].dx);

		}

    }

}

static void logs_draw(void)
{
	int i;

	for(i = 0; i < MAX_LOGS; i++)
	{
		if(log[i].used)
		{
			al_draw_bitmap(sprites.log, log[i].x, log[i].y, 0);

			//hitbox
			al_draw_rectangle(log[i].x, log[i].y, log[i].x + LOG_W, log[i].y + LOG_H, al_map_rgb(100, 100, 100), 1);
		}
			
	}

	//coordenadas
	int space;
	for(i = 0, space = 20; i < MAX_LOGS; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, log[i].x, log[i].y);
	}

}

static void cars_init(void)
{
	int i;
	//Inicio array de autos desocupando.
	for(i = 0; i < MAX_CARS; i++)
        car[i].used = false;   

}

static void cars_update(void)
{
	//se busca spawnear entre CARS_SPAWN_MIN y CARS_SPAWN_MAX autos cada CARS_SPAWN_FRAMES frames
	int new_quota = ((frames % CARS_SPAWN_FRAMES) ? 0 : get_rand_between(CARS_SPAWN_MIN, CARS_SPAWN_MAX));

	int i, used;

	//cuento cuantos autos usados hay
	for(i = 0, used = 0; i < MAX_CARS; i++)
		used += car[i].used;

    for(i = 0; i < MAX_CARS; i++)
    {
        //Spawneo de autos.
        if(!car[i].used && new_quota > 0 && used <= CARS_MAX_USED)	//Lugar libre?
        {
			//Asigno carril.
			car[i].lane = lanes_cars[get_rand_between(0, LANES_CAR_TOTAL-1)];

			//Coordenada 'y' en funcion del carril	
			car[i].y = CELL_H * car[i].lane + CAR_OFFSET_Y;	

			//Velocidad mayor en rutas mas alejadas
			car[i].dx = lanes_cars[LANES_CAR_TOTAL-1] - car[i].lane + 1;	

			//en pares...
			if(!(car[i].lane % 2))
			{
				//coordenada de inicio
				car[i].x = -CAR_W;
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
			for(p = 0, check = true; p < MAX_CARS; p++)
			{
				//si no es el mismo auto, y ese otro esta usado, y coinciden en lane...
				if(p != i && car[p].used && car[p].lane == car[i].lane)
				{
					//si colisiona con algun otro auto...
					if	(collide(
									car[i].x,
									car[i].y,
									car[i].x + CAR_W,
									car[i].y + CAR_H,
									car[p].x,
									car[p].y,
									car[p].x + CAR_W,
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
			//desplaza
			car[i].x += car[i].dx;

			//chequea si llego a los limites
			if((car[i].dx > 0 && car[i].x >= DISPLAY_W) || (car[i].dx < 0 && car[i].x <= -CAR_W))
				car[i].used = false;

			//printf("~car%d lane%d dx%d~\n", i, car[i].lane, car[i].dx);

		}

    }
}

static void cars_draw()
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
    {
        if(car[i].used)
		{
			//Dibujo los autos en sus carriles.
			al_draw_bitmap(sprites.car[0], car[i].x, car[i].y, 0); 

			//Dibujo hitbox
			al_draw_rectangle(car[i].x, car[i].y, car[i].x + CAR_W, car[i].y + CAR_H, al_map_rgb(100, 100, 100), 1);
		}
			   
		
    }

	//coordenadas
	int space;
	for(i = 0, space = 200; i < MAX_CARS; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, car[i].x, car[i].y);
	}
}

static void turtles_init(void)
{
	int i;
	for(i = 0; i < MAX_TURTLE_PACKS; i++)
	{
		turtle_pack[i].used = false;
	}
}

static void turtles_update(void)
{
	int new_quota = ((frames % TURTLES_SPAWN_FRAMES) ? 0 : get_rand_between(TURTLES_SPAWN_MIN, TURTLES_SPAWN_MAX));

	int i, used;

	//cuento cuantos packs usados hay
	for(i = 0, used = 0; i < MAX_TURTLE_PACKS; i++)
		used += turtle_pack[i].used;

    for(i = 0; i < MAX_TURTLE_PACKS; i++)
    {
        //Spawneo de turtle_packs
        if(!turtle_pack[i].used && new_quota > 0 && used <= TURTLES_MAX_USED)       //Lugar libre?
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
			for(p = 0, check = true; p < MAX_TURTLE_PACKS; p++)
			{
				//si no es el mismo pack, y ese otro esta usado, y coinciden en lane...
				if(p != i && turtle_pack[p].used && turtle_pack[p].lane == turtle_pack[i].lane)
				{
					//si colisiona con algun otro pack...
					if	(collide(
									turtle_pack[i].x,
									turtle_pack[i].y,
									turtle_pack[i].x + turtle_pack[i].wide,
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

				//se inicializa el contador de frames
				turtle_pack[i].frame = 0;			
				//se inicializa el timer para cambiar de frame
				turtle_pack[i].timer = 0;
				//fuera del agua
				turtle_pack[i].state = SURFACE;

				new_quota--;
			}

			//si no se puede spawnear...
			else
			{
				
			}

        }

		//si el tronco esta usado...
		else if(turtle_pack[i].used)
		{
			//desplaza
			turtle_pack[i].x += turtle_pack[i].dx;

			//aumenta timer interno
			turtle_pack[i].timer++;

			//pasa de frame
			if(!(turtle_pack[i].timer % TURTLES_FRAME_TIMEOUT))
				turtle_pack[i].frame++;
			
			//si esta fuera...
			if(turtle_pack[i].state == SURFACE)
			{
				if(turtle_pack[i].frame == 6)
					turtle_pack[i].frame = 0;

				//pasa a agua
				if(!(turtle_pack[i].timer % TURTLES_SURFACE_TIMEOUT))
				{
					turtle_pack[i].state = WATER;
					turtle_pack[i].frame = 7;
				}
			}

			//si esta bajo agua...
			else if(turtle_pack[i].state == WATER)
			{
				if(turtle_pack[i].frame == 11)
					turtle_pack[i].frame = 10;

				//pasa a fuera
				if(!(turtle_pack[i].timer % TURTLES_WATER_TIMEOUT))
				{
					turtle_pack[i].state = SURFACE;
					turtle_pack[i].frame = 0;
				}
			}
						

			//chequea si llego a los limites
			if((turtle_pack[i].dx > 0 && turtle_pack[i].x >= DISPLAY_W) || (turtle_pack[i].dx < 0 && turtle_pack[i].x <= -turtle_pack[i].wide))
				turtle_pack[i].used = false;

			//printf("~turtle_pack%d lane%d dx%d~\n", i, turtle_pack[i].lane, turtle_pack[i].dx);

		}

    }

}

static void turtles_draw(void)
{
	int i, j, flag;
	for(i = 0; i < MAX_TURTLE_PACKS; i++)
    {
        if(turtle_pack[i].used)
		{
			for(j = 0; j < turtle_pack[i].turtles_in_pack; j++)
			{
				if(turtle_pack[i].dx < 0)
					flag = ALLEGRO_FLIP_HORIZONTAL;	
				else
					flag = 0;
					
				al_draw_bitmap(sprites.turtle[turtle_pack[i].frame], turtle_pack[i].x + TURTLE_SIDE * j, turtle_pack[i].y, flag);
			}

			//Dibujo hitbox
			al_draw_rectangle(turtle_pack[i].x, turtle_pack[i].y, turtle_pack[i].x + turtle_pack[i].wide, turtle_pack[i].y + TURTLE_SIDE, al_map_rgb(100, 100, 100), 1);
		}
			   
		
    }

	//coordenadas
	int space;
	for(i = 0, space = 350; i < MAX_TURTLE_PACKS; i++, space += 10)
	{
		al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, turtle_pack[i].x, turtle_pack[i].y);
	}
}

static void fly_init(void)
{
	fly.used = false;
	fly.y = CELL_H + FLY_OFFSET_XY;
}

static void fly_update(void)
{
	//inicializado en 0 por ser static
	static int timeout;

	if(!fly.used)
	{
		//si no esta inicializado, inicializo timeout para spawneo
		if(!timeout)
			timeout = get_rand_between(FLY_SPAWN_FRAMES_MIN, FLY_SPAWN_FRAMES_MAX);
		
		if(!(frames % timeout))
		{
			//se elije uno de los puntos de llegada
			fly.goal = get_rand_between(0, MAX_GOALS-1);

			//calculo de coordenada x segun el punto elegido
			fly.x = CELL_W + (fly.goal * 2 * CELL_W) + FLY_OFFSET_XY;

			//marcado como usado
			fly.used = true;

			//recalculo timeout para el despawneo
			timeout = get_rand_between(FLY_DESPAWN_FRAMES_MIN, FLY_DESPAWN_FRAMES_MAX);
		}

	}

	else
	{
		//si se puede despawnear
		if(!(frames % timeout))
		{
			//mosca no usada
			fly.used = false;
			
			//desinicializo timeout
			timeout = 0;
		}
	}

}

static void fly_draw(void)
{
	if(fly.used)
	{
		//spirte
		al_draw_bitmap(sprites.fly, fly.x, fly.y, 0);

		//hitbox
		al_draw_rectangle(fly.x, fly.y, fly.x + FLY_SIDE, fly.y + FLY_SIDE, al_map_rgb(100,100,100), 1);
	}

	//coordenadas
	int space = 500;
	al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "Mosca ~ X:%d Y:%d", fly.x, fly.y);
	
}

static bool inside_log(int i, int x, int y, int w, int h)
{
	return(inside(  log[i].x, log[i].y, log[i].x + LOG_W, log[i].y + LOG_H,
					x, y, x + w, y + h));
}

static void spawn_log(int i)
{

	if(log[i].dx < 0)
	{
		log[i].x = DISPLAY_W;
	}

	else if(log[i].dx > 0)
	{
		log[i].x = (-1)*LOG_W ;
	}
    
    log[i].used = true;
}

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

 