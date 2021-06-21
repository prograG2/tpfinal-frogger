#include <stdlib.h>

#include "global.h"
#include "fsm.h"
#include "lista_dinamica.h"

STATE *p2state=NULL;	/*Used to store FSM state*/

celda_t mapa[ALTO][ANCHO];
Array buffer_estados;


int main (void)
{
	clrscr();

	initArray(&buffer_estados, 0);
    char evento;
	p2state=FSM_GetInitState();// Inicializo la FSM con el estado inicial

	while(evento = getEvento()){
		p2state = fsm(p2state, evento);
	}

	return 0;
}

