#ifndef _GLOBAL_H_
#define _GLOBAL_H_

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



#endif // _GLOBAL_H_