# Makefile de la plataforma RPI	\



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Directorio de objetos
OBJ_DIR := ../../../obj


# Objetos genericos sin path
_OBJS	:= display_RPI.o game_RPI.o input_RPI.o menu_RPI.o nombre_RPI.o 
# Objetos especificos sin path
_OBJS	+= bitmap_RPI.o mensajes_RPI.o
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

$(OBJ_DIR)/display_RPI.o: display.c ../../display.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_RPI.o: game.c ../../game.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/input_RPI.o: input.c ../../input.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/menu_RPI.o: menu.c ../../menu.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/nombre_RPI.o: nombre.c ../../nombre.h
	$(CC) $(CFLAGS) -c $< -o $@

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/bitmap_RPI.o: bitmap.c bitmap.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/mensajes_RPI.o: mensajes.c mensajes.h
	$(CC) $(CFLAGS) -c $< -o $@

#$(OBJ_DIR)/:
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

bitmap.o: bitmap.c bitmap.h
	$(CC) $(CFLAGS) -c $<

mensajes.o: mensajes.c mensajes.h
	$(CC) $(CFLAGS) -c $<

#:
#	$(CC) $(CFLAGS) -c $<

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos locales
clean-debug:
	$(RM) $(_OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~