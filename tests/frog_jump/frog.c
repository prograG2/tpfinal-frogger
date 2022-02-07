#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#define SC_WIDTH 640
#define SC_HEIGHT 480
#define TRUE 1
#define FALSE 0
#define FPS 60
#define PLAYER_COL 2
#define PLAYER_ROW 4
#define NO_FLAGS 0
#define PLAYER_SPEED 5

int main (void)
{
    ALLEGRO_DISPLAY *display; //EL EJE Y SIEMPRE ESTA INVERTIDO

    if (!al_init())
        al_show_native_message_box (display, NULL, NULL, "Couldn't initialize Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    
    display = al_create_display (SC_WIDTH, SC_HEIGHT);

    if (!display)
        al_show_native_message_box (display, NULL, NULL, "Display window couldn't be created", NULL, ALLEGRO_MESSAGEBOX_ERROR);

    al_set_new_display_flags (ALLEGRO_WINDOWED);
    al_set_window_position (display, 200, 200);
    al_set_new_window_title ("Frogger");

    char done = FALSE, draw = FALSE, active = FALSE;
    enum directions {up, right, left, down};
    double x = 10, y = 10;
    int mov_speed = 1, direction = down, source_x = 0, source_y = 0, player_speed;

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue ();

    al_install_keyboard ();
    ALLEGRO_KEYBOARD_STATE keystate;

    ALLEGRO_COLOR pitch_black = al_map_rgb (0, 0 ,0);
    al_register_event_source (event_queue, al_get_display_event_source (display));

    al_init_image_addon ();
    ALLEGRO_BITMAP *player = al_load_bitmap ("frog_spritesheet.png");
    double player_width = al_get_bitmap_width (player) / PLAYER_COL, player_height = al_get_bitmap_height (player) / PLAYER_ROW;
    al_register_event_source (event_queue, al_get_keyboard_event_source());

    ALLEGRO_TIMER *timer = al_create_timer (1.0/FPS);
    al_register_event_source (event_queue, al_get_timer_event_source (timer));
    al_start_timer (timer); //SOLO GAMELOOP DESPUES DE ESTO

    while (!done)   //GAMELOOP
    {
        ALLEGRO_EVENT events;
        al_wait_for_event (event_queue, &events);

        for (player_speed = PLAYER_SPEED; player_speed > 0; player_speed--)
        {
            if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //PARA SALIR
                done = TRUE;
            
            if (events.type == ALLEGRO_EVENT_TIMER) //MOVIMIENTO
            {
                active = TRUE;

                al_get_keyboard_state (&keystate);
                if (al_key_down (&keystate, ALLEGRO_KEY_DOWN))
                {
                    y += mov_speed;
                    direction = down;
                }
                else if (al_key_down (&keystate, ALLEGRO_KEY_UP))
                {
                    y -= mov_speed;
                    direction = up;
                }    
                else if (al_key_down (&keystate, ALLEGRO_KEY_RIGHT))
                {
                    x += mov_speed;
                    direction = right;
                }
                else if (al_key_down (&keystate, ALLEGRO_KEY_LEFT))
                {
                    x -= mov_speed;
                    direction = left;
                }
                else
                {
                    active = FALSE;
                }

                if (active)
                {
                    source_x = player_width;
                }
                else
                {
                    source_x = 0;
                }

                source_y = direction;

                draw = TRUE;           
            }

            if (draw)   //PARA QUE DIBUJE SOLO SI SE MUEEVE
            {
                al_draw_bitmap_region (player, source_x, source_y * player_height, player_width, player_height, x, y, NO_FLAGS);
                al_flip_display ();
                al_clear_to_color (pitch_black);

                draw = FALSE;
            }
        }
    }

    al_destroy_display (display);
    al_destroy_event_queue (event_queue);
    al_destroy_timer (timer);
    al_destroy_bitmap (player);

    return 0;
}