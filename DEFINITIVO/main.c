/**
 * @file main.c
 * @author 
 * @brief Archivo principal del proyecto. Inicializa threads y la FSM.
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>

#include "global.h"
#include "fsm.h"
#include "queue.h"
#include "termlib.h"

STATE* p2CurrentState = NULL;
unsigned char getEvent();

int main (void)
{
	//Limpio pantalla
	clrscr();

	//Variable de eventos
    event_t evento;

	//Inicializo la FSM con el estado inicial
	p2CurrentState = fsm_getInitState();

	if(queue_init() || game_data_setDificultad_easy())
		return 1;

	//Adquiero eventos y corro la FSM
	while((evento = getEvent()))
	{
		p2CurrentState = fsm(p2CurrentState, evento);
	}

	return 0;
}

unsigned char getEvent(){
	while(queue_empty());
	return queue_next();
}