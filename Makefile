SHELL := /bin/bash

MAKE_DIR			:= $(PWD)

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


CC := gcc
CFLAGS := -Wall -Wno-unknown-pragmas -O2

LIBS_PC		:=
LIBS_PC		+= `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 \
				allegro_primitives-5 allegro_image-5 allegro_audio-5 \
				allegro_acodec-5 --libs --cflags`
LIBS_PC 	+= -lm -L$(LIB_DIR) libalgif.a

LIBS_RPI	:=
LIBS_RPI	+= -lpthread -lm -L$(LIB_DIR) librpiutils.a

_OBJS 			:= main.o fsm.o queue.o util.o
OBJS			:= $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))

_OBJS_PLATFORM	:= display.o game.o input.o menu.o nombre.o 
OBJS_PLATFORM	:= $(patsubst %, $(OBJ_DIR)/%, $(_OBJS_PLATFORM))

OBJS			+= $(OBJS_PLATFORM)

# Nombre del ejecutable
EXEC 			:= frogger


RM := find $(PWD) -type f -delete


export CC CFLAGS RM OBJ_DIR OBJ_PC_DIR OBJ_RPI_DIR OBJS_PLATFORM


$(EXEC):
ifdef LIBS
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@
else
	@echo Elija alguna plataforma para compilar: 'make pc' o 'make rpi'
endif

pc:	LIBS = $(LIBS_PC)
pc:
	$(MAKE) -C $(SRC_PC_DIR) -f pc.mk
pc: $(EXEC)

rpi: LIBS = $(LIBS_RPI)
rpi:
	$(MAKE) -C $(SRC_RPI_DIR) -f rpi.mk
rpi: $(EXEC)

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


.PHONY: clean
clean:
	cd $(OBJ_DIR) 	
	$(RM) 
	cd $(BIN_DIR) 	
	$(RM) 