#include "joystick.h"

int prev = NO_MOVER;

int iniciarJoystick(){
    joy_init();
    return 0;
}

static int8_t modulo(int8_t x){
    if (x==-128) return 127; //excepción: caso en el cual -(-128) = -128
    return x >= 0 ? x : -x;
}

event_t leerJoystick(){
    joy_update();
    int act = joy_get_switch();
    if(act == J_PRESS){
        if(prev != J_PRESS){
            prev = J_PRESS;
            return ENTER;
        }
        return NO_MOVER;
    }

    jcoord_t crd = joy_get_coord();

    int umbral;

    if(prev == NO_MOVER)
        umbral = 20;
    else
        umbral = 10;    

    if((crd.y-umbral) > modulo(crd.x)) act = ARRIBA;
    else if((crd.y+umbral) < -(modulo(crd.x))) act = ABAJO;
    else if((crd.x-umbral) > modulo(crd.y)) act = DCHA;
    else if((crd.x+umbral) < -(modulo(crd.y))) act = IZDA;
    else act = NO_MOVER;


    if(act != prev){
        prev = act;
        return act;
    }
  
    return NO_MOVER;
}

