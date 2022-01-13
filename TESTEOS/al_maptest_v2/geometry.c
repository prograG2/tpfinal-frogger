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

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


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

bool inside(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if( bx1 > ax1   &&
        by1 > ay1   &&
        bx2 < ax2   &&
        by2 < ay2)

        return true;

    return false;
}

int map_int(int source, int min_in, int max_in, int min_out, int max_out)
{
    //int slope = (max_out - max_in) / (min_out - min_in);

    //int output = min_out + (slope * (source - min_in));

    int output = (source - min_in) * (max_out - min_out) / (max_in - min_in) + min_out;

    return(output);
}   


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 