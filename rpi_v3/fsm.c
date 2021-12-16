/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsm.h"
#include "menu.h"
#include "display.h"
#include "gamedata.h"
#include "queue.h"
#include "threads.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Rutina que hace nada.
 * 
 */
static void do_nothing(void);

static void menu_enter(void);

static void pasar_a_menu_ppal(void);
static void pasar_a_nombre(void);
static void pasar_a_dificultad(void);
static void pasar_a_ranking(void);
static void salir_del_juego(void);

static void set_dificultad(void);
static void ranking_enter(void);
static void iniciar_juego(void);

static void refresh(void);

static void mover_adelante(void);
static void mover_atras(void);
static void mover_izda(void);
static void mover_dcha(void);

static void pausar(void);
static void continuar(void);
static void reiniciar_juego(void);
static void salir_al_menu(void);

static void refresh(void);
static void perder_vida_choque(void);
static void perder_vida_agua(void);
static void perder_vida_timeout(void);
static void llegar(void);
static void respawn(void);
static void game_over(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


STATE en_menu_ppal[]=
{
	{ENTER, menu_ppal_esperando_opcion, menu_enter},
  	{ARRIBA, en_menu_ppal, subirOpcion},
	{ABAJO, en_menu_ppal, bajarOpcion},
  	{FIN_TABLA, en_menu_ppal, do_nothing}
};

STATE menu_ppal_esperando_opcion[]=
{
	{CTE_OPCION, poniendo_nombre, pasar_a_nombre},
	{CTE_OPCION+1, en_dificultad, pasar_a_dificultad},
	{CTE_OPCION+2, viendo_ranking, pasar_a_ranking},
	{CTE_OPCION+3, en_menu_ppal, salir_del_juego},
	{FIN_TABLA, menu_ppal_esperando_opcion, do_nothing}

};

STATE en_dificultad[]=
{
	{ENTER, en_menu_ppal, set_dificultad},
	{ARRIBA, en_dificultad, subirOpcion},
	{ABAJO, en_dificultad, bajarOpcion},
	{FIN_TABLA, en_dificultad, do_nothing}
};

STATE viendo_ranking[]=
{
	{ENTER, en_menu_ppal, ranking_enter},
	{FIN_TABLA, viendo_ranking, do_nothing}
};

STATE poniendo_nombre[]=
{
	{ESC, en_menu_ppal, pasar_a_menu_ppal},
	{LISTO, jugando, iniciar_juego},
	{FIN_TABLA, poniendo_nombre, do_nothing}
};

STATE jugando[]=
{
	{ENTER, en_pausa, pausar},
	{GAME_OVER, en_game_over, game_over},
	{ARRIBA, jugando, mover_adelante},
	{ABAJO, jugando, mover_atras},
	{IZDA, jugando, mover_izda},
	{DCHA, jugando, mover_dcha},
	{CHOCAR, jugando, perder_vida_choque},
	{AGUA, jugando, perder_vida_agua},
	{TIMEOUT, jugando, perder_vida_timeout},
	{META, jugando, llegar}, //Chqeuear si está libre
	{FIN_TABLA, jugando, do_nothing}
};

STATE en_pausa[]=
{
	{ENTER, en_pausa_esperando_opcion, menu_enter},
	{ARRIBA, en_pausa, subirOpcion},
	{ABAJO, en_pausa, bajarOpcion},
	{FIN_TABLA, en_pausa, do_nothing}
};

STATE en_pausa_esperando_opcion[]=
{
	{CTE_OPCION, jugando, continuar},
	{CTE_OPCION+1, jugando, reiniciar_juego},
	{CTE_OPCION+2, en_menu_ppal, salir_al_menu},
	{FIN_TABLA, en_pausa_esperando_opcion, do_nothing}
};

STATE en_game_over[]=
{
	{ENTER, en_game_over_esperando_opcion, menu_enter},
	{ARRIBA, en_game_over, subirOpcion},
	{ABAJO, en_game_over, bajarOpcion},
	{FIN_TABLA, en_game_over, do_nothing}
};

STATE en_game_over_esperando_opcion[]=
{
	{CTE_OPCION, jugando, iniciar_juego},
	{CTE_OPCION+1, en_menu_ppal, salir_al_menu},
	{FIN_TABLA, en_game_over_esperando_opcion, do_nothing}
};
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

STATE* fsm_getInitState(void)
{
 	return (en_menu_ppal);
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
	
	//Pasa al siguiente estado
	STATE* tmp = p_tabla_estado;
	p_tabla_estado = p_tabla_estado -> proximo_estado;   
      
	//Ejecuta la rutina correspondiente
	(*tmp -> p_rut_accion) ();    


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

static void menu_enter(void){
	pthread_join(tdisplaymenu, NULL);
}

static void pasar_a_menu_ppal(){
	setMenu((int*){JUGAR, DIFICULTAD, RANKING, SALIR}, 4);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void pasar_a_nombre(){
	pthread_create(&tdisplaynombre, NULL, thread_display_nombre, NULL);
}

static void pasar_a_dificultad(){
	setMenu((int*){FACIL, NORMAL, DIFICIL}, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void pasar_a_ranking(){
	pthread_create(&tdisplayranking, NULL, thread_display_ranking, NULL);
}

static void salir_del_juego(){
	pthread_join(tdisplaymenu, NULL);
	destruirMenu();
	queue_insert(SALIR);
}

static void ranking_enter(void){
	pthread_join(tdisplayranking, NULL);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void set_dificultad(void){
	jugador.dificultad = FACIL + menu.opcion_actual;
}

static void salir_del_juego(void){
	queue_insert(SALIR);
}

static void iniciar_juego(void){
	pthread_join(tdisplaynombre, NULL);
	jugador.vidas = 0b1111100000000000;
	jugador.niv_actual = 1;
    jugador.puntos = 0;
	reiniciar_nivel();
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tjugador, NULL, thread_jugador, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

static void reiniciar_nivel(void){
	jugador.ranas = 0b1001001001001001;
	jugador.tiempo_limite = 60*CLOCKS_PER_SEC*(1-0.05*(jugador.dificultad-FACIL));
	jugador.inicio = 0;
	jugador.agua = 0;
	respawn();
}

static void respawn(void){
    jugador.jugador_1 = 0b0000000010000000;
    jugador.jugador_2 = 0b0000000100000000;
	jugador.posicion_sur = CANT_FILAS-1;
	jugador.posicion_oeste = 7;
    int i, j;
    for(i=POS_AUTOS; i<POS_AUTOS+10; i+=2){
        uint16_t carril = 0;
		for(j=0; j<CANT_COLUMNAS;){
			int r = rand();
			if(r & 1){
				if(r & 0b10){
					carril |= jugador.agua? 0b1111 << j : 0b11 << j;
					j += jugador.agua? 6 : 4; //dejo 2 espacios mas
				}
				else{
					carril |= jugador.agua? 0b111111 << j : 0b1111 << j;
					j += jugador.agua? 8 : 6; //dejo 2 espacios mas
				}
			}
			else{
				j += 2; //dejo 2 espacios
			}
		}
		if (jugador.agua)
			carril = ~carril;
		jugador.mapa[i] = carril;
		jugador.mapa[i+1] = carril;
    }
}

static void mover_adelante(void){
	jugador.posicion_sur--;
	if(jugador.posicion_sur == 3)
		queue_insert(META);
}

static void mover_atras(void){
	if(jugador.posicion_sur < 15){
		jugador.posicion_sur++;
	}
}

static void mover_izda(void){
	if(jugador.posicion_oeste > 0){
		jugador.posicion_oeste--;
		jugador.jugador_1 <<= 1;
		jugador.jugador_2 <<= 1;
	}
}

static void mover_dcha(void){
	if(jugador.posicion_oeste < 14){
		jugador.posicion_oeste++;
		jugador.jugador_1 >>= 1;
		jugador.jugador_2 >>= 1;
	}
}

static void pausar(void){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tjugador, NULL);
	pthread_join(tdisplayjuego, NULL);
	setMenu((int*){CONTINUAR, REINICIAR, SALIR}, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void continuar(void){
	pthread_join(tdisplaymenu, NULL);
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tjugador, NULL, thread_jugador, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

static void salir_al_menu(void){
	pthread_join(tdisplaymenu, NULL);
	pasar_a_menu_ppal();
}

static void perder_vida_choque(void){
	//ruido1
	jugador.vidas--;
	jugador.inicio = 0;
	jugador.agua = 0;
	respawn();
}

static void perder_vida_agua(void){
	//ruido2
	jugador.vidas--;
	jugador.inicio = 0;
	jugador.agua = 0;
	respawn();
}

static void perder_vida_timeout(void){
	//sin ruido?
	jugador.vidas--;
	jugador.inicio = 0;
	jugador.agua = 0;
	respawn();
}

static void game_over(void){
	//cambiar_musica
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tjugador, NULL);
	pthread_join(tdisplayjuego, NULL);

	if(jugador.puntos > jugador.max_puntos){
		mostrarTexto("NUEVA PUNTUACION ALTA", POS_MSJ1);
		jugador.max_puntos = jugador.puntos;

		FILE *pFile1, *pFile2;
    	char linea[100];
		char nueva_linea[100] = {0};
    	pFile1 = fopen ("ranking.txt" , "r");
		pFile2 = fopen("tmp.txt", "w");
    	if (pFile1 == NULL)
        	perror ("game_over(): Error opening file ranking.txt ");
		if (pFile2 == NULL)
        	perror ("game_over(): Error opening file tmp.txt ");

   		while(fgets(linea, 100, pFile1) != NULL){
        	char* pch = strtok(linea," "); //separo el primer token
			strcpy(nueva_linea, pch); //copio el nombre
        	if(strcoll(pch, jugador.nombre) == 0){ //miro si es el nombre que buscaba
				pch = strtok(NULL, " "); //separo el segundo token
            	char nueva_puntuacion[25] = {0};
				lltoa(jugador.max_puntos, nueva_puntuacion, 10);
            	strcat(nueva_linea, " "); //guardo la puntuación máxima
				strcat(nueva_linea, nueva_puntuacion);
        	}
			else{
				pch = strtok(NULL, " ");
				strcat(nueva_linea, " "); //copio los puntos
				strcat(nueva_linea, pch);
			}
			fprintf(pFile2, "%s", nueva_linea);
    	}
    	fclose (pFile1);
		fclose (pFile2);
		remove("ranking.txt");
		rename("tmp.txt", "ranking.txt");
	}

	setMenu((int*){REINICIAR, SALIR}, 2);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void llegar(void){
	if(!jugador.agua){
		jugador.agua = 1;
		jugador.mapa[2] = jugador.ranas;
		jugador.mapa[3] = jugador.ranas;
		respawn();
	}
	else{
		
	}

}
