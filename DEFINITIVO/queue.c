/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

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

void queue_insert(event_t nuevo)
{
    node_t *temp = (node_t*)malloc(sizeof(node_t));

    temp->data = nuevo;

    if (front ==  NULL)
    {
      front = back = temp;
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
    return -1;
  }
  else{
    event_t r;
    if(back == NULL) r = front->data;
    else r = back->data;
    delete();
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
    event_t valor = front->data;
    node_t *temp = front;
    front = front->next;
    free(temp);
    return valor;
  }
  else return -1;
}

 