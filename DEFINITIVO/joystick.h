#ifndef JOYSTICK
#define JOYSTICK

#include <stdint.h>
#include "joydrv.h"
<<<<<<< HEAD

enum movimiento{NO_MOVER, ARRIBA, IZDA, ABAJO, DCHA, PRESS};

int prev = NO_MOVER;

int iniciarJoystick();

static int8_t modulo(int8_t x);

int leerJoystick();
=======
#include "global.h"

int iniciarJoystick();

event_t leerJoystick();
>>>>>>> rpi funcionando

#endif