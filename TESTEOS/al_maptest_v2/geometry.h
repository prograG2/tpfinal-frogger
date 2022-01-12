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
#define SPRITE_SIZE_FROG_STATIC_H       FROG_H
#define SPRITE_SIZE_FROG_STATIC_W       FROG_W
#define SPRITE_SIZE_FROG_DYNAMIC_LONG   46
#define SPRITE_SIZE_FROG_DYNAMIC_SHORT  FROG_W

//Para los pasos de la rana
#define STEP_FULL_SIZE  CELL_H
#define STEP_RATIO      (CELL_H/2)
#define STEP_FRACTION_SIZE  (STEP_FULL_SIZE / STEP_RATIO)

//Bordes para la rana en el mapa
#define FROG_MAX_X  (DISPLAY_W - (CELL_W - FROG_OFFSET_X))
#define FROG_MAX_Y  (DISPLAY_H - (CELL_H - FROG_OFFSET_Y))
#define FROG_MIN_X  (CELL_TOPLEFT_X + FROG_OFFSET_X)
#define FROG_MIN_Y  (CELL_TOPLEFT_Y + FROG_OFFSET_Y)


//Troncos
#define LOG_W   (4 * CELL_W)
#define LOG_H   40
#define LOG_OFFSET_X    0
#define LOG_OFFSET_Y    (CELL_H/2 - LOG_H/2)


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

enum DIRECTIONS
{
	UP,
	RIGHT,
	LEFT,
	DOWN
};

enum SURFACES
{
	CHILL,
	ROADWAY,
	WATER,
	TURTLE,
	LOG
};




/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


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


/*******************************************************************************
 ******************************************************************************/

#endif // _GEOMETRY_H_
