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

int main (void)
{
	//Limpio pantalla
	clrscr();

	//Variable de eventos
    event_t evento;

	//Inicializo la FSM con el estado inicial
	p2CurrentState = fsm_getInitState();

	//Adquiero eventos y corro la FSM
	while((evento = getEvent()))
	{
		p2CurrentState = fsm(p2CurrentState, evento);
	}

	return 0;
}

