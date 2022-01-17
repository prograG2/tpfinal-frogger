#'make' para compilar todo
#'make run' para compilar todo y ejecutar
#'make clean' para borrar todos los objetos

CC := gcc
OPTIONS := -Wall
NOLINK := -c
OBJS = main.o allegro_stuff.o entities.o geometry.o
ALLEGRO_LINKS = `pkg-config --libs --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5`

#Linkeo de los objetos
frogger: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} -o frogger ${ALLEGRO_LINKS}

#Creación de los objetos
main.o: main.c allegro_stuff.h entities.h geometry.h
	${CC} ${OPTIONS} ${NOLINK} main.c 

allegro_stuff.o: allegro_stuff.c geometry.h
	${CC} ${OPTIONS} ${NOLINK} allegro_stuff.c 

entities.o: entities.c allegro_stuff.h geometry.h
	${CC} ${OPTIONS} ${NOLINK} entities.c

geometry.o: geometry.c
	${CC} ${OPTIONS} ${NOLINK} geometry.c  

clean:
	rm *.o

run: frogger
	./frogger