#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <time.h>

#define PC 0
#define RPI 1

#define PLATAFORMA RPI

#define L_MAX 64
#define CTE_OPCION 100
#define JUGADOR_CLOCKS (clock_t)CLOCKS_PER_SEC*0.5
#define REFRESH_AUTOS_CLOCKS (clock_t)CLOCKS_PER_SEC*2
#define REFRESH_JUGADOR_CLOCKS (clock_t)CLOCKS_PER_SEC

#if PLATAFORMA == PC
    #define ALTO 640
    #define ANCHO 480
    #define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*0.04
    #define POS_MSJ1 100
    #define POS_MSJ2 200

#elif PLATAFORMA == RPI
    #define ALTO 16
    #define ANCHO 16
    #define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*0.5
    #define POS_MSJ1 2
    #define POS_MSJ2 9
    //#define CANT_FILAS 16
    //#define CANT_COLUMNAS 16

#elif
    #error "Plataforma no identificada"
#endif

typedef int event_t;
enum textos{JUGAR = 0, DIFICULTAD, RANKING, SALIRTXT, CONTINUAR, REINICIAR, FACIL, NORMAL, DIFICIL};
enum eventos{NADA = -1, SALIR = 0, CHOCAR = 200, AGUA, TIMEOUT, GAME_OVER, META};
enum eventos_tecla{NO_MOVER = -1, ESC = 59, BORRAR = 63, ENTER = 67, IZDA = 82, DCHA, ARRIBA, ABAJO}; //Se respetan las definiciones de ALLEGRO ¡Chequear si se cambió la versión!


#endif // _GLOBAL_H_