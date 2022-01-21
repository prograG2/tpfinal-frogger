# Makefile principal del proyecto	\
	-Crea objetos principales		\
	-Linkea con los objetos de plataforma	\
											\
	'make pc' compila y linkea para PC		\
	'make rpi' compila y linkea para RPI	



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


# Correr make con VERBOSE=1 para habiltiar los ecos
ifndef VERBOSE
# Evita ecos de make en consola
MAKEFLAGS += --silent
endif


# Directorio root
MAKE_DIR			:= $(PWD)

# Subdirectorios
BIN_DIR    			:= $(MAKE_DIR)/bin
DOC_DIR	    		:= $(MAKE_DIR)/doc
LIB_DIR 			:= $(MAKE_DIR)/lib
OBJ_DIR   			:= $(MAKE_DIR)/obj
OBJ_PLATFORM_DIR	:= $(OBJ_DIR)/platform
OBJ_PC_DIR			:= $(OBJ_PLATFORM_DIR)/pc
OBJ_RPI_DIR			:= $(OBJ_PLATFORM_DIR)/rpi
SRC_DIR   			:= $(MAKE_DIR)/src
SRC_PC_DIR			:= $(SRC_DIR)/platform/pc
SRC_RPI_DIR			:= $(SRC_DIR)/platform/rpi


# Objetos principales (sin paths)
_OBJS 			:= main.o fsm.o queue.o util.o
# Se agregan los paths
OBJS			:= $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))

# Objetos genericos (sin paths)
_OBJS_PLATFORM	:= display.o game.o input.o menu.o nombre.o 
# Se agregan los paths
OBJS_PLATFORM	:= $(patsubst %, $(OBJ_DIR)/%, $(_OBJS_PLATFORM))

# Se juntan todos los objetos con paths
OBJS			+= $(OBJS_PLATFORM)


# Libraries stuff ~~~~~~~~~~~~~~~~~~~~~~~~~
# Librerias genericas
LIBS		:= -lpthread -lm

# Librerias para PC
LIBS_PC		:=
LIBS_PC		+= `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 \
				allegro_primitives-5 allegro_image-5 allegro_audio-5 \
				allegro_acodec-5 --libs --cflags`
LIBS_PC 	+= -L$(LIB_DIR) libalgif.a

# Librerias para RPI
LIBS_RPI	:=
LIBS_RPI	+=  -L$(LIB_DIR) librpiutils.a
# Libraries stuff ~~~~~~~~~~~~~~~~~~~~~~~~~


# Compilador
CC := gcc
#Flags de compilacion
CFLAGS := -Wall -Wno-unknown-pragmas -O2
# Nombre del ejecutable
EXEC 			:= frogger

# Comando para borrar
RM := rm -f
# Comando para crear directorio si no existe
MK := mkdir -p


# Se exportan algunas variables para que sean visibles por subshells de otro comandos
export CC CFLAGS RM MK MAKE_DIR SRC_DIR OBJ_DIR OBJ_PC_DIR OBJ_RPI_DIR OBJS_PLATFORM



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
$(BIN_DIR)/$(EXEC):
ifdef PLATFORM
$(BIN_DIR)/$(EXEC): $(OBJS)					
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@
else
	@echo Elija alguna plataforma para compilar: ~make pc~ o ~make rpi~
endif


# Regla para PC
pc:	PLATFORM = PC
pc: dirs
	$(MAKE) -C $(SRC_PC_DIR) -f pc.mk
pc: LIBS += LIBS_PC $(BIN_DIR)/$(EXEC)


# Regla para RPI
rpi: PLATFORM = RPI
rpi: dirs
	$(MAKE) -C $(SRC_RPI_DIR) -f rpi.mk
rpi: LIBS += LIBS_RPI $(BIN_DIR)/$(EXEC)


# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/fsm.h $(SRC_DIR)/queue.h \
					$(SRC_DIR)/global.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/fsm.o: $(SRC_DIR)/fsm.c $(SRC_DIR)/fsm.h $(SRC_DIR)/queue.h \
					$(SRC_DIR)/util.h $(SRC_DIR)/global.h \
					$(patsubst %.o, %.h, $(OBJS_PLATFORM_NAMES))
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/queue.o: $(SRC_DIR)/queue.c $(SRC_DIR)/queue.h $(SRC_DIR)/global.h
	$(CC) $(CFLAGS) -c $<

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.c $(SRC_DIR)/util.h $(SRC_DIR)/global.h
	$(CC) $(CFLAGS) -c $<

# Objetos genericos ~~~~~~~~~~~~~~~~~~~~~~~~~


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Crea directorios de ejecutable y objetos si no estan creados
dirs:
	$(MK) $(BIN_DIR);	\
	$(MK) $(OBJ_DIR)	


# Borra todos los objetos y el ejecutable creados
clean:
	cd $(OBJ_DIR);			\
	$(RM) _OBJS;			\
	cd $(BIN_DIR);			\
	$(RM) $(EXEC);				\
	$(MAKE) -C $(SRC_PC_DIR) -f pc.mk clean;	\
	$(MAKE) -C $(SRC_RPI_DIR) -f rpi.mk clean
	
# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~	