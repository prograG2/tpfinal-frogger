# Makefile de la plataforma PC	\



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Directorio de objetos
OBJ_DIR := ../../../obj

# Directorio de bibliotecas
LIB_DIR := ../../../lib


# Objetos genericos sin path
_OBJS	:= display.o game.o input.o menu.o nombre.o 
# Objetos especificos sin path
_OBJS	+= allegro_stuff.o entities.o game_data.o geometry.o
# Objetos con path y la ID de la plataforma
OBJS	:= $(patsubst %.o,$(OBJ_DIR)/%_PC.o,$(_OBJS))


# algif5 stuff
_ALGIF_OBJS := algif.o bitmap.o gif.o lzw.o
ALGIF_OBJS	:= $(patsubst %.o,$(OBJ_DIR)/%_PC_ALGIF.o,$(_ALGIF_OBJS))


# Compilador
CC := gcc
#Flags de compilacion
CFLAGS := -Wall -Wno-unknown-pragmas -O2
ifdef CFLAG_DEBUG
CFLAGS += $(CFLAG_DEBUG)
endif


# Comando para borrar
RM := rm -f

# Crea directorio de objetos
dummy_obj_folder := $(shell mkdir -p $(OBJ_DIR))



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
all: $(OBJS) $(LIB_DIR)/libalgif.a


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/display_PC.o: display.c ../../display.h allegro_stuff.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_PC.o: game.c ../../game.h allegro_stuff.h entities.h game_data.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/input_PC.o: input.c ../../input.h allegro_stuff.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/menu_PC.o: menu.c ../../menu.h allegro_stuff.h geometry.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/nombre_PC.o: nombre.c ../../nombre.h allegro_stuff.h game_data.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/sound_PC.o: sound.c ../../sound.h
	$(CC) $(CFLAGS) -c $< -o $@

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~


$(OBJ_DIR)/allegro_stuff_PC.o: allegro_stuff.c allegro_stuff.h entities.h geometry.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/entities_PC.o: entities.c entities.h allegro_stuff.h geometry.h game_data.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_data_PC.o: game_data.c game_data.h allegro_stuff.h geometry.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/geometry_PC.o: geometry.c geometry.h
	$(CC) $(CFLAGS) -c $< -o $@


$(LIB_DIR)/libalgif.a: $(ALGIF_OBJS)
	ar -rc $@ $(ALGIF_OBJS)
	ranlib $@
$(OBJ_DIR)/algif_PC_ALGIF.o: ./algif5/algif.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/bitmap_PC_ALGIF.o: ./algif5/bitmap.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/gif_PC_ALGIF.o: ./algif5/gif.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/lzw_PC_ALGIF.o: ./algif5/lzw.c
	$(CC) $(CFLAGS) -c $< -o $@

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos
clean: clean-debug
	$(RM) $(OBJS)
	$(RM) $(ALGIF_OBJS)
	$(RM) $(LIB_DIR)/libalgif.a

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# PARA DEGUG | Trabaja en directorio actual ~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



all-debug: $(_OBJS)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

display.o: display.c ../../display.h allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

game.o: game.c ../../game.h allegro_stuff.h entities.h game_data.h 
	$(CC) $(CFLAGS) -c $<

input.o: input.c ../../input.h allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

menu.o: menu.c ../../menu.h allegro_stuff.h geometry.h
	$(CC) $(CFLAGS) -c $<

nombre.o: nombre.c ../../nombre.h allegro_stuff.h game_data.h
	$(CC) $(CFLAGS) -c $<

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~

allegro_stuff.o: allegro_stuff.c allegro_stuff.h entities.h geometry.h
	$(CC) $(CFLAGS) -c $<

entities.o: entities.c entities.h allegro_stuff.h geometry.h game_data.h
	$(CC) $(CFLAGS) -c $<

game_data.o: game_data.c game_data.h allegro_stuff.h geometry.h
	$(CC) $(CFLAGS) -c $<

geometry.o: geometry.c geometry.h
	$(CC) $(CFLAGS) -c $<

sound.o: sound.c ../../sound.h
	$(CC) $(CFLAGS) -c $< -o $@

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos locales
clean-debug:
	$(RM) $(_OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~