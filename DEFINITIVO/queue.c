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

static void delete();
static void printQueue();

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static node_t *front = NULL, *back = NULL;


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int queue_init(){
  #if PLATAFORMA == PC
  al_queue = al_create_event_queue();
  al_register_event_source(al_queue, al_get_keyboard_event_source());
  return al_queue;
  #endif
  return 1;
}


void queue_insert(event_t nuevo)
{
    node_t *temp = (node_t*)malloc(sizeof(node_t));

    temp->data = nuevo;
    printf("%d\n", nuevo);
    /*
    printf("\nAntes de poner: ");
    printQueue();
    */

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
    /*
    printf("\nTras poner: ");
    printQueue();
    */
}


int queue_empty()
{
  return front == NULL;
}

event_t queue_next()
{
  #if PLATAFORMA == PC
    ALLEGRO_EVENT ret_event;
		if(al_get_next_event(al_queue, &ret_event))
			last_key = ret_event.keyboard.keycode;
			return last_key;
	#endif

  if (front == NULL){
    return NADA;
  }
  else{
    event_t r = front->data;
    /*
    printf("Antes de retirar: ");
    printQueue();
    */
    delete();
    /*
    printf("Tras retirar: ");
    printQueue();
    */
    printf("%d\n", r);
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

static void printQueue(){
  node_t *temp = front;
  while(temp != back){
    printf("%d, ", temp->data);
    temp = temp->next;
  }
}

 