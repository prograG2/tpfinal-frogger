/**
 * @file 	queue.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * 			
 * @brief 	Source del modulo queue.
 * 			Funciones para el manejo de la cola de eventos.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"

#include <stdlib.h>
#include <stdio.h>


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

//Estructura de la queue
typedef struct nodeT
{
	event_t data;
	struct nodeT *next;
} node_t;


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Borra un elemento de la cola
 *
 */
static void borrarElemento(void);


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static node_t *front = NULL, *back = NULL;

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void queueInsertar(event_t nuevo)
{
	node_t *temp = (node_t *)malloc(sizeof(node_t));

	temp->data = nuevo;

	if (front == NULL)
	{
		front = temp;
		front->next = NULL;
	}
	else if (back == NULL)
	{
		back = temp;
		front->next = back;
		back->next = NULL;
	}
	else
	{
		back->next = temp;
		back = back->next;
	}
}

bool queueVacia(void)
{
	return front == NULL;
}

event_t queueSiguienteEvento(void)
{
	if (front == NULL)
	{
		return NADA;
	}
	else
	{
		event_t r = front->data;
		borrarElemento();
		return r;
	}
}

void destruirQueue(void)
{
	while (front != NULL)
	{
		queueSiguienteEvento();
	}
}

/*******************************************************************************
 *******************************************************************************
						LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void borrarElemento(void)
{
	if (front != NULL)
	{
		node_t *temp = front;
		front = front->next;
		free(temp);
		if (front == NULL)
		{
			back = NULL;
		}
	}
}

/*
static void printQueue(){
  node_t *temp = front;
  while(temp != back){
	printf("%d, ", temp->data);
	temp = temp->next;
  }
}
*/
