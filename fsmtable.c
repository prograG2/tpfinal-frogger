#include <stdio.h>
#include "fsm.h"
#include "fsmtable.h"

extern STATE *p2state;
/*Foward Declarations*/

extern STATE estado_menu_jugar[];
extern STATE estado_menu_dificultad[];
extern STATE estado_menu_ranking[];
extern STATE estado_menu_salir[];
extern STATE estado_ranking[];
extern STATE estado_poner_nombre[];
extern STATE estado_jugando[];
extern STATE estado_pausa_continuar[];
extern STATE estado_pausa_reiniciar[];
extern STATE estado_pausa_salir[];

// prototipos

static void do_nothing(void);
static void menu_arriba (void);
static void menu_abajo (void);
static void jugar_enter(void);
static void dificultad_enter(void);
static void menu_ranking_enter(void);
static void ranking_enter(void);
static void letra_anterior(void);
static void letra_siguiente(void);
static void borrar_letra(void);
static void siguiente_letra(void);
static void guardar_nombre(void);
static void mover_adelante(void);
static void mover_atras(void);
static void mover_izda(void);
static void mover_dcha(void);
static void pausar(void);
static void continuar(void);
static void reiniciar(void);
static void pausa_arriba(void);
static void pausa_abajo(void);
static void do_nothing(void);
static void salir_al_menu(void);


/*** tablas de estado ***/

/*** estado_0 ***/

STATE estado_menu_jugar[]=
{
  	{ENTER, estado_poner_nombre, jugar_enter},
  	{FLECHA_ARRIBA, estado_menu_salir, menu_arriba},
	{FLECHA_ABAJO, estado_menu_dificultad, menu_abajo},
  	{FIN_TABLA, estado_menu_jugar, do_nothing}
};

STATE estado_menu_dificultad[]=
{
  	{ENTER, estado_menu_dificultad, dificultad_enter},
  	{FLECHA_ARRIBA, estado_menu_jugar, menu_arriba},
	{FLECHA_ABAJO, estado_menu_ranking, menu_abajo},
  	{FIN_TABLA, estado_menu_dificultad, do_nothing}
};

STATE estado_menu_ranking[]=
{
  	{ENTER, estado_ranking, menu_ranking_enter},
  	{FLECHA_ARRIBA, estado_menu_dificultad, menu_arriba},
	{FLECHA_ABAJO, estado_menu_salir, menu_abajo},
  	{FIN_TABLA, estado_menu_ranking,do_nothing}
};

STATE estado_menu_salir[]=
{
  	{ENTER, estado_menu_salir, salir},
  	{FLECHA_ARRIBA, estado_menu_ranking, menu_arriba},
	{FLECHA_ABAJO, estado_menu_jugar, menu_abajo},
  	{FIN_TABLA, estado_menu_salir, do_nothing}
};

STATE estado_ranking[]=
{
	{ENTER, estado_menu_ranking, ranking_enter},
	{FIN_TABLA, estado_ranking, do_nothing}
};

STATE estado_poner_nombre[]=
{
	{FLECHA_ARRIBA, estado_poner_nombre, letra_anterior},
	{FLECHA_ABAJO, estado_poner_nombre, letra_siguiente},
	{FLECHA_IZDA, estado_poner_nombre, borrar_letra},
	{FLECHA_DCHA, estado_poner_nombre, siguiente_letra},
	{ENTER, estado_jugando, guardar_nombre},
	{FIN_TABLA, estado_poner_nombre, do_nothing}
};

STATE estado_jugando[]=
{
	{FLECHA_ARRIBA, estado_jugando, mover_adelante},
	{FLECHA_ABAJO, estado_jugando, mover_atras},
	{FLECHA_IZDA, estado_jugando, mover_izda},
	{FLECHA_DCHA, estado_jugando, mover_dcha},
	{ENTER, estado_pausa_continuar, pausar},
	{FIN_TABLA, estado_jugando, do_nothing}
};

STATE estado_pausa_continuar[]=
{
  	{ENTER, estado_jugando, continuar},
  	{FLECHA_ARRIBA, estado_menu_salir, pausa_arriba},
	{FLECHA_ABAJO, estado_menu_reinicar, pausa_abajo},
  	{FIN_TABLA, estado_pausa_continuar, do_nothing}
};

STATE estado_pausa_reiniciar[]=
{
  	{ENTER, estado_jugando, reiniciar},
  	{FLECHA_ARRIBA, estado_menu_continuar, pausa_arriba},
	{FLECHA_ABAJO, estado_menu_salir, pausa_abajo},
  	{FIN_TABLA, estado_pausa_reiniciar, do_nothing}
};

STATE estado_pausa_salir[]=
{
  	{ENTER, estado_menu_jugar, salir_al_menu},
  	{FLECHA_ARRIBA, estado_menu_reiniciar, pausa_arriba},
	{FLECHA_ABAJO, estado_menu_continuar, pausa_abajo},
  	{FIN_TABLA, estado_pausa_salir, do_nothing}
};


//========interfaz=================


STATE *FSM_GetInitState(void)
{
 	return (estado_0);
}



///=========Rutinas de accion===============

/*Incrementa el contador de coincidencias */

static void menu_arriba (void){

}

static void menu_abajo (void){
	
}

static void jugar_enter(void){

}

static void dificultad_enter(void){
	
}

static void menu_ranking_enter(void){
	
}

static void ranking_enter(void){
	
}


static void do_nothing(void){}


