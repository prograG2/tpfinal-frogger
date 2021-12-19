#include "display_pc.h"

int iniciarDisplay(){
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	disp = al_create_display(640, 480);
	must_init(disp, "display");
	font = al_create_builtin_font();
	must_init(font, "font");
    must_init(al_init_primitives_addon(), "primitives");
    al_register_event_source(al_queue, al_get_display_event_source(disp));
    al_init_image_addon();
    
}

void actualizarDisplay(){
    pthread_mutex_lock(&lock);
	al_flip_display();
    pthread_mutex_unlock(&lock);
}


void limpiarDisplay(){
    pthread_mutex_lock(&lock);
	al_clear_to_color(al_map_rgb(255, 255, 255));
    pthread_mutex_unlock(&lock);
}

void mostrarTexto(char* txt, int pos){
	al_draw_text(font, al_map_rgb(0,0,255), ANCHO/2, pos, ALLEGRO_ALIGN_CENTER, txt);
    actualizarDisplay();
}

