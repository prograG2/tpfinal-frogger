/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "queue.h"

#include <stdlib.h>
#include <stdio.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct nodeT
{
    event_t data;
    struct nodeT *next;
}node_t;



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 */
static void delete();


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static node_t *front = NULL, *back = NULL;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int queue_init(){
  return 1;
}


void queue_insert(event_t nuevo)
{
    node_t *temp = (node_t*)malloc(sizeof(node_t));

    temp->data = nuevo;
    //printf("%d\n", nuevo); //si se quita esto la queue funciona mal

    if (front ==  NULL)
    {
      front = temp;
      front->next = NULL;
    }
    else if(back == NULL){
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


int queue_empty()
{
  return front == NULL;
}

event_t queue_next()
{
  if (front == NULL){
    return NADA;
  }
  else{
    event_t r = front->data;
    delete();
    printf("\n%d\n", r); //para ver el evento que sigue
    return r;
  }
}
 



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delete()
{
  if(front != NULL){
    node_t *temp = front;
    front = front->next;
    free(temp);
    if(front == NULL){
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

 
