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

# Objetos principales (sin path)
_OBJS = main.o queue.o fsm.o
OBJS = $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))

# Plataforma a compilar. Se inicializa luego
PLATFORM = 0


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

# Crea directorio de objetos y ejecutable
dummy_obj_folder := $(shell mkdir -p $(OBJ_DIR))
dummy_obj_folder := $(shell mkdir -p $(BIN_DIR))


# Se exportan variables para que sean visibles por subshells de otros comandos
export OBJ_DIR



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



$(BIN_DIR)/$(EXEC):
ifneq ( , $(filter $(PLATFORM),PC RPI))
$(BIN_DIR)/$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@
else
	@echo Elija alguna plataforma para compilar: ~make pc~ o ~make rpi~
endif


# Regla para PC
pc:
	$(MAKE) -C $(SRC_PC_DIR)
	$(eval PLATFORM = PC)
	$(eval LIBS += $(LIBS_PC))
	$(eval OBJS += $(wildcard $(OBJ_DIR)/*_$(PLATFORM).o))
	echo ;
	echo Echoing objs: $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))$(OBJS)
	echo ;
	echo Echoing libs: $(LIBS)
	echo ;
	echo Echoing platform: $(PLATFORM)
	echo ;
	$(MAKE) -C $(SRC_DIR)
pc:	$(BIN_DIR)/$(EXEC)


# Regla para RPI
rpi:
	$(MAKE) -C $(SRC_RPI_DIR)
	$(eval PLATFORM = RPI)
	$(eval LIBS += $(LIBS_RPI))
	$(eval OBJS += $(wildcard $(OBJ_DIR)/*_$(PLATFORM).o))
	echo ;
	echo Echoing objs: $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))$(OBJS)
	echo ;
	echo Echoing libs: $(LIBS)
	echo ;
	echo Echoing platform: $(PLATFORM)
	echo ;
	$(MAKE) -C $(SRC_DIR)
rpi: $(BIN_DIR)/$(EXEC)


# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~

# Borra objetos
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(SRC_PC_DIR) clean
	$(MAKE) -C $(SRC_RPI_DIR) clean

# Borra objetos y ejecutable
cleaner: clean
	cd $(BIN_DIR);		\
	$(RM) *

# Otras reglas ~~~~~~~~~~~~~~~~~~~~~~~~