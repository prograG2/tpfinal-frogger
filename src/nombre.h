/**
 * @file 	nombre.h
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Header del modulo genérico nombre.
 * 			Prototipos de funciones de relacionadas al ingreso del nombre
 * 			del jugador.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

#ifndef _NOMBRE_H_
#define _NOMBRE_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Se ejecuta una vez al ingresar a poner un nuevo nombre.
 *
 */
void nuevoNombre(void);

/**
 * @brief Selecciona la siguiente letra superior
 *
 */
void subirLetra(void);

/**
 * @brief Selecciona la letra inferior
 *
 */
void bajarLetra(void);

/**
 * @brief Confirma la letra y pasa a seleccionar la siguiente
 *
 */
void siguienteLetra(void);

/**
 * @brief Confirma la letra
 *
 */
void agregarLetra(void);

/**
 * @brief
 *
 */
void subirNombre(void);

/**
 * @brief Devuelve puntero al nombre
 *
 * @return char* Puntero al nombre
 */
char *devolverNombre(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _NOMBRE_H_
