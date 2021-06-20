#include <stdio.h>

#include "global.h"
#include "fsm.h"	    /*FSM engine (interprete)*/
#include "fsmtable.h"   /*FSM Table*/


STATE *p2state=NULL;	/*Used to store FSM state*/

celda_t mapa[ALTO][ANCHO];

int main (void)
{

    int evento;
	clrscr();	
	
	p2state=FSM_GetInitState();// Inicializo la FSM con el estado inicial

	while((evento = getch()))  //Si hay evento
		p2state=fsm(p2state,evento);      //Se lo paso a la maquina de estados  	
}

