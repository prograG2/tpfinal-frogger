#ifndef INPUT_RPI
#define INPUT_RPI

#include <stdint.h>
#include "joydrv.h"
#include "global.h"

int iniciarEntradas();

event_t leerEntradas();

#endif