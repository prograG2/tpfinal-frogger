/**
 * @file 	fsm.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo fsm.
 * 			Administra la máquina de estados, siendo el engine del juego.
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "fsm.h"

#include "display.h"
#include "game.h"
#include "menu.h"
#include "input.h"
#include "nombre.h"
#include "sound.h"
#include "ranking.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

// Codigo para indicar que se llego al final de la tabla de estados
#define FIN_TABLA 0xFF

// Para offsetear estados relativos al menu
#define CTE_OPCION 100

// Delay en us que fixea consumo de CPU
#define FIX_CPU_USAGE_SLEEP_US 500

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct state_diagram_edge STATE;

// Estructura genérica de un estado de la FSM.
struct state_diagram_edge
{
  event_t evento;
  STATE *proximo_estado;
  void (*p_rut_accion)(void);
};

#pragma region privatePrototypes
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief	Thread que se ejecuta desde el inicio de la fsm hasta el cierre
 * 			del programa. Analiza constantemente las entradas externas.
 *
 * @return void*
 */
static void *threadInput(void *ptr);

/**
 * @brief	Thread sobre el cual corre el juego en sí, luego de ingresar
 * 			el nombre.
 *
 * @return void*
 */
static void *threadJuego(void *ptr);

/**
 * @brief	Thread que se ejecuta al estar mostrando el ranking.
 *
 * @return void*
 */
static void *threadDisplayRanking(void *ptr);

/**
 * @brief	Thread que se ejecuta al estar mostrando los creditos.
 *
 * @return void*
 */
static void *threadDisplayCreditos(void *ptr);

/**
 * @brief	Rutina que hace nada. Para mantener la estructura
 * 			de la fsm.
 *
 */
static void do_nothing(void);

/**
 * @brief	Rutina que se ejecuta al presionar enter.
 *
 */
static void procesar_enter_menu(void);

/**
 * @brief	Rutina que se ejecuta al ir al menu principal.
 *
 */
static void ir_a_menu_ppal(void);

/**
 * @brief	Rutina que se ejecuta al pasar a ingresar nombre.
 *
 */
static void ir_a_poniendo_nombre(void);

/**
 * @brief	Rutina que se ejecuta al pasar a seleccionar dificultad.
 *
 */
static void ir_a_seleccionando_dificultad(void);

/**
 * @brief	Rutina que se ejecuta al pasar a ver ranking.
 *
 */
static void ir_a_viendo_ranking(void);

/**
 * @brief	Rutina que se ejecuta al pasar a ver creditos.
 *
 */
static void ir_a_viendo_creditos(void);

/**
 * @brief	Rutina que se ejecuta al finalizar el programa.
 *
 */
static void salir_del_juego(void);

/**
 * @brief 	Rutina que se ejecuta al seleccionar una dificultad.
 *
 */
static void procesar_enter_dificultad(void);

/**
 * @brief	Rutina que se ejecuta al presionar enter en el ranking.
 *
 */
static void procesar_enter_ranking(void);

/**
 * @brief	Rutina que se ejecuta al presionar enter en los creditos.
 *
 */
static void procesar_enter_creditos(void);

/**
 * @brief	Rutina que se ejecuta al iniciar el juego en sí.
 *
 */
static void iniciar_juego(void);

/**
 * @brief	Rutina que se ejecuta al pausar el juego.
 *
 */
static void pausar(void);

/**
 * @brief	Rutina que se ejecuta al continuar el juego luego
 * 			de una pausa.
 *
 */
static void continuar(void);

/**
 * @brief	Rutina que se ejecuta cuando se pierde el juego.
 *
 */
static void procesar_game_over(void);

#pragma endregion privatePrototypes

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Puntero al estado actual
static STATE *p2CurrentState = NULL;

// Threads implementados
static pthread_t tinput, tjuego, tdisplayranking, tdisplaycreditos;

#pragma region FSM STATES
/*******************************************************************************
 * FSM STATES
 ******************************************************************************/

// Forward declarations de los estados
extern STATE en_menu_ppal[];
extern STATE seleccionando_dificultad[];
extern STATE viendo_ranking[];
extern STATE viendo_creditos[];
extern STATE poniendo_nombre[];

extern STATE jugando[];
extern STATE en_pausa[];
extern STATE en_game_over[];
// Forward declarations de los estados

STATE en_menu_ppal[] =
    {
        {ENTER, en_menu_ppal, procesar_enter_menu},
        {ARRIBA, en_menu_ppal, subirOpcion},
        {ABAJO, en_menu_ppal, bajarOpcion},
        {FORCE_SALIR, NULL, salir_del_juego},
        {CTE_OPCION, poniendo_nombre, ir_a_poniendo_nombre},
        {CTE_OPCION + 1, seleccionando_dificultad, ir_a_seleccionando_dificultad},
        {CTE_OPCION + 2, viendo_ranking, ir_a_viendo_ranking},
        {CTE_OPCION + 3, viendo_creditos, ir_a_viendo_creditos},
        {CTE_OPCION + 4, NULL, salir_del_juego},
        {FIN_TABLA, en_menu_ppal, do_nothing}};

STATE seleccionando_dificultad[] =
    {
        {ENTER, en_menu_ppal, procesar_enter_dificultad},
        {ARRIBA, seleccionando_dificultad, subirOpcion},
        {ABAJO, seleccionando_dificultad, bajarOpcion},
        {FORCE_SALIR, NULL, salir_del_juego},
        {FIN_TABLA, seleccionando_dificultad, do_nothing}};

STATE viendo_ranking[] =
    {
        {ENTER, en_menu_ppal, procesar_enter_ranking},
        {FORCE_SALIR, NULL, salir_del_juego},
        {FIN_TABLA, viendo_ranking, do_nothing}};

STATE viendo_creditos[] =
    {
        {ENTER, en_menu_ppal, procesar_enter_creditos},
        {FORCE_SALIR, NULL, salir_del_juego},
        {FIN_TABLA, viendo_creditos, do_nothing}};

STATE poniendo_nombre[] =
    {
        {ESC, en_menu_ppal, ir_a_menu_ppal},
        {ENTER, jugando, iniciar_juego},
        {ARRIBA, poniendo_nombre, subirLetra},
        {ABAJO, poniendo_nombre, bajarLetra},
        {DCHA, poniendo_nombre, siguienteLetra},
        {FORCE_SALIR, NULL, salir_del_juego},
        {FIN_TABLA, poniendo_nombre, agregarLetra} // Si no coincide el evento con ninguna de las teclas previas, se toam como si se apretase una letra
};

STATE jugando[] =
    {
        {ENTER, en_pausa, pausar},
        {GAME_OVER, en_game_over, procesar_game_over},
        {ARRIBA, jugando, moverAdelante},
        {ABAJO, jugando, moverAtras},
        {IZDA, jugando, moverIzda},
        {DCHA, jugando, moverDcha},
        {FORCE_SALIR, NULL, salir_del_juego},
        {FIN_TABLA, jugando, do_nothing}};

STATE en_pausa[] =
    {
        {ENTER, en_pausa, procesar_enter_menu},
        {ARRIBA, en_pausa, subirOpcion},
        {ABAJO, en_pausa, bajarOpcion},
        {FORCE_SALIR, NULL, salir_del_juego},
        {CTE_OPCION, jugando, continuar},
        {CTE_OPCION + 1, jugando, iniciar_juego},
        {CTE_OPCION + 2, en_menu_ppal, ir_a_menu_ppal},
        {FIN_TABLA, en_pausa, do_nothing}};

STATE en_game_over[] =
    {
        {ENTER, en_game_over, procesar_enter_menu},
        {ARRIBA, en_game_over, subirOpcion},
        {ABAJO, en_game_over, bajarOpcion},
        {FORCE_SALIR, NULL, salir_del_juego},
        {CTE_OPCION, jugando, iniciar_juego},
        {CTE_OPCION + 1, en_menu_ppal, ir_a_menu_ppal},
        {FIN_TABLA, en_game_over, do_nothing}};

#pragma endregion FSM STATES8

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool inicializarFsm(void)
{
  p2CurrentState = en_menu_ppal;

  srand(time(NULL));

  iniciarDisplay();
  iniciarMenu();
  iniciarEntradas();
  iniciarSonido();

  iniciarRanking();

  ir_a_menu_ppal();

  pthread_create(&tinput, NULL, threadInput, NULL);

  return true;
}

void fsm(event_t evento_actual)
{
  STATE *aux = p2CurrentState;
  /*
    Mientras el evento actual no coincida con uno "interesante", y mientras no se haya recorrido
    todo el estado...
    */
  while ((aux->evento != evento_actual) && (aux->evento != FIN_TABLA))
    // Verifico con la siguiente posibilidad dentro del mismo estado.
    ++aux;

  // Pasa al siguiente estado
  p2CurrentState = aux->proximo_estado;

  // Ejecuta la rutina correspondiente
  (*aux->p_rut_accion)();
}

void fixHighCpuUsage(void)
{
  usleep(FIX_CPU_USAGE_SLEEP_US);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void *threadInput(void *ptr)
{
  while (p2CurrentState)
  {
    event_t entrada = leerEntradas();
    if (entrada != NADA)
      queueInsertar(entrada);

    fixHighCpuUsage();
  }

  return NULL;
}

static void *threadJuego(void *ptr)
{

  reconfigurarDisplayON();

  srand(time(NULL));

  while (p2CurrentState == jugando)
  {
    if (tiempoRefrescoEntidades())
      refrescar();

    actualizarInterfaz();

    fixHighCpuUsage();
  }

  pausarJuego();

  reconfigurarDisplayOFF();

  return NULL;
}

static void *threadDisplayRanking(void *ptr)
{
  reconfigurarDisplayON();

  cargarRanking();

  while (p2CurrentState == viendo_ranking)
    mostrarRanking();

  limpiarDisplay();

  reconfigurarDisplayOFF();

  return NULL;
}

static void *threadDisplayCreditos(void *ptr)
{
  reconfigurarDisplayON();

  cargarCreditos();

  while (p2CurrentState == viendo_creditos)
  {
    mostrarCreditos();
    fixHighCpuUsage();
  }

  reconfigurarDisplayOFF();

  return NULL;
}

static void do_nothing(void)
{
}

static void procesar_enter_menu(void)
{
  reproducirEfecto(EFECTO_MENU_ENTER);
  queueInsertar(CTE_OPCION + getOpcion());
}

static void ir_a_menu_ppal()
{
  limpiarDisplay();
  dejarTexto("MENU", POS_MSJ_MENU, true);
  reproducirMusica(MUSICA_MENU_PPAL);
  int menu[5] = {JUGAR, DIFICULTAD, RANKING, CREDITOS, SALIRTXT};
  setMenu(menu, 5);
  setOpcion(0);
}

static void ir_a_viendo_ranking()
{
  limpiarDisplay();
  reconfigurarDisplayOFF();
  reproducirMusica(MUSICA_RANKING);
  pthread_create(&tdisplayranking, NULL, threadDisplayRanking, NULL);
}

static void ir_a_viendo_creditos(void)
{
  limpiarDisplay();
  reconfigurarDisplayOFF();
  reproducirMusica(MUSICA_CREDITOS);
  pthread_create(&tdisplaycreditos, NULL, threadDisplayCreditos, NULL);
}

static void salir_del_juego()
{
  pthread_join(tinput, NULL);
  pausarMusica();
  reproducirEfecto(EFECTO_SALIENDO);
  sleep(2);
  destruirMenu();
  destruirSonido();
  desiniciarRanking();
  limpiarDisplay();
  queueInsertar(SALIR);
}

static void procesar_enter_ranking(void)
{
  pthread_join(tdisplayranking, NULL);
  reconfigurarDisplayON();
  ir_a_menu_ppal();
}

static void procesar_enter_creditos(void)
{
  pthread_join(tdisplaycreditos, NULL);
  reconfigurarDisplayON();
  ir_a_menu_ppal();
}

static void iniciar_juego(void)
{
  limpiarDisplay();
  char *nombreJugador = devolverNombre();
  if (nombreJugador == NULL)
    setNombre(DEFAULT_PLAYER_NAME);
  else if (nombreJugador[0] == 0)
    setNombre(DEFAULT_PLAYER_NAME);
  else
    setNombre(nombreJugador);

  if (verificarJugadorRanking(getNombre()))
    setMaxPuntos(getJugadorRankingPuntos(getNombre()));

  inicializarJuego();
  reconfigurarDisplayOFF();

  reproducirMusica(MUSICA_JUGANDO);

  reiniciarNivel();
  pthread_create(&tjuego, NULL, threadJuego, NULL);
}

static void ir_a_poniendo_nombre()
{
  limpiarDisplay();
  dejarTexto("INGRESE NOMBRE", POS_MSJ_NOMBRE, true);
  nuevoNombre();
}

static void ir_a_seleccionando_dificultad()
{
  limpiarDisplay();
  dejarTexto("DIFICULTAD", POS_MSJ_DIFICULTAD, true);
  int menu[3] = {FACIL, NORMAL, DIFICIL};
  setMenu(menu, 3);
  setOpcion(0);
}

static void procesar_enter_dificultad(void)
{
  setDificultad(getOpcion());
  reproducirEfecto(EFECTO_MENU_ENTER);
  ir_a_menu_ppal();
}

static void pausar(void)
{
  limpiarDisplay();
  pthread_join(tjuego, NULL);
  reproducirMusica(MUSICA_MENU_PAUSA);
  reconfigurarDisplayON();
  dejarTexto("PAUSA", POS_MSJ_PAUSA, true);
  int menu[3] = {CONTINUAR, REINICIAR, SALIRTXT};
  setMenu(menu, 3);
  setOpcion(0);
}

static void continuar(void)
{
  limpiarDisplay();
  reconfigurarDisplayOFF();
  reproducirMusica(MUSICA_JUGANDO);
  reanudarJuego();
  pthread_create(&tjuego, NULL, threadJuego, NULL);
}

static void procesar_game_over(void)
{
  pthread_join(tjuego, NULL);

  limpiarDisplay();

  reproducirMusica(MUSICA_GAME_OVER);
  reconfigurarDisplayON();

  unsigned long long jugador_puntos = getPuntos();

  if (jugador_puntos > getMaxPuntos())
  {
    reproducirEfecto(EFECTO_NUEVO_MAX_SCORE);

    mostrarTexto("NUEVA PUNTUACION ALTA", POS_MSJ_NEW_HI_SCORE);
    setMaxPuntos(jugador_puntos);

    actualizarRanking(getNombre(), getMaxPuntos());
  }

  mostrarTexto("FIN DEL JUEGO", POS_MSJ_GAME_OVER);
  int menu[2] = {REINICIAR, SALIRTXT};
  limpiarDisplay();
  setMenu(menu, 2);
  setOpcion(0);
}
