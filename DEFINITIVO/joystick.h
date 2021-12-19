#ifndef JOYSTICK
#define JOYSTICK

#include <stdint.h>
#include "joydrv.h"
#include "global.h"

int iniciarJoystick();

event_t leerJoystick();

#endif