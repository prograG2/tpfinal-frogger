/**
 * @file 	game.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 * @brief 	Archivo para manejar la información del juego
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../game.h"

#include "bitmap.h"
#include "../../display.h"
#include "../../sound.h"
#include "../../queue.h"

#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define POS_AUTOS_INICIO 4
#define POS_AUTOS_FIN 13
#define CANT_CARRILES 5
#define SPAWN_MOVIMIENTOS 64
#define L_MAX 64

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static struct
{
  char nombre_jugador[L_MAX];
  int dificultad;
  int niv_actual;
  int jugador_posicion_sur;
  int jugador_posicion_oeste;
  uint16_t vidas;
  uint16_t ranas;
  uint16_t jugador_1;
  uint16_t jugador_2;
  unsigned long long puntos;
  unsigned long long max_puntos;
  bool jugando;
  bool agua;
  bool refresco_jugador;
  bool refresco_autos;
  bool pre_timeout; // para avisar si queda poco tiempo
  bool timeout;
  clock_t tiempo;
  clock_t tiempo_inicio;
  clock_t tiempo_referencia;
  clock_t tiempo_refresco_jugador;
  clock_t tiempo_refresco_autos;
  clock_t tiempo_alerta;
  matriz_t mapa;
  union
  {
    uint32_t completo;
    struct
    {
      uint16_t derecho;
      uint16_t izquierdo;
    };
  } carril[CANT_CARRILES];
} juego;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

extern matriz_t disp_matriz;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void reiniciarTimer();

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_t ttiempo;

static void *threadTiempo(void *ptr);

static bool instrucciones_dadas = false;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void setNombre(char *nombre)
{
  strcpy(juego.nombre_jugador, nombre);
}

void setMaxPuntos(unsigned long long max)
{
  juego.max_puntos = max;
}

void limpiarMapa()
{
}

void moverCarrriles(int x)
{
  for (int i = 0; i < 5; i++)
    juego.carril[i].completo <<= x; // movimiento de autos/troncos
  if (juego.agua && juego.jugador_posicion_sur < CANT_FILAS - 2 && juego.jugador_posicion_sur > 4)
    moverIzda(); // animación de movimiento de jugador con los troncos
}

void spawnearAutos()
{
  int i;
  for (i = 0; i < 5; i++)
  {
    if (juego.agua)
    {
      if (!(juego.carril[i].completo & 0b1111111111) && !(rand() % 15))
        juego.carril[i].completo |= 0b111111;
      else if (!(juego.carril[i].completo & 0b111111111111) && !(rand() % 30))
        juego.carril[i].completo |= 0b11111111;
    }
    else
    {
      if (!(juego.carril[i].completo & 0b111111) && !(rand() % 15))
        juego.carril[i].completo |= 0b11;
      else if (!(juego.carril[i].completo & 0b11111111) && !(rand() % 30))
        juego.carril[i].completo |= 0b1111;
    }
  }
}

void actualizarMapa()
{
  if (juego.agua)
  {
    juego.mapa[2] = juego.ranas;
    juego.mapa[3] = juego.ranas;
  }
  else
  {
    juego.mapa[2] = 0;
    juego.mapa[3] = 0;
  }
  for (int i = 0; i < 5; i++)
  {
    juego.mapa[POS_AUTOS_INICIO + 2 * i] = juego.carril[i].izquierdo;
    juego.mapa[POS_AUTOS_INICIO + 2 * i + 1] = juego.carril[i].izquierdo;
  }
}

void refrescar()
{
  if (juego.refresco_autos)
  {
    moverCarrriles(1);
    spawnearAutos();
    juego.refresco_autos = false;
  }
  if (juego.refresco_jugador)
  {
    uint16_t tmp = juego.jugador_1;
    juego.jugador_1 = juego.jugador_2;
    juego.jugador_2 = tmp;
    juego.refresco_jugador = false;
  }
}

bool tiempoRefrescoEntidades(void)
{
  return juego.refresco_jugador || juego.refresco_autos;
}

void setDificultad(int dificultad)
{
  juego.dificultad = dificultad;
}

char *getNombre()
{
  return juego.nombre_jugador;
}
unsigned long long getPuntos()
{
  return juego.puntos;
}

unsigned long long getMaxPuntos()
{
  return juego.max_puntos;
}

int getNivel()
{
  return juego.niv_actual;
}

void reiniciarNivel()
{
  juego.ranas = 0b1001001001001001;
  juego.agua = false;
  respawn();
  reiniciarTimer();
  reanudarJuego();
}

void respawn()
{
  juego.jugador_posicion_sur = CANT_FILAS - 1;
  if (!juego.agua)
  {
    juego.jugador_1 = 0b0000000100000000;
    juego.jugador_2 = 0b0000000010000000;
    juego.jugador_posicion_oeste = 7;
  }

  for (int i = 0; i < CANT_CARRILES; i++)
    juego.carril[i].completo = 0;
  limpiarMatriz(juego.mapa);

  for (int i = 0; i < SPAWN_MOVIMIENTOS; i++)
  {
    moverCarrriles(1);
    spawnearAutos();
  }

  actualizarMapa();
}

void moverAdelante()
{
  if (juego.jugador_posicion_sur > 3)
    juego.jugador_posicion_sur--;
  else
  {
    if (!juego.agua) // si voy por la mitad de la ronda
    {
      juego.agua = true;
      respawn();
    }
    else
    {
      juego.puntos += 500 + 250 * (juego.dificultad);
      juego.ranas |= juego.jugador_1 | juego.jugador_2;
      if (juego.ranas == 0b1111111111111111) // si completé el nivel
      {
        juego.puntos += 1000 + 250 * (juego.dificultad);
        pausarJuego();
        juego.niv_actual++;
        reproducirEfecto(EFECTO_NIVEL_COMPLETO);
        reiniciarNivel();
      }
      else // si completé la ronda pero aún falta completar el nivels
      {
        juego.agua = false;
        reproducirEfecto(EFECTO_META);
        respawn();
        juego.tiempo += CLOCKS_PER_SEC * 10;
      }
    }
  }
}

void moverAtras()
{
  if (juego.jugador_posicion_sur < 15)
    juego.jugador_posicion_sur++;
}

void moverIzda()
{
  if (juego.jugador_posicion_oeste > 0)
  {
    juego.jugador_posicion_oeste--;
    juego.jugador_1 <<= 1;
    juego.jugador_2 <<= 1;
  }
}

void moverDcha()
{
  if (juego.jugador_posicion_oeste < 14)
  {
    juego.jugador_posicion_oeste++;
    juego.jugador_1 >>= 1;
    juego.jugador_2 >>= 1;
  }
}

void perderVida()
{
  juego.agua ? reproducirEfecto(EFECTO_AHOGADO) : reproducirEfecto(EFECTO_IMPACTO);
  juego.agua = false;
  juego.vidas <<= 1;
  if (!juego.vidas)
    queueInsertar(GAME_OVER);
  else
    respawn();
}

void inicializarJuego()
{
  juego.puntos = 0;
  juego.niv_actual = 1;
  juego.vidas = 0b1110000000000000;
  if (!instrucciones_dadas)
  {
    reproducirEfecto(EFECTO_INSTRUCCIONES);
    clock_t meta = clock() + CLOCKS_PER_SEC*20;
    while(clock() < meta);
    instrucciones_dadas = true;
  }
}

void reiniciarTimer()
{
  juego.tiempo_inicio = CLOCKS_PER_SEC * (150 - (2 * (juego.dificultad + juego.niv_actual)));
  juego.tiempo = juego.tiempo_inicio;
  juego.tiempo_referencia = juego.tiempo_inicio;
  juego.tiempo_refresco_autos = CLOCKS_PER_SEC * (1 - 0.05 * (2 * (juego.dificultad + juego.niv_actual - 1)));
  juego.tiempo_refresco_jugador = CLOCKS_PER_SEC >> 1;
  juego.tiempo_alerta = CLOCKS_PER_SEC * 15;
  juego.refresco_autos = false;
  juego.refresco_jugador = false;
  juego.timeout = false;
  juego.pre_timeout = false;
}

void pausarJuego()
{
  juego.jugando = false;
  pthread_join(ttiempo, NULL);
}

void actualizarInterfaz()
{
  actualizarMapa();
  copiarMatriz(disp_matriz, juego.mapa);
  disp_matriz[0] = juego.vidas;

  // algoritmo para convertir el tiempo al indicador de 16 bits por aproximaciones sucesivas
  clock_t acc = 0, frac = juego.tiempo_inicio >> 1;
  uint16_t tiempo_bits = 0;
  int bit_de_referencia = 0b0000000000000001;
  int j;
  for (j = 8; j; j >>= 1, frac >>= 1)
  {
    if (juego.tiempo > (acc + frac))
    {
      acc += frac;
      bit_de_referencia <<= j;
      tiempo_bits |= bit_de_referencia - 1; // hago 1 todos los bits menos significativos que el de referencia
    }
  }

  disp_matriz[1] = tiempo_bits;

  disp_matriz[(juego.jugador_posicion_sur) - 1] |= juego.jugador_1;
  disp_matriz[juego.jugador_posicion_sur] |= juego.jugador_2;

  actualizarDisplay();

  if ((juego.mapa[(juego.jugador_posicion_sur) - 1]) & juego.jugador_1 || (juego.mapa[(juego.jugador_posicion_sur)]) & juego.jugador_2)
    perderVida();

  if (juego.timeout)
    queueInsertar(GAME_OVER);
}

void reanudarJuego(void)
{
  juego.jugando = true;
  pthread_create(&ttiempo, NULL, threadTiempo, NULL);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void *threadTiempo(void *ptr)
{
  clock_t ref = clock();
  clock_t ref_autos = ref + juego.tiempo_refresco_autos, ref_jugador = ref + juego.tiempo_refresco_jugador;
  while (juego.jugando)
  {
    if (!(juego.timeout))
    {
      clock_t tiempo = clock();
      juego.tiempo = juego.tiempo_referencia - (tiempo - ref);
      juego.timeout = juego.tiempo <= 0;
      if (!juego.pre_timeout && juego.tiempo <= juego.tiempo_alerta)
      {
        juego.pre_timeout = true;
        reproducirEfecto(EFECTO_POCO_TIEMPO);
      }
      if (tiempo > ref_autos)
      {
        juego.refresco_autos = true;
        ref_autos = tiempo + juego.tiempo_refresco_autos;
      }
      if (tiempo > ref_jugador)
      {
        juego.refresco_jugador = true;
        ref_jugador = tiempo + juego.tiempo_refresco_jugador;
      }
    }
    else
      ref = clock();
  }

  juego.tiempo_referencia = juego.tiempo;

  return NULL;
}