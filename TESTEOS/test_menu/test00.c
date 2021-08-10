/*
gcc test00.c -o test00 $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs --cflags)
./test00
*/

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

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
	float x, y;
	x = 100;
	y = 100;

	#define KEY_SEEN     1
	#define KEY_RELEASED 2

	//arreglo para manejar 227 teclas posibles
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));	//lo pone todo a 0

	/*
	float dx, dy;
	dx = 0;
	dy = 0;
	al_grab_mouse(disp);
	al_hide_mouse_cursor(disp);
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
				if(key[ALLEGRO_KEY_UP])
					y-=5;	//resta 5 a la coordenada y
				if(key[ALLEGRO_KEY_DOWN])
					y+=5;
				if(key[ALLEGRO_KEY_LEFT])
					x-=5;
				if(key[ALLEGRO_KEY_RIGHT])
					x+=5;

				if(key[ALLEGRO_KEY_ESCAPE])
					//para terminar el programa
					done = true;

				//avisa que se leyeron todas las teclas
				for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
					key[i] &= KEY_SEEN;

				//avisa que hay que renderizar
				redraw = true;
				break;

			//tecla presionada
			case ALLEGRO_EVENT_KEY_DOWN:
				//registra que se presionó una tecla
				key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
				break;

			//tecla soltada
			case ALLEGRO_EVENT_KEY_UP:
				//registra que se soltó una tecla
				key[event.keyboard.keycode] &= KEY_RELEASED;
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

			//carga los cambios anteriores para verlos
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
