#include <stdio.h>
#include "fsm.h"
#include "termlib.h"


STATE* fsm(STATE *p_tabla_estado,BYTE evento_actual)
{

    printf(RED_TEXT ">>%c<<\n" WHITE_TEXT,evento_actual); //just for test (debug)


   	while (p_tabla_estado -> evento != evento_actual		//Recorre las tablas de estado
		   && p_tabla_estado -> evento != FIN_TABLA)
		++p_tabla_estado;
      (*p_tabla_estado -> p_rut_accion) ();          /*rutina de accion corresondiente*/
      p_tabla_estado=p_tabla_estado -> proximo_estado;   /*siguiente estado*/


      return(p_tabla_estado);

}



