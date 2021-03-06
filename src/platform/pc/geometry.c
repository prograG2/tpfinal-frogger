/**
 * @file 	geometry.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo geometry. Look-up tables con medidas, funciones
 * 			orientadas a temas geométricos dentro del juego en PC.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Filas para troncos
 *
 */
const unsigned int lanes_logs[LANES_LOG_TOTAL] = {2, 4, 5};

/**
 * @brief Filas para tortugas
 *
 */
const unsigned int lanes_turtles[LANES_TURTLE_TOTAL] = {3, 6};

/**
 * @brief Filas para autos
 *
 */
const unsigned int lanes_cars[LANES_CAR_TOTAL] = {8, 9, 10, 11, 12};

/**
 * @brief Columnas para puntos de llegada
 *
 */
const unsigned int goal_cols[MAX_GOALS] = {1, 4, 7, 10, 13};

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// coordenadas topleft de cada frame del sprite de la rana
static const pair_xy_t pair_xy_frog_sprites_frames[FROG_FRAMES] =
	{
		{16, 16},
		{79, 15},
		{16, 79},
		{65, 79},
		{14, 141},
		{76, 141},
		{16, 204},
		{79, 190}};

// coordenadas topleft de cada frame del sprite de la tortuga
static const pair_xy_t pair_xy_turtle_sprites_frames[TURTLE_FRAMES] =
	{
		{2, 0},
		{51, 0},
		{99, 0},
		{146, 0},
		{194, 0},
		{243, 0},
		{290, 0},
		{337, 0},
		{382, 0},
		{445, 0},
		{496, 0}};

// coordenadas topleft de cada frame del sprite del auto
static const pair_xy_t pair_xy_car_sprites_frames[CAR_TYPE_N] =
	{
		{0, 1},	  // azul
		{77, 1},  // policia
		{155, 1}, // amarillo
		{0, 56},  // fire truck
		{0, 112}  // truck
};

// idem para sprite de coin
static const pair_xy_t pair_xy_coin_sprites_frames[SPRITE_COIN_FRAMES] =
	{
		{0, 0},
		{25, 0},
		{51, 0},
		{76, 0},
		{104, 0},
		{131, 0}};

// idem para sprite de splash
static const pair_xy_t pair_xy_splash_sprites_frames[SPRITE_SPLASH_FRAMES] =
	{
		{0, 0},
		{105, 0},
		{206, 0},
		{0, 86},
		{103, 86},
		{206, 86}};

/*******************************************************************************
 *******************************************************************************
            GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int get_rand_between(int low, int high)
{
	return (rand() % ((high + 1) - low) + low);
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
	return ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1;
}

bool collideShort(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	return (collide(ax, ay, ax + aw, ay + ah, bx, by, bx + bw, by + bh));
}

bool inside(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
	return bx1 > ax1 && by1 > ay1 && bx2 < ax2 && by2 < ay2;
}

bool insideShort(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	return (inside(ax, ay, ax + aw, ay + ah, bx, by, bx + bw, by + bh));
}

bool insideShortScaled(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh, float scale)
{
	if (scale < 0.0 || scale > 1.0)
		return false;

	float diff = (bw * (1.0 - scale));

	return (inside(ax, ay, ax + aw, ay + ah, bx + diff, by, bx + bw - diff, by + bh));
}

int mapInt(int source, int min_in, int max_in, int min_out, int max_out)
{
	// int slope = (max_out - max_in) / (min_out - min_in);

	// int output = min_out + (slope * (source - min_in));

	int output = (source - min_in) * (max_out - min_out) / (max_in - min_in) + min_out;

	return (output);
}

pair_xy_t getXYFromFrogFrame(int frame)
{
	return (pair_xy_frog_sprites_frames[frame]);
}

pair_xy_t getXYFromTurtleFrame(int frame)
{
	return (pair_xy_turtle_sprites_frames[frame]);
}

pair_xy_t getXYFromCarFrame(int frame)
{
	return (pair_xy_car_sprites_frames[frame]);
}

pair_xy_t getXYFromCoinFrame(int frame)
{
	return (pair_xy_coin_sprites_frames[frame]);
}

pair_xy_t getXYFromSplashFrame(int frame)
{
	return (pair_xy_splash_sprites_frames[frame]);
}