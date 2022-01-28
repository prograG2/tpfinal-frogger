/**
 * @file geometry.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <time.h>
#include <stdbool.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define DISPLAY_W   690
#define DISPLAY_H   644
#define ROWS    14
#define COLS    15
#define CELL_H  46
#define CELL_W  46

#define MAX_LANES			(ROWS - 1)	//-1 por la primera que es para HUD

#define LANES_CAR_TOTAL		5

#define LANES_LOG_TOTAL		3

#define LANES_TURTLE_TOTAL	2

//Coordenadas de la celda topleft (en su vértice topleft)
#define CELL_TOPLEFT_X  0 
#define CELL_TOPLEFT_Y  0

//Coordenadas de inicio ("ultima fila, columna 8"; referidas a topleft)
#define CELL_START_X    (CELL_TOPLEFT_X + CELL_W * ((COLS-1) / 2 ))
#define CELL_START_Y    (CELL_TOPLEFT_Y + CELL_H * (ROWS - 1))


#define FROG_W  30
#define FROG_H  30

#define FROG_OFFSET_X   (CELL_W / 2 - FROG_W/2)
#define FROG_OFFSET_Y   (CELL_H / 2 - FROG_H/2)

//Coordenadas inicio rana
#define CELL_START_FROG_X   (CELL_START_X + FROG_OFFSET_X)
#define CELL_START_FROG_Y   (CELL_START_Y + FROG_OFFSET_Y)

//Para los sprites de la rana
#define FROG_FRAMES						8
#define SPRITE_SIZE_FROG_STATIC_H       FROG_H
#define SPRITE_SIZE_FROG_STATIC_W       FROG_W
#define SPRITE_SIZE_FROG_DYNAMIC_LONG   46
#define SPRITE_SIZE_FROG_DYNAMIC_SHORT  FROG_W

//Para los pasos de la rana
#define STEP_FULL_SIZE  CELL_H
#define STEP_RATIO      (CELL_H/3)
#define STEP_FRACTION_SIZE  (STEP_FULL_SIZE / STEP_RATIO)

//Bordes para la rana en el mapa
#define FROG_MAX_X  (DISPLAY_W - (CELL_W - FROG_OFFSET_X))
#define FROG_MAX_Y  (DISPLAY_H - (CELL_H - FROG_OFFSET_Y))
#define FROG_MIN_X  (CELL_TOPLEFT_X + FROG_OFFSET_X)
#define FROG_MIN_Y  (CELL_TOPLEFT_Y + FROG_OFFSET_Y + CELL_H)


//Troncos
#define LOG_W   		(4 * CELL_W)
#define LOG_H   		40
#define LOG_OFFSET_X    0
#define LOG_OFFSET_Y    (CELL_H/2 - LOG_H/2)

//Autos
#define CAR_W   		(4 * CELL_W)
#define CAR_H   		40
#define CAR_OFFSET_X    0
#define CAR_OFFSET_Y    (CELL_H/2 - LOG_H/2)

//Tortugas
#define TURTLE_FRAMES							11	//11 frames distintos tiene la animación completa
#define	TURTLE_SIDE								CELL_W
#define TURTLE_FRAME_OFFSET_XY					(CELL_W/2 - TURTLE_SIDE/2)


//Moscas
#define	FLY_SIDE				30
#define	FLY_OFFSET_XY			(CELL_W/2 - FLY_SIDE/2)


#define SPRITE_SIZE_HEART	20	//cuadrado


#define MENU_OPTION_TOPLEFT_X 	45
#define MENU_OPTION_TOPLEFT_Y	175
#define MENU_OPTION_DELTA_Y		100
#define MENU_OPTION_W			600
#define MENU_OPTION_H			75


//Factor que determina cuando considerar que un bloque esta dentro de otro (ver 'inside_short_scaled')
#define INSERTION_FACTOR		(double)0.75


#define GOAL_ROW_OFFSET_Y_FIX		5	//baja un poco mas en Y
#define GOAL_ROW_MARGIN_TO_REACH	5	//holgura para meterse a uno de los goals


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
	int x;
	int y;

} pair_xy_t;

enum GOALS
{
	GOAL_LEFT,
	GOAL_LEFT_MID,
	GOAL_MID,
	GOAL_RIGHT_MID,
	GOAL_RIGHT,
	MAX_GOALS
};

enum DIRECTIONS
{
	DIRECTION_NONE,
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_LEFT,
	DIRECTION_DOWN
};

enum MENU_STATES
{
	MENU_STATE_OPCION_0,
	MENU_STATE_OPCION_1,
	MENU_STATE_OPCION_2,
	MENU_STATE_OPCION_3,
	MENU_STATE_OPCION_4,
	MENU_STATE_MAX
};

enum MENU_WINDOWS
{
	MENU_WINDOW_HOME,
	MENU_WINDOW_DIFFICULTY,
	MENU_WINDOW_PAUSE,
	MENU_WINDOW_GAME_OVER,
	MENU_WINDOW_MAX
};

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

//filas para troncos (referenciadas a 0
extern const unsigned int lanes_logs[LANES_LOG_TOTAL];
//filas para tortugas (referenciadas a 0
extern const unsigned int lanes_turtles[LANES_TURTLE_TOTAL];
//filas para autos (referenciadas a 0
extern const unsigned int lanes_cars[LANES_CAR_TOTAL];
//columnas para los puntos de llegada (referenciadas a 0)
extern const unsigned int goal_cols[MAX_GOALS];

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Devuelve un randon entre dos numeros dados
 * 
 * @param low Valor inferior
 * @param high Valor superior
 * @return int Valor random
 */
int get_rand_between(int low, int high);

/**
 * @brief Comprueba colición de hitboxes rectangulares
 * 
 * @param ax1 topleft corner de a (x)
 * @param ay1 topleft corner de a (y)
 * @param ax2 bottomright corner de a (x)
 * @param ay2 bottomright corner de a (y)
 * @param bx1 topleft corner de b (x)
 * @param by1 topleft corner de b (y)
 * @param bx2 bottomright corner de b (x)
 * @param by2 bottomright corner de b (y)
 * @return true Colisión
 * @return false No colisión
 */
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

/**
 * @brief Similar a 'collide', pero pide ancho y alto en vez de segundas coordenadas
 * 
 * @param ax topleft corner x de a
 * @param ay topleft corner y de a
 * @param aw ancho de a
 * @param ah alto de a
 * @param bx topleft corner x de b
 * @param by topleft corner y de b
 * @param bw ancho de b
 * @param bh alto de b
 * @return true Colision
 * @return false No colision
 */
bool collide_short(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);

/**
 * @brief Detecta si un rectángulo está dentro de otro
 * 
 * @param ax1 topleft corner de big (x)
 * @param ay1 topleft corner de big (y)
 * @param ax2 bottomright corner de big (x)
 * @param ay2 bottomright corner de big (y)
 * @param bx1 topleft corner de small (x)
 * @param by1 topleft corner de small (y)
 * @param bx2 bottomright corner de small (x)
 * @param by2 bottomright corner de small (y)
 * @return true Está dentro
 * @return false Está fuera
 */
bool inside(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

/**
 * @brief Similar a 'inside', pero pide ancho y alto en vez de segundas coordenadas
 * 
 * @param ax topleft corner x de big
 * @param ay topleft corner y de big
 * @param aw ancho de big
 * @param ah alto de big
 * @param bx topleft corner x de big
 * @param by topleft corner y de big
 * @param bw ancho de big
 * @param bh alto de big
 * @return true Esta dentro
 * @return false Esta fuera
 */
bool inside_short(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);

/**
 * @brief Similar a 'inside_short', pero permite setear cuan dentro debe estar una box dentro de la otra para tomarla como tal
 * 
 * @param ax topleft corner x de big
 * @param ay topleft corner y de big
 * @param aw ancho de big
 * @param ah alto de big
 * @param bx topleft corner x de big
 * @param by topleft corner y de big
 * @param bw ancho de big
 * @param bh alto de big
 * @param scale Factor de insercion. Entre 0.0 (nada metido) y 1.0 (completamente metido). Otro valor devuelve false
 * @return true 
 * @return false 
 */
bool inside_shot_scaled(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh, float scale);

/**
 * @brief Toma un valor comprendido dentro de un rango (in) y lo devuelve (mapea) a otro rango (out)
 * 
 * @source https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another
 * 
 * @param source Valor a mapear
 * @param min_in Limite inferior del rango de entrada
 * @param max_in Límite superior del rango de entrada
 * @param min_out Límite inferior del rango de salida
 * @param max_out Límite superior del rango de salida
 * @return int Valor mapeado
 */
int map_int(int source, int min_in, int max_in, int min_out, int max_out);

/**
 * @brief Devuelve par de coordenadas xy topleft de un frame dado del sprite de la rana
 * 
 * @param frame Numero de frame (0 a FROG_FRAMES)
 * @return pair_xy_t Par de coordenadas
 */
pair_xy_t geometry_get_pair_xy_frog_frame(int frame);

/**
 * @brief Devuelve par de coordenadas xy topleft de un frame dado del sprite de la tortuga
 * 
 * @param frame Numero de frame (0 a TURTLE_FRAMES)
 * @return pair_xy_t Par de coordenadas
 */
pair_xy_t geometry_get_pair_xy_turtle_frame(int frame);

/**
 * @brief Verifica si un numero coincide con alguno de un array dado (uints)
 * 
 * @param val Numero a verificar
 * @param array Array de numeros
 * @return true Existe
 * @return false No existe
 */
bool match_uint(unsigned int val, const unsigned int *array);



/*******************************************************************************
 ******************************************************************************/

#endif // _GEOMETRY_H_
