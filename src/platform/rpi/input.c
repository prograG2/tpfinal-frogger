/**
 * @file input.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../input.h"

#include "joydrv.h"

#include <stdint.h>


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

/**
 * @brief devuelve el módulo para una variable entera de 8 bits
 * 
 * @param x variable a obtener el módulo
 * @return int8_t |x|, con la excepción modulo(-128) = 127
 */
static int8_t modulo(int8_t x);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static int prev = NO_MOVER;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void iniciarEntradas()
{
    joy_init();
}

event_t leerEntradas()
{
    joy_update();
    int act = joy_get_switch();
    if(act == J_PRESS){
        if(prev != J_PRESS){
            prev = J_PRESS;
            return ENTER;
        }
        return NO_MOVER;
    }

    jcoord_t crd = joy_get_coord();

    int umbral;

    if(prev == NO_MOVER)
        umbral = 20;
    else
        umbral = 10;    

    if((crd.y-umbral) > modulo(crd.x)) act = ARRIBA;
    else if((crd.y+umbral) < -(modulo(crd.x))) act = ABAJO;
    else if((crd.x-umbral) > modulo(crd.y)) act = DCHA;
    else if((crd.x+umbral) < -(modulo(crd.y))) act = IZDA;
    else act = NO_MOVER;


    if(act != prev){
        prev = act;
        return act;
    }
  
    return NO_MOVER;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int8_t modulo(int8_t x)
{
    if (x==-128) return 127; //excepción: caso en el cual -(-128) = -128
    
	return x >= 0 ? x : -x;
}


 