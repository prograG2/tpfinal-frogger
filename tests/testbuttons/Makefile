ALLEGRO_LINKS = `pkg-config allegro-5 allegro_font-5 allegro_dialog-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 --libs --cflags`
CFLAGS = -O2 -Wall

test00: test00.c
	gcc test00.c $(CFLAGS) $(ALLEGRO_LINKS) -o test00

test01: test01.c
	gcc test01.c $(CFLAGS) $(ALLEGRO_LINKS) -o test01

clean:
	rm -f test00 test01

