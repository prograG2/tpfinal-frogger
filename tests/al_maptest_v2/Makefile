
# 'make' para buildear todo
# 'make run' para buildear todo y ejecutar
# 'make clean' para borrar objetos y ejecutable
# 'make clean all' para rebuildear todo
# 'make 'rerun' rebuildear todo y ejecutar

# Compilador
CC := gcc

# Flags de compilacion. Se desactivan warnings de pragmas, por le uso de 'region' y 'endregion' en MVSCode
CFLAGS := -Wall -Wno-unknown-pragmas -O2

# Objetos
OBJS := main.o allegro_stuff.o entities.o geometry.o game_data.o menu.o

# Ejecutable
EXEC := frogger

# Para el linkeo de librerias de allegro
ALLEGRO_LINKS := `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 --libs --cflags`

# Otros linkeos (algif)
EXTRA_LINKS := -lm -L. libalgif.a

# Comando para borrar archivos
RM := rm -f

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Regla principal
all: $(EXEC)

# Linkeo de los objetos
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(ALLEGRO_LINKS) $(EXTRA_LINKS) -o $@ 

# Creación de los objetos, sin linkeo
main.o: main.c allegro_stuff.h entities.h geometry.h game_data.h algif.h
	$(CC) $(CFLAGS) -c $<

allegro_stuff.o: allegro_stuff.c geometry.h
	$(CC) $(CFLAGS) -c $<

entities.o: entities.c allegro_stuff.h geometry.h game_data.h
	$(CC) $(CFLAGS) -c $<

geometry.o: geometry.c
	$(CC) $(CFLAGS) -c $<

game_data.o: game_data.c geometry.h allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

menu.o: menu.c allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

# Otras reglas
rerun: clean
	$(MAKE) run

clean:
	$(RM) $(OBJS) $(EXEC)

run: all
	./frogger