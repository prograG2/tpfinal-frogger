/*
testDisp enciende todo el display de a un LED por vez
*/

#include <stdio.h>
#include "disdrv.h"
#include "termlib.h"

int main(void)
{
    //inicializa myPoint en (0,0). Recordemos que está arriba a la izquierda.	
    dcoord_t myPoint = {};		
    disp_init();       //inicializa el display
    disp_clear();      //limpia todo el display
    //para cada coordenada en y...
    for (myPoint.y = DISP_MIN; myPoint.y <= (DISP_MAX_Y); myPoint.y++)
    {
        //para cada coordenada en x...
        for ( myPoint.x = DISP_MIN; 
                myPoint.x <= (DISP_MAX_X) ; myPoint.x++)	        {
            // prende el LED en el buffer. Otra opción es:
            // disp_write({i, j}, D_ON);
            disp_write(myPoint, D_ON);
            
            //imprime cuál LED fue encendido
            printf("(%2d,%2d) " , myPoint.x, myPoint.y);
            //printf(YELLOW_TEXT "(%2d,%2d) " ,
            // myPoint.x, myPoint.y);

            //ahora lo vemos en el display
            disp_update();
        }
        printf("\n");
    }
    return 0;
}
