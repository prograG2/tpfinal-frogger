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

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsm.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Fixea consumo elevado de cpu en el while loop principal
 * 
 */
static void fix_high_cpu_usage(void);


/*******************************************************************************
 *******************************************************************************
                        			MAIN
 *******************************************************************************
 ******************************************************************************/

int main (void)
{
    event_t evento;

	srand(time(NULL));

	if(!inicializarFsm())
		return 1;

	while((evento = queue_next()))
	{
		if(evento != NADA)
		{
			fsm(evento);
		}

		fix_high_cpu_usage();
	}

	printf("\nSaliendo...\n");

	return 0;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void fix_high_cpu_usage(void)
{
	usleep(1000);
}




