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
#include "threads.h"

#include "display.h"
#include "joystick.h"
#include "global.h"
#include "fsm.h"
#include "queue.h"
#include "menu.h"

unsigned char getEvent();
extern STATE* p2CurrentState;

int main (void)
{
    event_t evento;
	p2CurrentState = fsm_getInitState();
	srand(time(NULL));
	iniciarDisplay();
	iniciarJoystick();
	iniciarMenu();
	setMenu((int*){JUGAR, DIFICULTAD, RANKING, SALIR}, 4);
	setOpcion(0);
	jugador.dificultad = NORMAL;

	if(queue_init())
		return 1;

	pthread_create(&tjoystick, NULL, thread_joystick, NULL);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
	while(evento = getEvent()){
		p2CurrentState = fsm(p2CurrentState, evento);
	}
	p2CurrentState = SALIR;

	pthread_join(tjoystick, NULL);

	return 0;
}

unsigned char getEvent(){
	while(queue_empty());
	return queue_next();
}

