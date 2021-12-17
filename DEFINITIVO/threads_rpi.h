#ifndef THREADS_RPI
#define THREADS_RPI

#include <pthread.h>
#include "queue.h"
#include "joystick.h"
#include "display_rpi.h"
#include "global.h"
#include <time.h>
#include "menu_rpi.h"
#include "game_rpi.h"
#include "mensajes_rpi.h"
#include "fsm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

pthread_t tjoystick, tdisplaymenu, tdisplaynombre, tdisplayjuego, tdisplayranking, tjugador, tautos, ttiempo;
extern STATE* p2CurrentState;

void *thread_joystick();

void *thread_display_menu();

void *thread_display_nombre();

void *thread_display_juego();

void *thread_display_ranking();

void *thread_tiempo();

void *thread_autos();

#endif