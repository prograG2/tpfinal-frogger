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

//gcc main.c -o main -Wall $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs --cflags) && ./main

#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define TRUE 1
#define FALSE 0
#define FPS 60
#define NO_FLAGS 0

#define ROWS    9
#define COLS    9
#define CELL_H  60
#define CELL_W  60
#define STEP_FULL_SIZE  60
#define STEP_RATIO      15
#define STEP_FRACTION_SIZE  (STEP_FULL_SIZE / STEP_RATIO)
#define SPRITE_SIZE_FROG_STATIC_H   30
#define SPRITE_SIZE_FROG_STATIC_W   30
#define SPRITE_SIZE_FROG_DYNAMIC_LONG  45
#define SPRITE_SIZE_FROG_DYNAMIC_SHORT  30

//Coordenadas de la celda topleft (en su vértice topleft)
#define CELL_TOPLEFT_X  10 
#define CELL_TOPLEFT_Y  18

//Coordenadas de inicio
#define CELL_START_X    (CELL_TOPLEFT_X + CELL_W * (COLS / 2 ))
#define CELL_START_Y    (CELL_TOPLEFT_Y + CELL_H * (ROWS - 1))

//Bordes para la rana en el mapa
#define FROG_MAX_X  (CELL_TOPLEFT_X + CELL_W * (COLS - 1))
#define FROG_MAX_Y  (CELL_TOPLEFT_Y + CELL_H * (ROWS - 1))
#define FROG_MIN_X  CELL_TOPLEFT_X
#define FROG_MIN_Y  CELL_TOPLEFT_Y

#define FROG_W  30
#define FROG_H  30

#define KEY_PRESSED         2
#define KEY_JUST_PRESSED    1
#define KEY_RELEASED        0

#define MAX_LIVES   3

#define MAX_CARS    10


#define MAX_LOGS    3
#define LOG_W   (3 * CELL_W)
#define LOG_H   45


enum DIRECTIONS {UP, RIGHT, LEFT, DOWN};
enum SURFACES   {CHILL, ROADWAY, WATER, TURTLE, LOG};


unsigned char key[ALLEGRO_KEY_MAX];


typedef struct 
{
    ALLEGRO_BITMAP* _frogsheet;

    ALLEGRO_BITMAP* frog[8];

    ALLEGRO_BITMAP* background_game;

    ALLEGRO_BITMAP* log;


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
} sprite_t;
sprite_t sprites;

typedef struct
{
    int x;
    int y;
    int moving;
    int facing;
    int steps;
    unsigned char surface;
    int lives;

} frog_t;
frog_t frog;

typedef struct
{
    int x;
    int y;
    int dx;
    bool on_screen;

} car_t;
car_t cars[MAX_CARS];

typedef struct
{
    int x;
    int y;
    int dx;
    bool on_screen;

} log_t;
log_t logs[MAX_LOGS];





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


/**
 * @brief Inicializa variable de tecla
 * 
 */
void keyboard_init(void);

/**
 * @brief Registra cambios en las teclas
 * 
 * @param event Evento que ocurre
 */
void keyboard_update(ALLEGRO_EVENT* event);

/**
 * @brief Inicializa la rana
 * 
 */
void frog_init(void);

/**
 * @brief Actualiza posicionamiento de la rana
 * 
 */
void frog_update(void);

/**
 * @brief Dibuja la rana
 * 
 */
void frog_draw(void);

void logs_init(void);
void logs_update(void);
void logs_draw(void);
bool logs_collide(int i, int x, int y, int w, int h);

/**
 * @brief Devuelve un randon entre dos numeros dados
 * 
 * @param low Valor inferior
 * @param high Valor superior
 * @return int Valor random
 */
int get_rand_between(int low, int high);

/**
 * @brief Comprueba colición de hitboxes rectangulares
 * 
 * @param ax1 topleft corner de a (x)
 * @param ay1 topleft corner de a (y)
 * @param ax2 bottomright corner de a (x)
 * @param ay2 bottomright corner de a (y)
 * @param bx1 topleft corner de b (x)
 * @param by1 topleft corner de b (y)
 * @param bx2 bottomright corner de b (x)
 * @param by2 bottomright corner de b (y)
 * @return true Colisión
 * @return false No colisión
 */
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);




int main(void)
{
    srand(getpid());

    //init allegro
    must_init(al_init(), "allegro");
    //init teclado
    must_init(al_install_keyboard(), "keyboard");
    //init mouse
    must_init(al_install_mouse(), "mouse");
    //init image
    must_init(al_init_image_addon(), "image");

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

    
    //Inicializa los spritesheets.
    sprites_init();

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
    
    keyboard_init();
    frog_init();
    logs_init();

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

                frog_update();
                logs_update();

                //si es 'escape', avisa para cerrar la ventana
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                //avisa que hay que renderizar
                redraw = true;
                break;

            //se apreto la "x" de la ventana
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				//para terminar el programa
				done = true;
				break;

            default:
                break;
        }

        //actualiza teclado
        keyboard_update(&event);

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

            //al_draw_bitmap(sprites.frog[0], CELL_TOPLEFT_X, CELL_TOPLEFT_Y, NO_FLAGS);
            al_draw_filled_rectangle(CELL_TOPLEFT_X + 20, CELL_TOPLEFT_Y +20, CELL_TOPLEFT_X+40, CELL_TOPLEFT_Y+40, al_map_rgb(255, 0, 0));

            
            logs_draw();
            frog_draw();

			//escribe text con fuente "font", color, desde las coordenadas (0,0)
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %d Y: %d", frog.x, frog.y);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "X: %d Y: %d", logs[0].x, logs[0].y);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 30, 0, "X: %d Y: %d", logs[1].x, logs[1].y);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 40, 0, "X: %d Y: %d", logs[2].x, logs[2].y);
			//dibuja un rectángulo relleno de 10x10, color rojo
			al_draw_filled_rectangle(frog.x+25, frog.y+25, frog.x + 35, frog.y + 35, al_map_rgb(255, 0, 0));

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

    sprites.log = al_load_bitmap("log_spritesheet.png");
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

    al_destroy_bitmap(sprites.log);
    
}

void keyboard_init(void)
{
    memset(key, 0, ALLEGRO_KEY_MAX);
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch(event->type)
    {
        case ALLEGRO_EVENT_KEY_DOWN:
            if(key[event->keyboard.keycode] == KEY_JUST_PRESSED)
                key[event->keyboard.keycode] = KEY_PRESSED;
            
            if(key[event->keyboard.keycode] == KEY_RELEASED)
                key[event->keyboard.keycode] = KEY_JUST_PRESSED;

            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] = KEY_RELEASED;

            break;

        default:
            break;
    }
}

void frog_init(void)
{
    frog.x = CELL_START_X;
    frog.y = CELL_START_Y;
    frog.moving = false;
    frog.facing = UP;
    frog.steps = 0;
    frog.surface = CHILL;
    frog.lives = MAX_LIVES;
}

void frog_update(void)
{
    if(!frog.moving)
    {
        if(key[ALLEGRO_KEY_LEFT] == KEY_JUST_PRESSED)
        {

            frog.facing = LEFT;
            frog.moving = true;
            key[ALLEGRO_KEY_LEFT] = KEY_PRESSED;
        }     
        if(key[ALLEGRO_KEY_RIGHT] == KEY_JUST_PRESSED)
        {
            frog.facing = RIGHT;
            frog.moving = true;
            key[ALLEGRO_KEY_RIGHT] = KEY_PRESSED;
        }     
        if(key[ALLEGRO_KEY_UP] == KEY_JUST_PRESSED)
        {
            frog.facing = UP;
            frog.moving = true;
            key[ALLEGRO_KEY_UP] = KEY_PRESSED;
        }  
        if(key[ALLEGRO_KEY_DOWN] == KEY_JUST_PRESSED)
        {
            frog.facing = DOWN;
            frog.moving = true;
            key[ALLEGRO_KEY_DOWN] = KEY_PRESSED;
        }
    }

    else if (frog.moving)
    {
    
        if(frog.facing == LEFT)
            frog.x -= STEP_FRACTION_SIZE;
        if(frog.facing == RIGHT)
            frog.x += STEP_FRACTION_SIZE;
        if(frog.facing == UP)
            frog.y -= STEP_FRACTION_SIZE;
        if(frog.facing == DOWN)
            frog.y += STEP_FRACTION_SIZE;

        if(frog.x < FROG_MIN_X)
            frog.x = FROG_MIN_X;
        if(frog.x > FROG_MAX_X)
            frog.x = FROG_MAX_X;
        if(frog.y < FROG_MIN_Y)
            frog.y = FROG_MIN_Y;
        if(frog.y > FROG_MAX_Y)
            frog.y = FROG_MAX_Y;

        if(++frog.steps == STEP_RATIO)
        {
            frog.steps = 0;
            frog.moving = false;
        }
    }

    //if colision, y otros.

    int i;
    for(i = 0; i < MAX_LOGS; i++)
    {
        if(!logs[i].on_screen)
            continue;
        
        if(logs_collide(i, frog.x, frog.y, frog.x + FROG_W, frog.y + FROG_H))
        {
            //printf("COLLIDE CON %d", i);
            frog.x += logs[i].dx;
            break;
        }
    }

}

void frog_draw(void)
{

    int center_x, center_y;
    ALLEGRO_BITMAP* tempbitmap;

    if(frog.moving)
    {
        if(frog.facing == UP)
            tempbitmap = sprites.frog[1];
        if(frog.facing == DOWN)
            tempbitmap = sprites.frog[7];
        if(frog.facing == RIGHT)
            tempbitmap = sprites.frog[3];
        if(frog.facing == LEFT)
            tempbitmap = sprites.frog[5];

    }

    else if(!frog.moving)
    {
        if(frog.facing == UP)
            tempbitmap = sprites.frog[0];
        if(frog.facing == DOWN)
            tempbitmap = sprites.frog[6];
        if(frog.facing == RIGHT)
            tempbitmap = sprites.frog[2];
        if(frog.facing == LEFT)
            tempbitmap = sprites.frog[4];

    }

    center_x = frog.x + CELL_W / 2 - FROG_W/2;
    center_y = frog.y + CELL_H / 2 - FROG_H/2;

    al_draw_bitmap(tempbitmap, center_x, center_y, NO_FLAGS);

}

void logs_init(void)
{
    int i;

    for(i = 0; i < MAX_LOGS; i++)
    {
        logs[i].y = CELL_TOPLEFT_Y + 2 * CELL_H;
        logs[i].dx = 2;
        logs[i].on_screen = false;
    }

}

void logs_update(void)
{
    int i;
    int random_val = get_rand_between(1, 3);

    for(i = 0; i < MAX_LOGS; i++)
    {
        if(!logs[i].on_screen)
        {   
            if(i > 0)
            {
                if(logs[i-1].x >= random_val * CELL_W )
                {
                    logs[i].x = (-1)*LOG_W ;
                    logs[i].on_screen = true;
                }
            }

            if(i == 0)
            {
                if(!logs[MAX_LOGS-1].on_screen || (logs[MAX_LOGS-1].x >= random_val * CELL_W ))
                {
                    logs[i].x = (-1)*LOG_W ;
                    logs[i].on_screen = true;
                }
            }
            
        }

        if(logs[i].on_screen)
        {
            logs[i].x += logs[i].dx;

            if(logs[i].x >= al_get_bitmap_width(sprites.background_game))
                logs[i].on_screen = false;
        }
        
    }
}

void logs_draw(void)
{
    int i, center_y;

    for(i = 0; i < MAX_LOGS; i++)
    {
        if(logs[i].on_screen)
        {
            center_y = logs[i].y + CELL_H / 2 - LOG_H / 2;
            al_draw_bitmap(sprites.log, logs[i].x, center_y, NO_FLAGS);
        }
            
    }
}

bool logs_collide(int i, int x, int y, int w, int h)
{
    return collide(x, y, x + w, y + h, logs[i].x, logs[i].y, logs[i].x + LOG_W, logs[i].y + LOG_H);
}

int get_rand_between(int low, int high)
{
    return ((rand() % (high - low + 1)) + low) ;
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}