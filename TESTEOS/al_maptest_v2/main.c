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
 
    /*
    while(1)
    {
        printf("%d~", lanes_logs[get_rand_between(0, LANES_LOG_TOTAL-1)]);
        for(int i = 0; i < 10000000; i++);
    }
    */
    
    allegro_inits();
    entities_init();

    printf("\nfont height %d ~~ font width %d\n", allegro_get_var_font_h(), allegro_get_var_font_w());

    while(1)    
    {
        event = allegro_wait_for_event();
        
        switch(event)
        {
            case ALLEGRO_EVENT_TIMER:
                
                entities_update();
                
                //si es 'escape', avisa para cerrar la ventana
                if(keyboard_check_key(ALLEGRO_KEY_ESCAPE))
                    allegro_set_var_done(true);
                
                //play~pausa de musica de fondo
                if(keyboard_check_key(ALLEGRO_KEY_P))
                    allegro_sound_toggle_background_status();

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
            printf("\n~~cerrado~~\n\n");

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

            //entidades
            entities_draw();

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


