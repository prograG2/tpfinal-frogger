/**
 * @file geometry.c
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

#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

//filas para troncos
const unsigned int lanes_logs[LANES_LOG_TOTAL] = {2,4,5};
//filas para tortugas
const unsigned int lanes_turtles[LANES_TURTLE_TOTAL] = {3,6};
//filas para autos
const unsigned int lanes_cars[LANES_CAR_TOTAL] = {8,9,10,11,12};
//columnas para los puntos de llegada (referenciadas a 0)
const unsigned int goal_cols[MAX_GOALS] = {1,4,7,10,13};


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//coordenadas topleft de cada frame del sprite de la rana
static const pair_xy_t pair_xy_frog_sprites_frames[FROG_FRAMES] =
    {
        {16,16},
        {79,15},
        {16,79},
        {65,79},
        {14,141},
        {76,141},
        {16,204},
        {79,190}
    };

//coordenadas topleft de cada frame del sprite de la tortuga
static const pair_xy_t pair_xy_turtle_sprites_frames[TURTLE_FRAMES] =
	{
        {2,0},
        {51,0},
        {99,0},
        {146,0},
        {194,0},
        {243,0},
        {290,0},
        {337,0},
        {382,0},
        {445,0},
        {496,0}
	};

//coordenadas topleft de cada frame del sprite del auto
static const pair_xy_t pair_xy_car_sprites_frames[CAR_TYPE_N] =
	{
        {0,1},		//azul
        {77,1},		//policia
        {155,1},	//amarillo
        {0,56},		//fire truck
        {0,112}		//truck
    };


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int get_rand_between(int low, int high)
{
    return (rand()%((high+1)-low) + low);
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if (ax1 < bx2 &&
        ax2 > bx1 &&
        ay1 < by2 &&
        ay2 > by1)

        return true;

    return false;
}

bool collideShort(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	return(collide(ax, ay, ax + aw, ay + ah, bx, by, bx + bw, by + bh));
}

bool inside(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if( bx1 > ax1   &&
        by1 > ay1   &&
        bx2 < ax2   &&
        by2 < ay2)

        return true;

    return false;
}

bool insideShort(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	return(inside(ax, ay, ax + aw, ay + ah, bx, by, bx + bw, by + bh));
}

bool insideShortScaled(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh, float scale)
{
	if(scale < 0.0 || scale > 1.0)
		return false;

	float diff = (bw * (1.0 - scale));

	return(inside(ax, ay, ax + aw, ay + ah, bx + diff, by, bx + bw - diff, by + bh));
}

int mapInt(int source, int min_in, int max_in, int min_out, int max_out)
{
    //int slope = (max_out - max_in) / (min_out - min_in);

    //int output = min_out + (slope * (source - min_in));

    int output = (source - min_in) * (max_out - min_out) / (max_in - min_in) + min_out;

    return(output);
}

pair_xy_t getXYFromFrogFrame(int frame)
{
    return(pair_xy_frog_sprites_frames[frame]);
}

pair_xy_t getXYFromTurtleFrame(int frame)
{
    return(pair_xy_turtle_sprites_frames[frame]);
}

pair_xy_t getXYFromCarFrame(int frame)
{
    return(pair_xy_car_sprites_frames[frame]);
}

bool matchUint(unsigned int val, const unsigned int *array)
{
	if(array == NULL)
	{
		printf("PUNTERO INVALIDO ~ funcion: matchUint ~ val=%d", val);
		exit(EXIT_FAILURE);
	}
	
	int i;
	for(i = 0; array[i] != '\0'; i++)
	{
		if(val == array[i])
			return true;;
	}

	return false;
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



