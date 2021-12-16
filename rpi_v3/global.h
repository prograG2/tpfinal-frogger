#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define PC 0
#define RPI 1


#define NO_POS -1
#define POS_MSJ1 2
#define POS_MSJ2 9
#define POS_AUTOS 4

#define L_MAX 64

#define PLATAFORMA RPI

#if PLATAFORMA == PC
    #define ALTO 500
    #define ANCHO 500

#elif PLATAFORMA == RPI
    #define ALTO 16
    #define ANCHO 16

#elif
    #error "Plataforma no identificada"
#endif


#define SLEEP_CLOCKS (clock_t)CLOCKS_PER_SEC*0.1
#define JUGADOR_CLOCKS (clock_t)CLOCKS_PER_SEC*0.5
#define REFRESH_CLOCKS (clock_t)CLOCKS_PER_SEC

typedef unsigned char event_t;
enum textos{JUGAR = 0, DIFICULTAD, RANKING, SALIRTXT, CONTINUAR, REINICIAR, FACIL, NORMAL, DIFICIL};
enum eventos{NADA = -1, SALIR = 0, ARRIBA, ABAJO, IZDA, DCHA, ENTER, BORRAR, ESC, LISTO, REFRESH, CHOCAR, AGUA, TIMEOUT, GAME_OVER, META};
#define CTE_OPCION 100

#endif // _GLOBAL_H_