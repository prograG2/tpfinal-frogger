/**
 * @file 	main.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Archivo principal.
 * 			Inicia y pone a correr la maquian de estados (fsm).
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsm.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 *******************************************************************************
                                    MAIN
 *******************************************************************************
 ******************************************************************************/

int main(void)
{
	event_t evento;

	if (!inicializarFsm())
		return 1;

	while ((evento = queueSiguienteEvento()))
	{
		if (evento != NADA)
		{
			fsm(evento);
		}

		fixHighCpuUsage();
	}

	destruirQueue();

	printf("\nGracias por jugar <3\n");

	return 0;
}