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

#include "global.h"
#include "fsm.h"
#include "queue.h"
#include <stdio.h>

extern STATE* p2CurrentState;

int main (void)
{
    event_t evento;
	if(inicializarFsm()) //al inicializarse la fsm, se inicializa todo lo demás
		return 1;
	
	while((evento = queue_next())){
		if(evento != NADA)
			fsm(evento);
	}

	printf("%s\n", "Saliendo...");

	return 0;
}


