<<<<<<< HEAD
main: main.o fsm.o queue.o threads_pc.o
	gcc -Wall -g main.o fsm.o queue.o threads_pc.o -o main -lallegro -lallegro_font -lallegro_primitives -lpthread
=======
frogger_rpi: main.o bitmap_rpi.o disdrv.o display_rpi.o fsm.o game_rpi.o joydrv.o joystick.o mensajes_rpi.o menu_rpi.o nombre_rpi.o queue.o util.o
	gcc -Wall -g main.o bitmap_rpi.o disdrv.o display_rpi.o fsm.o game_rpi.o joydrv.o joystick.o mensajes_rpi.o menu_rpi.o nombre_rpi.o queue.o util.o -o frogger_rpi -lpthread
>>>>>>> rpi funcionando

main.o: main.c fsm.h queue.h global.h
	gcc -Wall -g -c main.c

<<<<<<< HEAD
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


	
=======
bitmap_rpi.o: bitmap_rpi.c bitmap_rpi.h
	gcc -Wall -g -c bitmap_rpi.c

display_rpi.o: display_rpi.c display_rpi.h bitmap_rpi.h mensajes_rpi.h global.h
	gcc -Wall -g -c display_rpi.c -lpthread

fsm.o: fsm.c fsm.h queue.h util.h global.h nombre_rpi.h game_rpi.h display_rpi.h menu_rpi.h joystick.h
	gcc -Wall -g -c fsm.c -lpthread

game_rpi.o: game_rpi.c game_rpi.h queue.h bitmap_rpi.h global.h display_rpi.h
	gcc -Wall -g -c game_rpi.c

joystick.o: joystick.c joystick.h joydrv.h global.h
	gcc -Wall -g -c joystick.c

mensajes_rpi.o: mensajes_rpi.c mensajes_rpi.h bitmap_rpi.h global.h
	gcc -Wall -g -c mensajes_rpi.c

menu_rpi.o: menu_rpi.c menu_rpi.h mensajes_rpi.h global.h display_rpi.h
	gcc -Wall -g -c menu_rpi.c

nombre_rpi.o: nombre_rpi.c nombre_rpi.h mensajes_rpi.h display_rpi.h global.h
	gcc -Wall -g -c nombre_rpi.c

queue.o: queue.c queue.h global.h
	gcc -Wall -g -c queue.c

util.o: util.c util.h
	gcc -Wall -g -c util.c
>>>>>>> rpi funcionando
