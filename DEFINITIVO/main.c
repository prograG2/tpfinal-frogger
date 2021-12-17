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

event_t getEvent();
extern STATE* p2CurrentState;

int main (void)
{
    event_t evento;
	p2CurrentState = fsm_getInitState(); //al inicializarse la fsm, se inicializa todo lo demás

	while(evento = getEvent())
		p2CurrentState = fsm(p2CurrentState, evento);

	return 0;
}
#if PLATAFORMA == PC
event_t getEvent(){
	ALLEGRO_EVENT ret_event;
	while(queue_empty()){
		if(al_get_next_event(al_queue, &ret_event))
			switch(ret_event.keyboard.keycode){
				case ALLEGRO_KEY_UP: return ARRIBA;
				case ALLEGRO_KEY_DOWN: return ABAJO;
				case ALLEGRO_KEY_LEFT: return IZDA;
				case ALLEGRO_KEY_RIGHT: return DCHA;
				case ALLEGRO_KEY_ENTER: return ENTER;
				case ALLEGRO_KEY_BACKSPACE: return BORRAR;
				case ALLEGRO_KEY_ESCAPE: return ESC;
				default:
					last_key = ret_event.keyboard.keycode;
					return last_key;
			}
	}
	return queue_next();
}
#else
event_t getEvent(){
	while(queue_empty());
	return queue_next();
}
#endif

