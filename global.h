#define PC 0
#define RPI 1

#define PLATAFORMA PC

#if PLATAFORMA == PC
    #define ALTO 500
    #define ANCHO 500
#elif PLATAFORMA == RPI
    #define ALTO 16
    #define ANCHO 16
#elif
    #error "Plataforma no identificada"
#endif


typedef struct
{
    char rana : 1;
    char objeto : 5;
    char piso : 2;
}celda_t;

enum eventos{SALIR = 0, ARRIBA, ABAJO, IZDA, DCHA, ENTER, BORRAR, ESC, REFRESH};