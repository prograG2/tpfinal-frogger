frogger_rpi: main.o bitmap_rpi.o disdrv.o display_rpi.o fsm.o game_rpi.o joydrv.o joystick.o mensajes_rpi.o menu_rpi.o nombre_rpi.o queue.o util.o
	gcc -Wall -g main.o bitmap_rpi.o disdrv.o display_rpi.o fsm.o game_rpi.o joydrv.o joystick.o mensajes_rpi.o menu_rpi.o nombre_rpi.o queue.o util.o -o frogger_rpi -lpthread

main.o: main.c fsm.h queue.h global.h
	gcc -Wall -g -c main.c

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
