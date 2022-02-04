/**
 * @file nombre.c
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

#include "../../nombre.h"

#include "allegro_stuff.h"
#include "game_data.h"

#include <string.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define NAME_TOPLEFT_X 55
#define NAME_TOPLEFT_Y 312

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void nuevoNombre(void)
{
    allegro_clear_display();

    game_data_clear_name();
    game_data_set_score_max(0);

    /*cambiar por background correspondiente*/
    al_draw_bitmap(sprites.name, 0, 0, 0);

    al_flip_display();
}

void subirLetra(void)
{
}

void bajarLetra(void)
{
}

void siguienteLetra(void)
{
}

void agregarLetra(void)
{
    game_data_add_name_letter(allegro_get_last_key());

    char *name = game_data_get_name();

    allegro_clear_display();

    /*cambiar por background correspondiente*/
    al_draw_bitmap(sprites.name, 0, 0, 0);

    al_draw_textf(allegro_get_var_font(), al_map_rgb(100, 200, 200), NAME_TOPLEFT_X, NAME_TOPLEFT_Y, 0,
                  "%s", name);

    al_flip_display();
}

void subirNombre(void)
{
}

char *devolverNombre(void)
{
    return game_data_get_name();
}
