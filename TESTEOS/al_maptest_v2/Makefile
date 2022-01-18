# 'make' para compilar todo
# 'make run' para compilar todo y ejecutar
# 'make clean' para borrar todos los objetos

CC = gcc
CFLAGS = -Wextra -Wall -O2
OBJS = main.o allegro_stuff.o entities.o geometry.o game_data.o
ALLEGRO_LINKS = `pkg-config --libs --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5`
RM = rm -rf $(OBJS)

# Regla principal
all: frogger

# Linkeo de los objetos
frogger: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(ALLEGRO_LINKS) -o $@ 

# Creación de los objetos, sin linkeo
main.o: main.c allegro_stuff.h entities.h geometry.h game_data.h
	$(CC) $(CFLAGS) -c main.c

allegro_stuff.o: allegro_stuff.c geometry.h
	$(CC) $(CFLAGS) -c allegro_stuff.c

entities.o: entities.c allegro_stuff.h geometry.h game_data.h
	$(CC) $(CFLAGS) -c entities.c

geometry.o: geometry.c
	$(CC) $(CFLAGS) -c geometry.c

game_data.o: game_data.c geometry.h allegro_stuff.h
	$(CC) $(CFLAGS) -c game_data.c

# Otras reglas
clean:
	$(RM)

run: frogger
	./frogger