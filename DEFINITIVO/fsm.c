/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include "fsm.h"
#include "queue.h"
#include "util.h"

#if PLATAFORMA == PC
	#include "game_pc.h"
	#include "display_pc.h"
	#include "menu_pc.h"
	#include "threads_pc.h"
#else
	#include "game_rpi.h"
	#include "display_rpi.h"
	#include "menu_rpi.h"
	#include "threads_rpi.h"
    #include "joystick.h"
	Renglon nombreDisp;
#endif


int index, j;
char nombre[50];
=======
#include <string.h>
#include <pthread.h>
#include "global.h"
#include "fsm.h"
#include "util.h"

#if PLATAFORMA == PC
	#include "nombre_pc.h"
	#include "game_pc.h"
	#include "display_pc.h"
	#include "menu_pc.h"
#else
	#include "nombre_rpi.h"
	#include "game_rpi.h"
	#include "display_rpi.h"
	#include "menu_rpi.h"
    #include "joystick.h"
#endif

pthread_t tjoystick, tdisplaymenu, tdisplayjuego, tdisplayranking, tautos, ttiempo;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void *thread_joystick();

void *thread_display_menu();

void *thread_tiempo();

void *thread_autos();
>>>>>>> rpi funcionando

void *thread_display_juego();

void *thread_display_ranking();
/**
 * @brief Rutina que hace nada.
 * 
 */
void do_nothing(void);
<<<<<<< HEAD


void menu_enter(void);

void pasar_a_menu_ppal(void);
void pasar_a_nombre(void);
void pasar_a_dificultad(void);
void pasar_a_ranking(void);
void salir_del_juego(void);

void set_dificultad(void);
void ranking_enter(void);
void subir_letra(void);
void bajar_letra(void);
void siguiente_letra(void);
void agregar_letra(void);
void iniciar_juego(void);

void pausar(void);
void continuar(void);
void reiniciar_juego(void);
void salir_al_menu(void);

=======


void menu_enter(void);

void pasar_a_menu_ppal(void);
void pasar_a_nombre(void);
void pasar_a_dificultad(void);
void pasar_a_ranking(void);
void salir_del_juego(void);

void set_dificultad(void);
void ranking_enter(void);
void iniciar_juego(void);

void pausar(void);
void continuar(void);
void salir_al_menu(void);

>>>>>>> rpi funcionando
void subir_nivel(void);
void siguiente_nivel(void);

void game_over(void);

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
<<<<<<< HEAD
	{CTE_OPCION+3, en_menu_ppal, salir_del_juego},
=======
	{CTE_OPCION+3, NULL, salir_del_juego},
>>>>>>> rpi funcionando
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
	{ENTER, jugando, iniciar_juego},
<<<<<<< HEAD
	{ARRIBA, poniendo_nombre, subir_letra},
	{ABAJO, poniendo_nombre, bajar_letra},
	{DCHA, poniendo_nombre, siguiente_letra},
	{FIN_TABLA, poniendo_nombre, agregar_letra}
=======
	{ARRIBA, poniendo_nombre, subirLetra},
	{ABAJO, poniendo_nombre, bajarLetra},
	{DCHA, poniendo_nombre, siguienteLetra},
	{FIN_TABLA, poniendo_nombre, agregarLetra}
>>>>>>> rpi funcionando
};

STATE jugando[]=
{
	{ENTER, en_pausa, pausar},
	{GAME_OVER, en_game_over, game_over},
	{ARRIBA, jugando, moverAdelante},
	{ABAJO, jugando, moverAtras},
	{IZDA, jugando, moverIzda},
	{DCHA, jugando, moverDcha},
	{CHOCAR, jugando, perderVidaChoque},
	{AGUA, jugando, perderVidaAgua},
	{TIMEOUT, jugando, perderVidaTimeout},
	{META, pasando_de_nivel, subir_nivel}, //Para pasar de nivel
	{FIN_TABLA, jugando, do_nothing}
};

STATE pasando_de_nivel[]=
{
	{ENTER, jugando, siguiente_nivel},
	{FIN_TABLA, pasando_de_nivel, do_nothing}
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
	{CTE_OPCION+1, jugando, iniciar_juego},
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

<<<<<<< HEAD
STATE* fsm(STATE *p_tabla_estado, event_t evento_actual)
{

=======
void fsm(event_t evento_actual)
{
	STATE* aux = p2CurrentState;
>>>>>>> rpi funcionando
	/*
	Mientras el evento actual no coincida con uno "interesante", y mientras no se haya recorrido
	todo el estado...
	*/
	while ((aux -> evento != evento_actual) && (aux -> evento != FIN_TABLA))
	{
		//Verifico con la siguiente posibilidad dentro del mismo estado.
		++aux;
	}
	
	//Pasa al siguiente estado
<<<<<<< HEAD
	STATE* tmp = p_tabla_estado;
	p_tabla_estado = p_tabla_estado -> proximo_estado;   
      
	//Ejecuta la rutina correspondiente
	(*tmp -> p_rut_accion) ();    


	//Devuelve puntero a nuevo estado
	return(p_tabla_estado);
=======
	p2CurrentState = aux -> proximo_estado;   
      
	//Ejecuta la rutina correspondiente
	(*aux -> p_rut_accion) ();
>>>>>>> rpi funcionando
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
<<<<<<< HEAD

void do_nothing(void)
{

}

STATE* fsm_getInitState(void)
{
	srand(time(NULL));
	if(!queue_init())
		return 1;

    iniciarPlataforma();

    #if PLATAFORMA == PC
		al_init();
        al_install_keyboard();
        al_register_event_source(al_queue, al_get_keyboard_event_source());
	#else
		
	#endif
	
    iniciarDisplay();
    iniciarMenu();
    iniciarJoystick();

    //"algo genérico del menu, para ambas plataformas"
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIR};
	setMenu(menu, 4);
	setOpcion(0);

 	return (en_menu_ppal);
}


void menu_enter(void){
	pthread_join(tdisplaymenu, NULL);
    queue_insert(CTE_OPCION+menu.opcion_actual);
}

void pasar_a_menu_ppal(){
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIR};
	setMenu(menu, 4);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

void pasar_a_ranking(){
	pthread_create(&tdisplayranking, NULL, thread_display_ranking, NULL);
}

void salir_del_juego(){
	pthread_join(tdisplaymenu, NULL);
	destruirMenu();
	queue_insert(SALIR);
}

void ranking_enter(void){
	pthread_join(tdisplayranking, NULL);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

void subir_letra(void){
	if(--jugador.nombre[index] < 'A')
		jugador.nombre[index] = 'Z';
	#if PLATAFORMA == PC
		mostrarTexto(jugador.nombre, ALTO/2);
	#else
		reemplazarLetra(nombreDisp, jugador.nombre[index], j);
    	escribirRenglonDisplay(nombre_, POS_MSJ2);
	#endif
}

void bajar_letra(void){

    if(get_jugador_name())
    set_jugador_name(*string, )

	if(++jugador.nombre[index] > 'Z')
		jugador.nombre[index] = 'A';
	#if PLATAFORMA == PC
		mostrarTexto(jugador.nombre, ALTO/2);
	#else
		reemplazarLetra(nombre_, c, j);
    	escribirRenglonDisplay(nombre_, POS_MSJ2);
	#endif
}

void agregar_letra(void){
	if(index == L_MAX-2)
		return;
	char letra[2];
	letra[0] = (char) last_key;
	letra[1] = '\0';
	strcat(jugador.nombre, letra);      //cambiar por agregar caracteres al string que vive acá (en fsm.c)
	index++;
	mostrarTexto(jugador.nombre, ALTO/2);   //cambiar por algún get del nombre
}

void siguiente_letra(void){
	if(index == L_MAX-2)
		return;
	index++;
	jugador.nombre[index] = 'A';
	jugador.nombre[index+1] = '\0';
	#if PLATAFORMA == PC
		mostrarTexto(jugador.nombre, ALTO/2);
	#else
		int resto = (CANT_COLUMNAS-j) - 6; //Considero el peor caso para calcular el espacio
        if(resto < 0){
            renglonShiftIzq(nombreDisp, -resto); //Me corro lo que necesito para que entre la sig letra
            j = CANT_COLUMNAS - 6;
        }
        else  
			j += longitudes[c-'A'] + 1;
		reemplazarLetra(nombreDisp, jugador.nombre[index], j);
    	escribirRenglonDisplay(nombreDisp, POS_MSJ2);
	#endif
}

void subir_nivel(){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	jugador.niv_actual++;
	char pasar_str[10] = "NIVEL ";
	char niv_str[3];
	ulltoa(jugador.niv_actual,niv_str,10);
	strcat(pasar_str, niv_str);
	mostrarTexto(pasar_str, PLATAFORMA == PC? ALTO/2 : POS_MSJ1);
}		

void siguiente_nivel(){
	reiniciar_nivel();
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}


void iniciar_juego(void){
	jugador.puntos = 0;     //cambiar por algo tipo set
	jugador.max_puntos = 0; //cambiar por algo tipo set

    //mandar el string con el nombre que vive en fsm.c al jugador.nombre

	FILE* pFile;
    char linea[100];
    pFile = fopen ("ranking.txt" , "r");
    if (pFile == NULL)
        perror ("ranking.txt: Error opening file");
    while(fgets(linea, 100, pFile) != NULL){
        char* pch = strtok(linea," "); //separo el primer token
        if(strcoll(pch, jugador.nombre) == 0){ //miro si es el nombre que buscaba
            pch = strtok(NULL," "); //separo el segundo token
            jugador.max_puntos = atoll(pch); //guardo la puntuación máxima
            break;
        }
    }
    fclose (pFile);

	jugador.vidas = 0b1111100000000000;
	jugador.niv_actual = 1;
    jugador.puntos = 0;
	reiniciar_nivel();
=======
void *thread_joystick(){
    while(p2CurrentState){
	    event_t joystick = leerJoystick();
	    if(joystick != NO_MOVER){ //Si hay movimiento de joystick
		    queue_insert(joystick);
		}
    }
	return NULL;
}

void *thread_display_menu(){
    while((p2CurrentState == en_menu_ppal) || (p2CurrentState == en_dificultad) || (p2CurrentState == en_pausa) || (p2CurrentState == en_game_over)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverOpcionActual();
    }
	queue_insert(CTE_OPCION+getOpcion());
	return NULL;
}

void *thread_tiempo(){
	clock_t tiempo = getTiempoInicial(), inicio = getTiempoInicial();
	clock_t limite = getTiempoLimite();
    clock_t ref = clock();
    while((p2CurrentState == jugando) && (tiempo < limite)){
        tiempo = inicio + clock() - ref;
		setTiempo(tiempo); //setear la interfaz tambien
    }
    queue_insert(TIMEOUT);
	return NULL;
}

void *thread_autos(){
	while(p2CurrentState == jugando){
	clock_t meta = clock() + REFRESH_JUGADOR_CLOCKS;
	while(clock() < meta);
	refrescarJugador();
	meta = clock() + REFRESH_JUGADOR_CLOCKS;
	while(clock() < meta);
	refrescarJugador();
	refrescarAutos();
	printf("agua: %d", getAgua());
	}
	return NULL;
}

void *thread_display_juego(){
    while(p2CurrentState == jugando)
		actualizarInterfaz();
	return NULL;
}

void *thread_display_ranking(){
	FILE* pFile;
	char linea[100];
	pFile = fopen ("ranking.txt" , "r");
	if (pFile == NULL){
		perror ("mostrarRanking(): Error opening file");
		return NULL;
	}
	int puesto = 1;
	char msj[100];
	
	while(fgets(linea, 100, pFile) != NULL){
		limpiarDisplay();
		char* pch = strtok(linea," ");
		ulltoa(puesto, msj);
		strcat(msj, " ");
		strcat(msj, pch);
		clock_t meta = clock() + SLEEP_CLOCKS;
		while(clock() < meta);
		printf("%s\n", msj);
		mostrarTexto(msj, POS_MSJ1);
		pch = strtok(NULL, " ");
		printf("%s\n", pch);
		mostrarTexto(pch, POS_MSJ2);
	}
	fclose (pFile);
	queue_insert(ENTER);
	return NULL;
}

void do_nothing(void)
{

}

int inicializarFsm(void)
{
	p2CurrentState = en_menu_ppal;
	srand(time(NULL));
	if(!queue_init())
		return 1;

    #if PLATAFORMA == PC
		al_init();
        al_install_keyboard();
        al_register_event_source(al_queue, al_get_keyboard_event_source());
	#else
		
	#endif
	
    iniciarDisplay();
    iniciarMenu();
    iniciarJoystick();

	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIRTXT};
	setMenu(menu, 4);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
	pthread_create(&tjoystick, NULL, thread_joystick, NULL);
	return 0;
}


void menu_enter(void){
	pthread_join(tdisplaymenu, NULL);
}

void pasar_a_menu_ppal(){
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIRTXT};
	setMenu(menu, 4);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

void pasar_a_ranking(){
	pthread_create(&tdisplayranking, NULL, thread_display_ranking, NULL);
}

void salir_del_juego(){
	destruirMenu();
	pthread_join(tjoystick, NULL);
	pthread_join(tdisplaymenu, NULL);
	limpiarDisplay();
	queue_insert(SALIR);
}

void ranking_enter(void){
	pthread_join(tdisplayranking, NULL);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}


void subir_nivel(){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	subirNivel();
	char pasar_str[10] = "NIVEL ";
	char niv_str[3];
	ulltoa(getNivel(), niv_str);
	strcat(pasar_str, niv_str);
	mostrarTexto(pasar_str, POS_MSJ1);
}		

void siguiente_nivel(){
	reiniciarNivel();
>>>>>>> rpi funcionando
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

<<<<<<< HEAD
void pasar_a_nombre(){
	jugador.nombre[0] = 'A';
	jugador.nombre[1] = '\0';
	index = 0;
	limpiarDisplay();
	mostrarTexto("INGRESE NOMBRE", PLATAFORMA == PC? 100 : POS_MSJ1);
}

void pasar_a_dificultad(){
	int menu[3] = {FACIL, NORMAL, DIFICIL};
	setMenu(menu, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

void set_dificultad(void){
	jugador.dificultad = FACIL + menu.opcion_actual;
}

void pausar(void){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	int menu[3] = {CONTINUAR, REINICIAR, SALIR};
=======

void iniciar_juego(void){
	inicializarJuego();

    //mandar el string con el nombre que vive en fsm.c al jugador.nombre

	FILE* pFile;
    char linea[100];
    pFile = fopen ("ranking.txt" , "r");
    if (pFile == NULL)
        perror ("ranking.txt: Error opening file");
    while(fgets(linea, 100, pFile) != NULL){
        char* pch = strtok(linea," "); //separo el primer token
        if(strcoll(pch, getNombre()) == 0){ //miro si es el nombre que buscaba
            pch = strtok(NULL," "); //separo el segundo token
			setMaxPuntos(strtoull(pch, NULL, 10));
            break;
        }
    }
    fclose (pFile);

	reiniciarNivel();
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

void pasar_a_nombre(){
	nuevoNombre();
	limpiarDisplay();
	//mostrarTexto("INGRESE NOMBRE", POS_MSJ1);
}

void pasar_a_dificultad(){
	int menu[3] = {FACIL, NORMAL, DIFICIL};
>>>>>>> rpi funcionando
	setMenu(menu, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

<<<<<<< HEAD
void continuar(void){
	pthread_join(tdisplaymenu, NULL);
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

void salir_al_menu(void){
	pthread_join(tdisplaymenu, NULL);
	pasar_a_menu_ppal();
}

void game_over(void){
	//cambiar_musica
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);

	if(jugador.puntos > jugador.max_puntos){
		mostrarTexto("NUEVA PUNTUACION ALTA", PLATAFORMA == PC? ALTO/2 : POS_MSJ1);
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
	int menu[2] = {REINICIAR, SALIR};
	setMenu(menu, 2);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}
=======
void set_dificultad(void){
	p2CurrentState = menu_ppal_esperando_opcion;
	pthread_join(tdisplaymenu, NULL);
	setDificultad(FACIL + getOpcion());
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIRTXT};
	setMenu(menu, 4);
	setOpcion(0);
	p2CurrentState = en_menu_ppal;
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

void pausar(void){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	int menu[3] = {CONTINUAR, REINICIAR, SALIRTXT};
	setMenu(menu, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

void continuar(void){
	pthread_join(tdisplaymenu, NULL);
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

void salir_al_menu(void){
	pthread_join(tdisplaymenu, NULL);
	pasar_a_menu_ppal();
}

void game_over(void){
	//cambiar_musica
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	uint64_t jugador_puntos = getPuntos();
	if(jugador_puntos > getMaxPuntos()){
		mostrarTexto("NUEVA PUNTUACION ALTA", POS_MSJ1);
		setMaxPuntos(jugador_puntos);

		FILE *pFile1, *pFile2;
		char linea[100];
		char nueva_linea[100];
		pFile1 = fopen("ranking.txt" , "r");
		pFile2 = fopen("tmp.txt", "w");
		if (pFile1 == NULL)
			perror ("game_over(): Error opening file ranking.txt ");
		if (pFile2 == NULL)
			perror ("game_over(): Error opening file tmp.txt ");

		int ubicado = 0;

		while(fgets(linea, 100, pFile1) != NULL){
			char* pch = strtok(linea," "); //separo el nombre
			strcpy(nueva_linea, pch);
			pch = strtok(NULL, " "); //separo los puntos
			uint64_t puntos = strtoull(pch, NULL, 10);

			if(jugador_puntos > puntos && !ubicado){ //ubico la puntuacion donde corresponde
				char aux[100];
				strcpy(aux, getNombre());
				char nueva_puntuacion[25];
				ulltoa(jugador_puntos, nueva_puntuacion);
				strcat(aux, " ");
				strcat(aux, nueva_puntuacion);
				fprintf(pFile2, "%s", aux);
				ubicado = 1;
			}
			if(strcmp(nueva_linea, getNombre()) != 0){ //miro si NO es el nombre que ya puse
				strcat(nueva_linea, " ");
				strcat(nueva_linea, pch); //concateno los puntos
				fprintf(pFile2, "%s", nueva_linea);
			}
		}
		fclose (pFile1);
		fclose (pFile2);
		remove("ranking.txt");
		rename("tmp.txt", "ranking.txt");
	}
	int menu[2] = {REINICIAR, SALIRTXT};
	limpiarDisplay();
	setMenu(menu, 2);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}
>>>>>>> rpi funcionando
