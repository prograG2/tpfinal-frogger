main: main.o fsm.o queue.o threads_pc.o
	gcc -Wall -g main.o fsm.o queue.o threads_pc.o -o main -lallegro -lallegro_font -lallegro_primitives -lpthread

main.o: main.c fsm.h queue.h global.h
	gcc -Wall -g -c main.c

fsm.o: fsm.c fsm.h queue.h global.h rutinas_pc.o
	gcc -Wall -g -c fsm.c

queue.o: queue.c queue.h global.h
	gcc -Wall -g -c queue.c

rutinas_pc.o: rutinas_pc.c fsm.o threads_pc.o queue.o menu_pc.o
	gcc -Wall -g -c rutinas_pc.c -lallegro -lallegro_font -lallegro_primitives

display_pc.o: display_pc.c display_pc.h queue.c global.h
	gcc -Wall -g -c display_pc.c -lallegro -lallegro_font -lallegro_primitives

threads_pc.o: threads_pc.c threads_pc.h queue.o display_pc.o global.h menu_pc.o gamedata.h fsm.o
	gcc -Wall -g -c threads_pc.c -lallegro -lallegro_font -lallegro_primitives -lpthread

menu_pc.o: menu_pc.c menu_pc.h
	gcc -Wall -g -c menu_pc.c


	
