#ifndef THREADS_PC
#define THREADS_PC

#include <pthread.h>
#include <time.h>
#include <stdio.h>

#include "global.h"
#include "queue.h"
#include "display_pc.h"
#include "menu_pc.h"
#include "game_pc.h"
#include "fsm.h"

pthread_t tdisplaymenu, tdisplayjuego, tdisplayranking, tautos, ttiempo;
extern STATE* p2CurrentState;

void *thread_display_menu();

void *thread_display_nombre();

void *thread_display_juego();

void *thread_display_ranking();

void *thread_tiempo();

void *thread_autos();

#endif