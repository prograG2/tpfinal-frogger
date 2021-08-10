/*
gcc test01.c -o test01 $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs --cflags)
./test01

gcc test01.c -o test01 $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs --cflags) && ./test01
*/

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

//Función para inicializar "cosas". Si hay error, lo printea y termina el programa.
void must_init(bool test, const char *description);

int main(void)
{
	//init genérico de allegro
	must_init(al_init(), "allegro");
	//init de teclado
	must_init(al_install_keyboard(), "keyboard");
	//init de mouse
	must_init(al_install_mouse(), "mouse");

	//timer que actualiza cada 1/30 segundos ("30fps")
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");

	//cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	//opciones para el display (antialiasing)
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	//crea display de 640x480 pixeles
    #define D_W 640
    #define D_H 480
	ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
	must_init(disp, "display");

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

	//coordenadas globales
	float x, y, curX, curY;
	x = 100;
	y = 100;

	/*
	#define KEY_SEEN     1
	#define KEY_RELEASED 2
	//arreglo para manejar 227 teclas posibles
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));	//lo pone todo a 0
	*/

	/*
	float dx, dy;
	dx = 0;
	dy = 0;
	al_grab_mouse(disp);
	al_hide_mouse_cursor(disp);     //oculta el cursor default
	*/

	//comienza a contar el timer 
	al_start_timer(timer);


	//loop principal
	while(1)
	{
		//bloquea el proceso hasta que llegue un evento de las fuentes registradas antes.
		al_wait_for_event(queue, &event);

		//analiza el tipo de evento
		switch(event.type)
		{
			//timer
			case ALLEGRO_EVENT_TIMER:

				//game logic

				//avisa que hay que renderizar
				redraw = true;
				break;

			//tecla presionada
			//case ALLEGRO_EVENT_KEY_CHAR:
			case ALLEGRO_EVENT_KEY_DOWN:
				if(event.keyboard.keycode == ALLEGRO_KEY_UP)
					y-=50;	//resta a la coordenada Y
				if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
					y+=50;
				if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
					x-=100;
				if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
					x+=100;

                //si NO es escape, sale del switch
				if(event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
					break;

                //si SÍ es escape, activa flag para terminar el programa, y sale del switch
                else
                {
                    done = true;
                    break;
                }

            //se mueve el mouse
            case ALLEGRO_EVENT_MOUSE_AXES:
                x = event.mouse.x;      //copia coordenadas del mouse a variables del programa
                y = event.mouse.y;
                curX = event.mouse.x;
                curY = event.mouse.y;
                break;
			
			//se apreto la "x" de la ventana
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				//para terminar el programa
				done = true;
				break;
		}


		//si hay que cerrar el programa
		if(done)
		{
			printf("\ncerrado\n");
			break;		//sale del while
		}

		//si se pide renderizar, y la cola de eventos esta vacía, se renderiza
		if(redraw && al_is_event_queue_empty(queue))
		{
			//pone todo en negro
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//escribe text con fuente "font", color, desde las coordenadas (0,0)
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
			//dibuja un rectángulo relleno de 10x10, color rojo
			al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));

            ALLEGRO_COLOR buttonColor;
            ALLEGRO_COLOR textColor;
            //si el cursor está dentro del rectángulo
            if(curX >= D_W/2 - 75 && curX <= D_W/2 + 75 && curY >= D_H/2 - 50 && curY <= D_H/2 + 50)
            {
                //se preasigna el color para el botón
                buttonColor = al_map_rgb(100,100,100);
                //se preasigna el color para el texto
                textColor = al_map_rgb(255,255,255);
            }
            else
            {
                buttonColor = al_map_rgb(0,100,0);
                textColor = al_map_rgb(0,0,255);
            }

            //dibuja rectángulo
            al_draw_filled_rectangle(D_W/2 - 75, D_H/2 - 50, D_W/2 + 75, D_H/2 + 50, buttonColor);
            //escribe texto en el centro del rectángulo
            al_draw_text(font, textColor, D_W/2, D_H/2, ALLEGRO_ALIGN_CENTER, "FROGGER"); 
            

			//carga los cambios anteriores para verlos
            /*sin este comando, todo lo anterior NO se visualiza en pantalla*/
			al_flip_display();

			//avisa que ya se renderizó
			redraw = false;
		}
	}

	//se destruyen las cosas creadas
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}

void must_init(bool test, const char *description)
{
	if(test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}
