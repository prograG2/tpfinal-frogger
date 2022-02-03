/**
 * @file display.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "../../display.h"
#include "../../ranking.h"

#include "allegro_stuff.h"
#include "game_data.h"

#include <pthread.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define CREDITS_SCROLL_SPEED 1

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static pthread_mutex_t lock;

static int credits_scroll_cont;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool iniciarDisplay()
{
  if (pthread_mutex_init(&lock, NULL) != 0)
    return 1;

  allegro_inits();

  return 0;
}

void actualizarDisplay()
{
}

void limpiarDisplay()
{
}

void mostrarTexto(char *txt, int pos)
{
}

void dejarTexto(char *txt, int pos, bool repetir)
{
}

void cargarRanking(void)
{
  int i = 0;

  int lines = getRankingLineas();
  char **names = getRankingNombres();
  unsigned long long *scores = getRankingPuntos();

  allegro_clear_display();
  for (i = 0; i < lines; i++)
  {
    al_draw_textf(allegro_get_var_font(),
                  al_map_rgb(255, 255, 255),
                  10,
                  100 + i * 20,
                  0,
                  "%s", names[i]);

    al_draw_textf(allegro_get_var_font(),
                  al_map_rgb(255, 255, 255),
                  400,
                  100 + i * 20,
                  0,
                  "%lld", scores[i]);
  }
  al_flip_display();
}

void mostrarRanking(void)
{
}

void cargarCreditos(void)
{
  credits_scroll_cont = 0;
}

void mostrarCreditos(void)
{
  if (allegro_get_var_redraw())
  {

    credits_scroll_cont -= CREDITS_SCROLL_SPEED;
    if (credits_scroll_cont == -CREDITS_SCREEN_FINAL)
      credits_scroll_cont = CREDITS_SCREEN_START;

    allegro_clear_display();
    al_draw_bitmap(sprites.credits, 0, credits_scroll_cont, 0);
    al_flip_display();

    allegro_set_var_redraw(false);
  }
}

void reconfigurarDisplayON(void)
{
  allegro_reinit_display();
}

void reconfigurarDisplayOFF(void)
{
  allegro_deinit_display();
}