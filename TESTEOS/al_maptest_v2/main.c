/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#include "allegro_stuff.h"
#include "entities.h"
#include "geometry.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static ALLEGRO_EVENT_TYPE event;


/*******************************************************************************
 *******************************************************************************
                                    MAIN 
 *******************************************************************************
 ******************************************************************************/

int main(void)
{
    srand(time(NULL));
    allegro_inits();
    frog_init();
    logs_init();

    while(1)    
    {
        event = allegro_wait_for_event();
        
        switch(event)
        {
            case ALLEGRO_EVENT_TIMER:
                
                frog_update();
                logs_update();
                
                //si es 'escape', avisa para cerrar la ventana
                if(keyboard_check_key(ALLEGRO_KEY_ESCAPE))
                    allegro_set_var_done(true);

                //avisa que hay que renderizar
                allegro_set_var_redraw(true);

                break;

            //se apretó la "x" de la ventana
            case ALLEGRO_EVENT_DISPLAY_CLOSE:

                allegro_set_var_done(true);
                
                break;

            default:

                break;

        }

        //si hay que cerrar el programa
        if(allegro_get_var_done())
        {
            printf("\ncerrado\n");

            //sale del while
			break;  
        }

        //actualiza teclado
        keyboard_update();

        //si se pide renderizar, y la cola de eventos esta vacía, se renderiza
        if(allegro_get_var_redraw() && allegro_is_event_queue_empty())
        {
            //pone todo en negro
			allegro_clear_display();

            //sprite de fondo
            allegro_draw_background();

            logs_draw();
            frog_draw();

            //coordenadas rana
            al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, 0, 0, "X: %d Y: %d", frog_get_x(), frog_get_y());

            //coordenadas troncos
            int i, space;
            for(i = 0, space = 20; i < MAX_LOGS; i++, space += 10)
            {
                al_draw_textf(allegro_get_var_font(), al_map_rgb(200, 50, 50), 0, space, 0, "N°:%d X:%d Y:%d", i, log_get_x(i), log_get_y(i));
            }

            //carga los cambios anteriores para verlos
			al_flip_display();

            //avisa que ya se renderizó
			allegro_set_var_redraw(false);
        
        }

    }

    //se destruyen reservas de memoria de allegro
    allegro_deinits();

    return 0;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


