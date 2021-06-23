/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsm.h"
#include <stdio.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Rutina que hace nada.
 * 
 */
static void do_nothing(void);

static void menu_arriba (void);
static void menu_abajo (void);

static void jugar_enter(void);
static void dificultad_enter(void);
static void menu_ranking_enter(void);
static void ranking_enter(void);
static void salir_enter(void);

static void letra_anterior(void);
static void letra_siguiente(void);
static void borrar_letra(void);
static void siguiente_letra(void);
static void guardar_nombre(void);

static void refresh(void);

static void mover_adelante(void);
static void mover_atras(void);
static void mover_izda(void);
static void mover_dcha(void);

static void pausar(void);
static void continuar(void);
static void reiniciar(void);
static void pausa_arriba(void);
static void pausa_abajo(void);
static void salir_al_menu(void);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * FORWARD DECLARATION FOR STATEs
 ******************************************************************************/

extern STATE menu_seleccionando_jugar[];
extern STATE menu_seleccionando_dificultad[];
extern STATE menu_seleccionando_ranking[];
extern STATE menu_seleccionando_salir[];

extern STATE viendo_ranking[];

extern STATE poniendo_nombre[];

extern STATE jugando[];

extern STATE pausa_seleccionando_continuar[];
extern STATE pausa_seleccionando_reiniciar[];
extern STATE pausa_seleccionando_salir[];


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

STATE menu_seleccionando_jugar[]=
{
  	{ENTER, poniendo_nombre, jugar_enter},
  	{ARRIBA, menu_seleccionando_salir, menu_arriba},
	{ABAJO, menu_seleccionando_dificultad, menu_abajo},
  	{FIN_TABLA, menu_seleccionando_jugar, do_nothing}
};

STATE menu_seleccionando_dificultad[]=
{
  	{ENTER, menu_seleccionando_dificultad, dificultad_enter},
  	{ARRIBA, menu_seleccionando_jugar, menu_arriba},
	{ABAJO, menu_seleccionando_ranking, menu_abajo},
  	{FIN_TABLA, menu_seleccionando_dificultad, do_nothing}
};

STATE menu_seleccionando_ranking[]=
{
  	{ENTER, viendo_ranking, menu_ranking_enter},
  	{ARRIBA, menu_seleccionando_dificultad, menu_arriba},
	{ABAJO, menu_seleccionando_salir, menu_abajo},
  	{FIN_TABLA, menu_seleccionando_ranking,do_nothing}
};

STATE menu_seleccionando_salir[]=
{
  	{ENTER, menu_seleccionando_salir, salir_enter},
  	{ARRIBA, menu_seleccionando_ranking, menu_arriba},
	{ABAJO, menu_seleccionando_jugar, menu_abajo},
  	{FIN_TABLA, menu_seleccionando_salir, do_nothing}
};

STATE viendo_ranking[]=
{
	{ENTER, menu_seleccionando_ranking, ranking_enter},
	{FIN_TABLA, viendo_ranking, do_nothing}
};

STATE poniendo_nombre[]=
{
	{ESC, menu_seleccionando_jugar, salir_al_menu},
	{ENTER, jugando, guardar_nombre},
	{FIN_TABLA, poniendo_nombre, do_nothing}
};

STATE jugando[]=
{
	{ARRIBA, jugando, mover_adelante},
	{ABAJO, jugando, mover_atras},
	{IZDA, jugando, mover_izda},
	{DCHA, jugando, mover_dcha},
	{ENTER, pausa_seleccionando_continuar, pausar},
	{REFRESH, jugando, refresh},
	{FIN_TABLA, jugando, do_nothing}
};

STATE pausa_seleccionando_continuar[]=
{
  	{ENTER, jugando, continuar},
  	{ARRIBA, menu_seleccionando_salir, pausa_arriba},
	{ABAJO, pausa_seleccionando_reiniciar, pausa_abajo},
  	{FIN_TABLA, pausa_seleccionando_continuar, do_nothing}
};

STATE pausa_seleccionando_reiniciar[]=
{
  	{ENTER, jugando, reiniciar},
  	{ARRIBA, pausa_seleccionando_continuar, pausa_arriba},
	{ABAJO, menu_seleccionando_salir, pausa_abajo},
  	{FIN_TABLA, pausa_seleccionando_reiniciar, do_nothing}
};

STATE pausa_seleccionando_salir[]=
{
  	{ENTER, menu_seleccionando_jugar, salir_al_menu},
  	{ARRIBA, pausa_seleccionando_reiniciar, pausa_arriba},
	{ABAJO, pausa_seleccionando_continuar, pausa_abajo},
  	{FIN_TABLA, pausa_seleccionando_salir, do_nothing}
};


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

STATE* fsm_getInitState(void)
{
 	return (menu_seleccionando_jugar);
}

STATE* fsm_getCurrentState(void)
{
	return p2CurrentState;
}

STATE* fsm(STATE *p_tabla_estado, event_t evento_actual)
{

	/*
	Mientras el evento actual no coincida con uno "interesante", y mientras no se haya recorrido
	todo el estado...
	*/
	while ((p_tabla_estado -> evento != evento_actual) && (p_tabla_estado -> evento != FIN_TABLA))
	{
		//Verifico con la siguiente posibilidad dentro del mismo estado.
		++p_tabla_estado;
	}
      
	//Ejecuta la rutina correspondiente
	(*p_tabla_estado -> p_rut_accion) ();    

	//Pasa al siguiente estado
	p_tabla_estado = p_tabla_estado -> proximo_estado;   

	//Devuelve puntero a nuevo estado
	return(p_tabla_estado);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void do_nothing(void)
{

}

