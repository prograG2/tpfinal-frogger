/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-22
 * 
 * @copyright Clopyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define TRUE 1
#define FALSE 0
#define FPS 60
#define PLAYER_COL 2
#define PLAYER_ROW 4
#define NO_FLAGS 0

#define MOV_RATIO 5

#define ROWS    9
#define COLS    9
#define CELL_H  60
#define CELL_W  60
#define STEP_FULL_SIZE  60
#define STEP_RATIO      10
#define STEP_FRACTION_SIZE  (STEP_FULL_SIZE / STEP_RATIO)
#define SPRITE_SIZE_FROG_STATIC_H   30
#define SPRITE_SIZE_FROG_STATIC_W   30
#define SPRITE_SIZE_FROG_DYNAMIC_LONG  45
#define SPRITE_SIZE_FROG_DYNAMIC_SHORT  30

//Coordenadas de la celda topleft (en su vértice topleft)
#define CELL_TOPLEFT_X  40
#define CELL_TOPLEFT_Y  48


typedef struct SPRITES
{
    ALLEGRO_BITMAP* _frogsheet;

    ALLEGRO_BITMAP* frog[8];

    ALLEGRO_BITMAP* background_game;


    /*
    ALLEGRO_BITMAP* ship;
    ALLEGRO_BITMAP* ship_shot[2];
    ALLEGRO_BITMAP* life;

    ALLEGRO_BITMAP* alien[3];
    ALLEGRO_BITMAP* alien_shot;

    ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
    ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

    ALLEGRO_BITMAP* powerup[4];
    */
} SPRITES;
SPRITES sprites;


/**
 * @brief Inicializa "cosas" de Allegro, y sale del programa si hay problemas, avisando dónde estuvo.
 * 
 * @param test Handler//booleano con status de la inicialización.
 * @param description String con la descripción/nombre de la "cosa" a inicializar.
 */
void must_init(bool test, const char *description);

/**
 * @brief Copia parte de un spritesheet y lo devuelve como un nuevo bitmap
 * 
 * @param x top left 'x' coord
 * @param y top left 'y' coord
 * @param w wide
 * @param h heigth
 * @return ALLEGRO_BITMAP* 
 */
ALLEGRO_BITMAP* sprite_cut(int x, int y, int w, int h);

/**
 * @brief Inicializa los sprites a usar
 * 
 */
void sprites_init(void);

/**
 * @brief Destruye los sprites a usar
 * 
 */
void sprites_deinit(void);



int main(void)
{
    //init allegro
    must_init(al_init(), "allegro");
    //init teclado
    must_init(al_install_keyboard(), "keyboard");
    //init mouse
    must_init(al_install_mouse(), "mouse");

    //timer que actualiza cada 1/30 segundos ("30fps")
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	must_init(timer, "timer");

    //cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	//opciones para el display (antialiasing)
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    al_init_image_addon ();
    //Inicializa los spritesheets.
    sprites_init();
    //ALLEGRO_BITMAP *background = al_load_bitmap ("frogger_background.png");
    //ALLEGRO_BITMAP *player = al_load_bitmap ("frog_spritesheet.png");

    double player_width = al_get_bitmap_width (sprites.background_game) / PLAYER_COL, player_height = al_get_bitmap_height (sprites.background_game) / PLAYER_ROW;
    

    uint16_t display_W = al_get_bitmap_width(sprites.background_game), display_H = al_get_bitmap_height(sprites.background_game);
	ALLEGRO_DISPLAY* disp = al_create_display(display_W, display_H);
    must_init(disp, "display");
    al_set_window_position (disp, 200, 200);
    al_set_new_window_title ("Frogger");
	

	//para usar la fuente builtin
	ALLEGRO_FONT* font = al_create_builtin_font();
	must_init(font, "font");

	//para dibujar figuras primitivas (círculos, rectángulos, líneas, rellenos o no, etc.)
	must_init(al_init_primitives_addon(), "primitives");


	//registra eventos posibles
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());  

	bool done = false;		//flag para salir el programa
	bool redraw = true;		//flag para renderizar
	ALLEGRO_EVENT event;	//variable evento

    char active = FALSE, move = false;
    enum directions {UP, RIGHT, LEFT, DOWN};
    double x = CELL_TOPLEFT_X, y = CELL_TOPLEFT_Y;
    int mov_big_step = 30, mov_small_step = mov_big_step/MOV_RATIO, direction = DOWN, source_x = 0, source_y = 0, player_speed;
    int count_steps = 0;

    //coordenadas globales
	//float x, y, curX, curY;

    


    //inicializa timer
    al_start_timer(timer);

    /*---------------------------------------------------------------------------*/

    while(1)
    {
        //espera bloqueante, hasta que llega evento
        al_wait_for_event(queue, &event);

        /*---------------------------------------------------------------------------*/

        //se analiza el evento
        switch(event.type)
        {

            case ALLEGRO_EVENT_TIMER:

                if(active)
                {
                    switch (direction)
                    {
                        case UP:
                            y -= STEP_FRACTION_SIZE;
                            break;

                        case DOWN:
                            y += STEP_FRACTION_SIZE;
                            break;

                        case RIGHT:
                            x += STEP_FRACTION_SIZE;
                            break;

                        case LEFT:
                            x -= STEP_FRACTION_SIZE;
                            break;
                        
                        default:
                            break;
                    }
                    
                    source_x = player_width;

                    if(++count_steps == STEP_RATIO)
                    {
                        active = false;
                        count_steps = 0;
                    }
                }
                else
                {
                    source_x = 0;
                }

                source_y = direction;

                //avisa que hay que renderizar
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                {
                    int keypressed = event.keyboard.keycode;
                }

  
                if(event.keyboard.keycode == ALLEGRO_KEY_UP)
				{
                    if(!active)
                    {
                        direction = UP;
                        active = true;
                    }
                    
                }
				else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
                    if(!active)
                    {
                        direction = DOWN;
                        active = true;
                    }
                }	
				else if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
				{
                    if(!active)
                    {
                        direction = LEFT;
                        active = true;
                    }
                }
				else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				{
                    if(!active)
                    {
                        direction = RIGHT;
                        active = true;
                    }
                }   

                //si NO es escape, sale del switch
				if(event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                {
                    
					break;
                } 
                //si SÍ es escape, activa flag para terminar el programa, y sale del switch
                else
                {
                    done = true;
                    break;
                }  

            case ALLEGRO_EVENT_MOUSE_AXES:
                //x = event.mouse.x;      //copia coordenadas del mouse a variables del programa
                //y = event.mouse.y;
                break;

            //se apreto la "x" de la ventana
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				//para terminar el programa
				done = true;
				break;

            default:
                break;
        }

        /*---------------------------------------------------------------------------*/

        //si hay que cerrar el programa
		if(done)
		{
			printf("\ncerrado\n");
			break;  //sale del while
		}

        //si se pide renderizar, y la cola de eventos esta vacía, se renderiza
		if(redraw && al_is_event_queue_empty(queue))
		{
			//pone todo en negro
			al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap(sprites.background_game, 0, 0, 0);

            //al_draw_bitmap_region (player, source_x, source_y * player_height, player_width, player_height, x, y, NO_FLAGS);
            //al_draw_tinted_scaled_rotated_bitmap_region(player, source_x, source_y * player_height, player_width, player_height, al_map_rgb(255, 255, 255), (source_x + player_width)/2, (source_y * player_height + player_height)/2, x, y, 0.5, 0.5, 0, NO_FLAGS);
            
            int center_x = x - (al_get_bitmap_width(sprites.frog[0]) / 2);
            int center_y = y - (al_get_bitmap_height(sprites.frog[0]) / 2);


            ALLEGRO_BITMAP* tempbitmap;
            if(active)
            {
                switch(direction)
                {
                    case UP:
                        tempbitmap = sprites.frog[1];
                        break;

                    case DOWN:
                        tempbitmap = sprites.frog[7];
                        break;

                    case RIGHT:
                        tempbitmap = sprites.frog[3];
                        break;

                    case LEFT:
                        tempbitmap = sprites.frog[5];

                    default:
                        break;


                }
            }

            else
            {
               switch(direction)
                {
                    case UP:
                        tempbitmap = sprites.frog[0];
                        break;

                    case DOWN:
                        tempbitmap = sprites.frog[6];
                        break;

                    case RIGHT:
                        tempbitmap = sprites.frog[2];
                        break;

                    case LEFT:
                        tempbitmap = sprites.frog[4];

                    default:
                        break;


                } 
            }
            al_draw_bitmap(tempbitmap, center_x, center_y, NO_FLAGS);

			//escribe text con fuente "font", color, desde las coordenadas (0,0)
			//al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
			//dibuja un rectángulo relleno de 10x10, color rojo
			al_draw_filled_rectangle(x-5, y-5, x + 5, y+  5, al_map_rgb(255, 0, 0));
            
            

			//carga los cambios anteriores para verlos
            /*sin este comando, todo lo anterior NO se visualiza en pantalla*/
			al_flip_display();

			//avisa que ya se renderizó
			redraw = false;
		}

    }

    //se destruyen las cosas creadas
    sprites_deinit();
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}



void must_init(bool test, const char *description)
{
	if(test) return;

	printf("~no se pudo inicializar %s~\n", description);
	exit(1);
}

ALLEGRO_BITMAP* sprite_cut(int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._frogsheet, x, y, w, h);
    must_init(sprite, "sprite cut");
    return sprite;
}

void sprites_init(void)
{
    sprites._frogsheet = al_load_bitmap("frog_spritesheet.png");

    sprites.frog[0] = sprite_cut(16, 16, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
    sprites.frog[1] = sprite_cut(79, 16, SPRITE_SIZE_FROG_DYNAMIC_SHORT, SPRITE_SIZE_FROG_DYNAMIC_LONG);
    sprites.frog[2] = sprite_cut(16, 79, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
    sprites.frog[3] = sprite_cut(66, 79, SPRITE_SIZE_FROG_DYNAMIC_LONG, SPRITE_SIZE_FROG_DYNAMIC_SHORT);
    sprites.frog[4] = sprite_cut(15, 141, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
    sprites.frog[5] = sprite_cut(77, 141, SPRITE_SIZE_FROG_DYNAMIC_LONG, SPRITE_SIZE_FROG_DYNAMIC_SHORT);
    sprites.frog[6] = sprite_cut(16, 203, SPRITE_SIZE_FROG_STATIC_W, SPRITE_SIZE_FROG_STATIC_H);
    sprites.frog[7] = sprite_cut(79, 190, SPRITE_SIZE_FROG_DYNAMIC_SHORT, SPRITE_SIZE_FROG_DYNAMIC_LONG);

    sprites.background_game = al_load_bitmap("frogger_background.png");
}

void sprites_deinit(void)
{
    int i;

    al_destroy_bitmap(sprites._frogsheet);

    for(i = 0; i < 8; i++)
    {
        al_destroy_bitmap(sprites.frog[i]);
    }

    al_destroy_bitmap(sprites.background_game);
    
}