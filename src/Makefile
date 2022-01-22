# Makefile de los modulos no-especificos del programa	\



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Objetos sin path
_OBJS	:= main.o fsm.o queue.o util.o
# Objetos con path
OBJS	:= $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

# Headers de los modulos genericos de las plataformas
DEPS_GENERIC = display.h game.h input.h menu.h nombre.h


# Compilador
CC := gcc
#Flags de compilacion
CFLAGS := -Wall -Wno-unknown-pragmas -O2


# Comando para borrar
RM := rm -f



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
all: $(OBJS)


# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/main.o: main.c fsm.h queue.h global.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/fsm.o: fsm.c fsm.h queue.h util.h global.h $(DEPS_GENERIC)
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/queue.o: queue.c queue.h global.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/util.o: util.c util.h global.h
	$(CC) $(CFLAGS) -c $<

# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~


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


# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~

main.o: main.c fsm.h queue.h global.h
	$(CC) $(CFLAGS) -c $<

fsm.o: fsm.c fsm.h queue.h util.h global.h $(DEPS_GENERIC)
	$(CC) $(CFLAGS) -c $<

queue.o: queue.c queue.h global.h
	$(CC) $(CFLAGS) -c $<

util.o: util.c util.h global.h
	$(CC) $(CFLAGS) -c $<

# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos locales
clean-debug:
	$(RM) $(_OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~



