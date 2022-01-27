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
MAKE_DIR			:= .

# Subdirectorios
BIN_DIR    			:= $(MAKE_DIR)/bin
DOC_DIR	    		:= $(MAKE_DIR)/doc
LIB_DIR 			:= $(MAKE_DIR)/lib
OBJ_DIR   			:= $(MAKE_DIR)/obj
SRC_DIR   			:= $(MAKE_DIR)/src
SRC_PC_DIR			:= $(SRC_DIR)/platform/pc
SRC_RPI_DIR			:= $(SRC_DIR)/platform/rpi

# Objetos principales (sin path)
_OBJS = main.o queue.o fsm.o
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))


# Libraries stuff ~~~~~~~~~~~~~~~~~~~~~~~~~
# Librerias genericas
LIBS		:= -lpthread -lm

# Librerias para PC
LIBS_PC		:=
LIBS_PC		+= `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 --libs --cflags`
#LIBS_PC 	+= -Llib -lalgif



# Librerias para RPI
LIBS_RPI	:=
LIBS_RPI	+=  -Llib -lrpiutils
# Libraries stuff ~~~~~~~~~~~~~~~~~~~~~~~~~


# Compilador
CC := gcc
#Flags de compilacion
CFLAGS := -Wall -Wno-unknown-pragmas -O2
#CFLAG_DEBUG := -g
ifdef CFLAG_DEBUG
CFLAGS += $(CFLAG_DEBUG)
endif


# Comando para borrar
RM := rm -f
# Comando para crear directorio si no existe
MK := mkdir -p



# Se exportan variables para que sean visibles por subshells de otros comandos
export OBJ_DIR CFLAG_DEBUG



# Plataforma (https://westermarck.com/thoughts/raspberry-pi-linux-32-64/)
arch		:= ($shell uname -m)
ifeq ($(arch), armv7l)
PLATFORM 	= RPI
TARGET 		= frogger_RPI
else
PLATFORM = PC
TARGET 		= frogger_PC
endif



# Crea directorio de objetos y ejecutable
dummy_obj_folder := $(shell mkdir -p $(OBJ_DIR))
dummy_obj_folder := $(shell mkdir -p $(BIN_DIR))



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



all: $(BIN_DIR)/$(TARGET)


$(BIN_DIR)/$(TARGET): build_MAIN build_$(PLATFORM)
	$(eval OBJS += $(wildcard $(OBJ_DIR)/*_$(PLATFORM).o))
	$(eval LIBS += $(LIBS_$(PLATFORM)))
	@echo ;
	@echo Echoing objs: $(OBJS)
	@echo ;
	@echo Echoing libs: $(LIBS)
	@echo ;
	@echo Echoing platform: $(PLATFORM)
	@echo ;
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@


# Regla para modulos principales
build_MAIN:
	$(MAKE) -C $(SRC_DIR)

# Regla para PC
build_PC:
	$(MAKE) -C $(SRC_PC_DIR)

# Regla para RPI
build_RPI:
	$(MAKE) -C $(SRC_RPI_DIR)


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~	

# Ejecuta
run: all
	cd $(BIN_DIR);	\
	./$(TARGET)

# Borra objetos
clean:
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(SRC_PC_DIR) clean
	$(MAKE) -C $(SRC_RPI_DIR) clean

# Borra objetos y ejecutable
cleaner: clean
	$(RM) $(BIN_DIR)/$(TARGET)

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~