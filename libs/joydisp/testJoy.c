/*
testJoy imprime las coordenadas del joystick. Termina cuando se presiona el switch.
*/

#include <stdio.h>
#include "joydrv.h"
#include "termlib.h"

int main(void)
{
    jcoord_t myCoords;
    joy_init();//inicializo el joystick
    do
    {
        //primero actualizo las coordenadas medidas
        joy_update();
        //luego las guardo en myCoords
        myCoords = joy_get_coord();

        printf("(%4d, %4d)\n" , myCoords.x, myCoords.y);	
        //printf(CYAN_TEXT "(%4d, %4d)\n" , 
        //                           myCoords.x, myCoords.y);

    } while (joy_get_switch() == J_NOPRESS); //mientras no se
                                          //presione el switch

    return 0;
}
