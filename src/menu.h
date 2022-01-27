/**
 * @file menu.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _MENU_H_
#define _MENU_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 */
void iniciarMenu(void);

/**
 * @brief 
 * 
 */
void destruirMenu(void);

/**
 * @brief Set the Menu object
 * 
 * @param a 
 * @param size 
 */
void setMenu(int* a, unsigned int size);

/**
 * @brief Set the Opcion object
 * 
 * @param opc 
 */
void setOpcion(int opc);

/**
 * @brief Get the Opcion object
 * 
 * @return int 
 */
int getOpcion(void);

/**
 * @brief 
 * 
 */
void subirOpcion(void);

/**
 * @brief 
 * 
 */
void bajarOpcion(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _MENU_H_
