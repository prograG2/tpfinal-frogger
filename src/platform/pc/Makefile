# Makefile de la plataforma PC	\



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Objetos genericos sin path
_OBJS	:= display.o game.o input.o menu.o nombre.o 
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



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
all: dirs $(OBJS)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/display.o: display.c ../../display.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/game.o: game.c ../../game.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/input.o: input.c ../../input.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/menu.o: menu.c ../../menu.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/nombre.o: nombre.c ../..nombre.h
	$(CC) $(CFLAGS) -c $<

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/allegro_stuff.o: allegro_stuff.c allegro_stuff.h
	$(CC) $(CFLAGS) -c $<

#$(OBJ_DIR)/:
#	$(CC) $(CFLAGS) -c $<

# Objetos especificos ~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Crea directorio de objetos, si no esta creado
dirs:
	$(MK) $(OBJ_DIR)

# Borra objetos
clean:
	$(RM) $(OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# PARA DEGUG | Trabaja en directorio actual ~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



all-debug; $(_OBJS)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

display.o: display.c ../../display.h
	$(CC) $(CFLAGS) -c $<

game.o: game.c ../../game.h
	$(CC) $(CFLAGS) -c $<

input.o: input.c ../../input.h
	$(CC) $(CFLAGS) -c $<

menu.o: menu.c ../../menu.h
	$(CC) $(CFLAGS) -c $<

nombre.o: nombre.c ../..nombre.h
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