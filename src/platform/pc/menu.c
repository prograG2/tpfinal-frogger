/**
 * @file menu.c
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

#include "../../menu.h"
#include "../../sound.h"

#include "allegro_stuff.h"
#include "geometry.h"
#include "game_data.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define STATS_X_COORD 20
#define STATS_Y_COORD_START (DISPLAY_H / 2 + 50)

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct
{
  int actual_state;
  int max_states;
} window_t;

typedef struct
{
  window_t window[MENU_WINDOW_MAX];

  int actual_window;

} menu_t;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa el menu
 *
 */
static void inicializarMenu(void);

/**
 * @brief Dibuja menu
 *
 */
static void renderizarMenu(void);

/**
 * @brief Muestra nombre del jugador y score en el menu de pausa o gameover
 *
 */
static void show_stats(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static menu_t menu;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void iniciarMenu(void)
{
  inicializarMenu();
}

void destruirMenu(void)
{
  allegro_deinits();
}

void setMenu(int *a, unsigned int size)
{
  switch (a[0])
  {
  // menu principal (JUGAR, DIFICULTAD, RANKING, SALIRTXT)
  case JUGAR:
    menu.actual_window = MENU_WINDOW_HOME;

    break;

  // menu dificultades (FACIL, NORMAL, DIFICIL)
  case FACIL:
    menu.actual_window = MENU_WINDOW_DIFFICULTY;

    break;

  // menu pausa (CONTINUAR, REINICIAR, SALIRTXT)
  case CONTINUAR:
    menu.actual_window = MENU_WINDOW_PAUSE;
    allegro_set_rick_flag(false);

    break;

  // menu game over (REINICIAR, SALIRTXT)
  case REINICIAR:
    menu.actual_window = MENU_WINDOW_GAME_OVER;

    break;

  default:
    break;
  }
}

void setOpcion(int opc)
{
  // Seleccina uno de los botones del menu actual
  menu.window[menu.actual_window].actual_state = opc;

  renderizarMenu();
}

int getOpcion(void)
{
  return (menu.window[menu.actual_window].actual_state);
}

void subirOpcion(void)
{
  int *actual_option = &menu.window[menu.actual_window].actual_state;
  int *max_option = &menu.window[menu.actual_window].max_states;

  (*actual_option)--;

  if (*actual_option < 0)
    setOpcion(*max_option - 1);
  else
    renderizarMenu();

  reproducirEfecto(EFECTO_SELECCION);
}

void bajarOpcion(void)
{
  int *actual_option = &menu.window[menu.actual_window].actual_state;
  int *max_option = &menu.window[menu.actual_window].max_states;

  (*actual_option)++;

  if (*actual_option == *max_option)
    setOpcion(0);
  else
    renderizarMenu();

  reproducirEfecto(EFECTO_SELECCION);
}

void moverOpcionActual(void)
{
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void inicializarMenu(void)
{
  // menu principal (JUGAR, DIFICULTAD, RANKING, SALIRTXT)
  menu.window[MENU_WINDOW_HOME].max_states = 5;

  // menu dificultades (FACIL, NORMAL, DIFICIL)
  menu.window[MENU_WINDOW_DIFFICULTY].max_states = 3;

  // menu pausa (CONTINUAR, REINICIAR, SALIRTXT)
  menu.window[MENU_WINDOW_PAUSE].max_states = 3;

  // menu game over (REINICIAR, SALIRTXT)
  menu.window[MENU_WINDOW_GAME_OVER].max_states = 2;
}

static void renderizarMenu()
{
  allegro_clear_display();

  ALLEGRO_BITMAP *background = NULL;
  ALLEGRO_BITMAP *option = NULL;

  background = sprites.menu[menu.actual_window].background;
  option = sprites.menu[menu.actual_window].option[menu.window[menu.actual_window].actual_state];

  al_draw_bitmap(background, 0, 0, 0);

  al_draw_bitmap(option, MENU_OPTION_TOPLEFT_X,
                 MENU_OPTION_TOPLEFT_Y + (menu.window[menu.actual_window].actual_state * MENU_OPTION_DELTA_Y),
                 0);

  if (menu.actual_window == MENU_WINDOW_PAUSE || menu.actual_window == MENU_WINDOW_GAME_OVER)
    show_stats();

  al_flip_display();
}

static void show_stats(void)
{
  char *name = game_data_get_name();
  int score = game_data_get_score();
  int max_score = game_data_get_old_max_score();
  ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
  ALLEGRO_FONT *font = allegro_get_var_font();

  int x = STATS_X_COORD;
  int y = STATS_Y_COORD_START;

  al_draw_textf(font, color,
                x,
                y,
                0,
                "Jugador: %s", name);

  y += 20;

  if (menu.actual_window == MENU_WINDOW_PAUSE)
  {
    al_draw_textf(font, color,
                  x,
                  y,
                  0,
                  "Score:   %d", score);

    y += 20;

    al_draw_textf(font, color,
                  x,
                  y,
                  0,
                  "Max score:   %d", max_score);
  }
  else if (menu.actual_window == MENU_WINDOW_GAME_OVER)
  {
    if (score > max_score)
    {
      al_draw_textf(font, color,
                    x,
                    y + 10,
                    0,
                    "NUEVA PUNTUACION MAXIMA!");

      y += 40;

      al_draw_textf(font, color,
                    x,
                    y,
                    0,
                    "Anterior: %d", max_score);

      y += 20;

      al_draw_textf(font, color,
                    x,
                    y,
                    0,
                    "Nueva: %d", score);
    }

    else
    {
      al_draw_textf(font, color,
                    x,
                    y,
                    0,
                    "Score:   %d", score);

      y += 20;

      al_draw_textf(font, color,
                    x,
                    y,
                    0,
                    "Max score:   %d", max_score);
    }
  }
}
