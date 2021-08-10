# makefile general del proyecto.

# Organizativo
CC := gcc
OPTIONS := -Wall 
# -g para debuggear, -O2 para optimizar
OBJS = main.o game_data.o fsm.o queue.o display.o timer.o termlib.o


# Ejecutables
frogger: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} -o frogger

# VM: ${OBJS}
#	${CC} ${OPTIONS} ${OBJS} -o froggerVM -D PLATAFORMA=0

# RPI: ${OBJS}
#	${CC} ${OPTIONS} {OBJS} -o froggerRPI -D PLATAFORMA=1


# Objetos
main.o: main.c global.h fsm.h queue.h termlib.h
	${CC} ${OPTIONS} -c main.c

game_data.o: game_data.c game_data.h global.h
	${CC} ${OPTIONS} -c game_data.c

fsm.o: fsm.c fsm.h
	${CC} ${OPTIONS} -c fsm.c

queue.o: queue.c queue.h fsm.h
	${CC} ${OPTIONS} -c queue.c

display.o: display.c display.h
	${CC} ${OPTIONS} -c display.c

timer.o: timer.c timer.h
	${CC} ${OPTIONS} -c timer.c

termlib.o: termlib.c termlib.h
	${CC} ${OPTIONS} -c termlib.c



# Limpia objetos
clean:
	rm *.o
