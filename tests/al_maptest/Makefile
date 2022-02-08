ALLEGRO_LINKS = `pkg-config allegro-5 allegro_font-5 allegro_dialog-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 --libs --cflags`
CFLAGS = -O2 -Wall

main: main.c
	gcc main.c $(CFLAGS) $(ALLEGRO_LINKS) -o main

run: main
	./main

clean:
	rm -f main
 