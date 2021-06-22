#include <stdlib.h>

#include "global.h"
#include "fsm.h"
#include "queue.h"

STATE *p2state=NULL;	/*Used to store FSM state*/

int main (void)
{
	clrscr();
    char evento;
	p2state=FSM_GetInitState();// Inicializo la FSM con el estado inicial

	while(evento = getEvento()){
		p2state = fsm(p2state, evento);
	}

	return 0;
}

