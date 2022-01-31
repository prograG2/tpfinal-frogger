# Makefile de los modulos no-especificos del programa	\



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Directorio de objetos
OBJ_DIR := ../obj


# Objetos sin path
_OBJS	:= main.o queue.o fsm.o ranking.o
# Objetos con path
OBJS	:= $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

# Headers de los modulos genericos de las plataformas
DEPS_GENERIC = display.h game.h input.h menu.h nombre.h


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
all: $(OBJS)


# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/main.o: main.c fsm.h queue.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/fsm.o: fsm.c fsm.h queue.h ranking.o $(DEPS_GENERIC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ranking.o: ranking.c ranking.h
	$(CC) $(CFLAGS) -c $< -o $@

# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~


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


# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~

main.o: main.c fsm.h queue.h
	$(CC) $(CFLAGS) -c $<

fsm.o: fsm.c fsm.h queue.h ranking.h $(DEPS_GENERIC)
	$(CC) $(CFLAGS) -c $<

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $<

ranking.o: ranking.c ranking.h
	$(CC) $(CFLAGS) -c $<

# Objetos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos locales
clean-debug:
	$(RM) $(_OBJS)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~



