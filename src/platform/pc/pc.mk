# Makefile de la plataforma PC	\
	Crea los objetos genericos y privados de la plataforma.



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Directorio objeto de la plataforma
OBJ_PLAT_DIR = $(OBJ_PC_DIR)

# Objetos especificos de la platafoma (sin paths)
_OBJS	:= 
# Se agregan los paths
OBJS 	:= $(patsubst %, $(OBJ_PLAT_DIR)/%, $(_OBJS))
# Se agregan los objetos genericos
OBJS	+= $(OBJS_PLATFORM)



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
all: dirs $(OBJS)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/display.o: display.c $(SRC_DIR)/display.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/game.o: game.c $(SRC_DIR)/game.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/input.o: input.c $(SRC_DIR)/input.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/menu.o: menu.c $(SRC_DIR)/menu.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/nombre.o: nombre.c $(SRC_DIR)/nombre.h
	$(CC) $(CFLAGS) -c $<

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_PLAT_DIR)/allegro_stuff.o: allegro_stuff.c allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_PLAT_DIR)/:
	$(CC) $(CFLAGS) -c $<

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Crea directorios objetos si no estan creados
dirs:
	$(MK) $(OBJ_DIR);	\
	$(MK) $(OBJ_PLAT_DIR)

# Borra objetos creados (por este makefile)
clean:
	$(RM) $(OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~