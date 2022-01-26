/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsm.h"

#include "display.h"
#include "game.h"
#include "menu.h"
#include "input.h"
#include "nombre.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*0.5


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/


#pragma region privatePrototypes
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief 
 * 
 * @return void* 
 */
void* thread_input(void* ptr);

/**
 * @brief 
 * 
 * @return void* 
 */
void* thread_display_menu(void* ptr);

/**
 * @brief 
 * 
 * @return void* 
 */
void* thread_tiempo(void* ptr);

/**
 * @brief 
 * 
 * @return void* 
 */
void* thread_autos(void* ptr);

/**
 * @brief 
 * 
 * @return void* 
 */
void* thread_display_juego(void* ptr);

/**
 * @brief 
 * 
 * @return void* 
 */
void* thread_display_ranking(void* ptr);

/**
 * @brief Rutina que hace nada.
 * 
 */
static void do_nothing(void);

/**
 * @brief 
 * 
 */
static void menu_enter(void);

/**
 * @brief 
 * 
 */
static void pasar_a_menu_ppal(void);
/**
 * @brief 
 * 
 */
static void pasar_a_nombre(void);
/**
 * @brief 
 * 
 */
static void pasar_a_dificultad(void);
/**
 * @brief 
 * 
 */
static void pasar_a_ranking(void);
/**
 * @brief 
 * 
 */
static void salir_del_juego(void);

/**
 * @brief Set the dificultad object
 * 
 */
static void set_dificultad(void);
/**
 * @brief 
 * 
 */
static void ranking_enter(void);
/**
 * @brief 
 * 
 */
static void iniciar_juego(void);

/**
 * @brief 
 * 
 */
static void pausar(void);
/**
 * @brief 
 * 
 */
static void continuar(void);
/**
 * @brief 
 * 
 */
static void salir_al_menu(void);

/**
 * @brief 
 * 
 */
static void subir_nivel(void);
/**
 * @brief 
 * 
 */
static void siguiente_nivel(void);

/**
 * @brief 
 * 
 */
static void game_over(void);

/**
 * @brief 
 * 
 * @param num 
 * @param str 
 */
static void ulltoa(uint64_t num, char* str);

#pragma endregion privatePrototypes

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//Puntero al estado actual
static STATE* p2CurrentState = NULL;

//threads a implementar
pthread_t tinput, tdisplaymenu, tdisplayjuego, tdisplayranking, tautos, ttiempo;


#pragma region FSM STATES
/*******************************************************************************
 * FSM STATES
 ******************************************************************************/

//Forward declarations de los estados
extern STATE en_menu_ppal[];
extern STATE menu_ppal_esperando_opcion[];
extern STATE en_dificultad[];
extern STATE viendo_ranking[];
extern STATE poniendo_nombre[];

extern STATE jugando[];
extern STATE pasando_de_nivel[];
extern STATE en_pausa[];
extern STATE en_pausa_esperando_opcion[];
extern STATE en_game_over[];
extern STATE en_game_over_esperando_opcion[];
//Forward declarations de los estados

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
	{CTE_OPCION+3, NULL, salir_del_juego},
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
	{ARRIBA, poniendo_nombre, subirLetra},
	{ABAJO, poniendo_nombre, bajarLetra},
	{DCHA, poniendo_nombre, siguienteLetra},
	{FIN_TABLA, poniendo_nombre, agregarLetra} //Si no coincide el evento con ninguna de las teclas previas, se toam como si se apretase una letra
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
#pragma endregion FSM STATES

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool inicializarFsm(void)
{
	p2CurrentState = en_menu_ppal;
	
	if(!queue_init())
		return false;

    iniciarDisplay();
    iniciarMenu();
    iniciarEntradas();

	fijarTexto("MENU", POS_MSJ_MENU);
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIRTXT};
	setMenu(menu, 4);
	setOpcion(0);

	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
	pthread_create(&tinput, NULL, thread_input, NULL);

	return true;
}

void fsm(event_t evento_actual)
{
	STATE* aux = p2CurrentState;
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
	p2CurrentState = aux -> proximo_estado;   
      
	//Ejecuta la rutina correspondiente
	(*aux -> p_rut_accion) ();
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void* thread_input(void* ptr){
    while(p2CurrentState){
	    event_t entrada = leerEntradas();
	    if(entrada != NADA){
		    queue_insert(entrada);
		}
    }

	return NULL;
}

void* thread_display_menu(void* ptr){
    while((p2CurrentState == en_menu_ppal) || (p2CurrentState == en_dificultad) || (p2CurrentState == en_pausa) || (p2CurrentState == en_game_over)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverOpcionActual();
    }
	queue_insert(CTE_OPCION+getOpcion());

	return NULL;
}

void *thread_tiempo(void* ptr){
	clock_t tiempo = getTiempoInicial(), inicio = getTiempoInicial();
	clock_t limite = getTiempoLimite();
    clock_t ref = clock();
    while((p2CurrentState == jugando) && (tiempo < limite)){
        tiempo = inicio + clock() - ref;
		setTiempo(tiempo);
    }
    queue_insert(TIMEOUT);
	return NULL;
}

void *thread_autos(void* ptr){
	while(p2CurrentState == jugando){
	clock_t meta = clock() + REFRESH_JUGADOR_CLOCKS;
	while(clock() < meta);
	refrescar();
	//printf("agua: %d", getAgua());
	}
	return NULL;
}

void *thread_display_juego(void* ptr){
	reconfigurarDisplayON();

    while(p2CurrentState == jugando)
		actualizarInterfaz();

	reconfigurarDisplayOFF();

	return NULL;
}

void *thread_display_ranking(void* ptr){
	FILE* pFile;
	char linea[100];
	pFile = fopen ("ranking.txt" , "r");
	if (pFile == NULL){
		perror ("mostrarRanking(): Error opening file");
		return NULL;
	}
	int puesto_int = 1;
	char puesto[2], *nombre, *puntos;
	
	while(fgets(linea, 100, pFile) != NULL){
		char* pch = strtok(linea," ");
		nombre = pch;
		ulltoa(puesto_int++, puesto);
		pch = strtok(NULL, " ");
		puntos = pch;
		mostrarPosicion(puesto, nombre, puntos);
	}
	fclose (pFile);
	queue_insert(ENTER);
	return NULL;
}

static void do_nothing(void)
{

}


static void menu_enter(void){
	limpiarDisplay();
	pthread_join(tdisplaymenu, NULL);
}

static void pasar_a_menu_ppal(){
	fijarTexto("MENU", POS_MSJ_MENU);
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIRTXT};
	setMenu(menu, 4);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void pasar_a_ranking(){
	mostrarTexto("RANKING", POS_MSJ_RANKING);

	//crea el archivo, si no lo estaba
	FILE* pFile;
	pFile = fopen ("ranking.txt" , "a");
	if (pFile == NULL){
		perror ("Error creanto archivo de ranking");
	}
	fclose (pFile);

	pthread_create(&tdisplayranking, NULL, thread_display_ranking, NULL);
}

static void salir_del_juego(){
	pthread_join(tinput, NULL);
	pthread_join(tdisplaymenu, NULL);
	destruirMenu();
	limpiarDisplay();
	queue_insert(SALIR);
}

static void ranking_enter(void){
	pthread_join(tdisplayranking, NULL);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}


static void subir_nivel(){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	subirNivel();
	char pasar_str[10] = "NIVEL ";
	char niv_str[3];
	ulltoa(getNivel(), niv_str);
	strcat(pasar_str, niv_str);
	mostrarTexto(pasar_str, POS_MSJ_PASAR);
}		

static void siguiente_nivel(){
	reiniciarNivel();
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}


static void iniciar_juego(void){
	inicializarJuego();
	reconfigurarDisplayOFF();

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

static void pasar_a_nombre(){
	nuevoNombre();
	limpiarDisplay();
	fijarTexto("INGRESE NOMBRE", POS_MSJ_NOMBRE);
}

static void pasar_a_dificultad(){
	fijarTexto("DIFICULTAD", POS_MSJ_DIFICULTAD);
	int menu[3] = {FACIL, NORMAL, DIFICIL};
	setMenu(menu, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void set_dificultad(void){
	p2CurrentState = menu_ppal_esperando_opcion;
	pthread_join(tdisplaymenu, NULL);
	setDificultad(FACIL + getOpcion());
	int menu[4] = {JUGAR, DIFICULTAD, RANKING, SALIRTXT};
	setMenu(menu, 4);
	setOpcion(0);
	p2CurrentState = en_menu_ppal;
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void pausar(void){
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	reconfigurarDisplayON();
	fijarTexto("PAUSA", POS_MSJ_PAUSA);
	int menu[3] = {CONTINUAR, REINICIAR, SALIRTXT};
	setMenu(menu, 3);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void continuar(void){
	pthread_join(tdisplaymenu, NULL);
	limpiarDisplay();
	continuandoJuego();
	reconfigurarDisplayOFF();
	pthread_create(&tdisplayjuego, NULL, thread_display_juego, NULL);
	pthread_create(&tautos, NULL, thread_autos, NULL);
	pthread_create(&ttiempo, NULL, thread_tiempo, NULL);
}

static void salir_al_menu(void){
	pthread_join(tdisplaymenu, NULL);
	limpiarDisplay();
	pasar_a_menu_ppal();
}

static void game_over(void){
	//cambiar_musica
	pthread_join(ttiempo, NULL);
	pthread_join(tautos, NULL);
	pthread_join(tdisplayjuego, NULL);
	uint64_t jugador_puntos = getPuntos();
	if(jugador_puntos > getMaxPuntos()){
		mostrarTexto("NUEVA PUNTUACION ALTA", POS_MSJ_NEW_HI_SCORE);
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
				//fprintf(pFile2, "%s", aux);
				ubicado = 1;
			}
			if(strcmp(nueva_linea, getNombre()) != 0){ //miro si NO es el nombre que ya puse
				strcat(nueva_linea, " ");
				strcat(nueva_linea, pch); //concateno los puntos
				//fprintf(pFile2, "%s", nueva_linea);
			}
		}
		fclose (pFile1);
		fclose (pFile2);
		remove("ranking.txt");
		rename("tmp.txt", "ranking.txt");
	}
	mostrarTexto("FIN DEL JUEGO", POS_MSJ_GAME_OVER);
	int menu[2] = {REINICIAR, SALIRTXT};
	limpiarDisplay();
	setMenu(menu, 2);
	setOpcion(0);
	pthread_create(&tdisplaymenu, NULL, thread_display_menu, NULL);
}

static void ulltoa(uint64_t num, char* str)
{
	uint64_t sum = num;
	int i = 0;
	int digit;
	do
	{
		digit = sum % 10;
		str[i++] = '0' + digit;
		sum /= 10;
	}while (sum);
	str[i--] = '\0';

    int j = 0;
    char ch;
    while(i > j)
    {
        ch = str[i];
        str[i--] = str[j];
        str[j++] = ch;
    }
}
