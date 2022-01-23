# Makefile de la plataforma PC	\



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Directorio de objetos
OBJ_DIR := ../../../obj


# Objetos genericos sin path
_OBJS	:= display_PC.o game_PC.o input_PC.o menu_PC.o nombre_PC.o 
# Objetos especificos sin path
_OBJS	+= 
# Objetos con path
OBJS	:= $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))


# Compilador
CC := gcc
#Flags de compilacion
CFLAGS := -Wall -Wno-unknown-pragmas -O2


# Comando para borrar
RM := rm -f

# Crea directorio de objetos
dummy_obj_folder := $(shell mkdir -p $(OBJ_DIR))



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
all: $(OBJS)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/display_PC.o: display.c ../../display.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_PC.o: game.c ../../game.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/input_PC.o: input.c ../../input.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/menu_PC.o: menu.c ../../menu.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/nombre_PC.o: nombre.c ../../nombre.h
	$(CC) $(CFLAGS) -c $< -o $@

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/allegro_stuff_PC.o: allegro_stuff.c allegro_stuff.h
	$(CC) $(CFLAGS) -c $< -o $@

#$(OBJ_DIR)/_PC.o:
#	$(CC) $(CFLAGS) -c $< -o $@

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos
clean: clean-debug
	$(RM) $(OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# PARA DEGUG | Trabaja en directorio actual ~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



all-debug: $(_OBJS)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

display.o: display.c ../../display.h
	$(CC) $(CFLAGS) -c $<

game.o: game.c ../../game.h
	$(CC) $(CFLAGS) -c $<

input.o: input.c ../../input.h
	$(CC) $(CFLAGS) -c $<

menu.o: menu.c ../../menu.h
	$(CC) $(CFLAGS) -c $<

nombre.o: nombre.c ../../nombre.h
	$(CC) $(CFLAGS) -c $<

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~

allegro_stuff.o: allegro_stuff.c allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

#:
#	$(CC) $(CFLAGS) -c $<

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos locales
clean-debug:
	$(RM) $(_OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~