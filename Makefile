# Makefile principal del proyecto	\
	-Linkea todos lo objetos con librerias correspondientes	\
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
SRC_DIR   			:= $(MAKE_DIR)/src
SRC_PC_DIR			:= $(SRC_DIR)/platform/pc
SRC_RPI_DIR			:= $(SRC_DIR)/platform/rpi


# Objetos con fullpath
OBJS = $(wildcard $(OBJ_DIR)/*.o)


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
export OBJ_DIR MK



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Regla principal
all: $(BIN_DIR)/$(EXEC)


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
	$(MAKE) -C $(SRC_PC_DIR)
pc: LIBS += LIBS_PC $(BIN_DIR)/$(EXEC)


# Regla para RPI
rpi: PLATFORM = RPI
rpi: dirs
	$(MAKE) -C $(SRC_RPI_DIR)
rpi: LIBS += LIBS_RPI $(BIN_DIR)/$(EXEC)


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Crea directorios de ejecutable y objetos si no estan creados
dirs:
	$(MK) $(BIN_DIR);	\
	$(MK) $(OBJ_DIR)	


# Borra objetos
clean:
	$(RM) $(OBJS);							\
	$(MAKE) -C $(SRC_DIR) clean;			\
	$(MAKE) -C $(SRC_PC_DIR) clean;			\
	$(MAKE) -C $(SRC_PC_DIR) clean-debug;	\
	$(MAKE) -C $(SRC_RPI_DIR) clean;		\
	$(MAKE) -C $(SRC_RPI_DIR) clean-debug

# Borra objetos y ejecutable
cleaner: clean
	cd $(BIN_DIR);		\
	$(RM) *
	
# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~	