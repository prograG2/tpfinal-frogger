#ifndef MENSAJES
#define MENSAJES

#include "bitmap.c"
#include <stdint.h>

#define NO_POS -1
#define POS_MSJ1 2
#define POS_MSJ2 9
#define MOVER_TEXTO 1
#define NO_MOVER_TEXTO 0
#define TAM_RENGLON 5
#define INDEX_ESPACIO 26
#define CANT_SIMBOLOS 27
#define L_MAX 64
#define NO_REPETIR 0
#define REPETIR 1
#define CERO_INDEX 27
#define FULL_INDEX 37

typedef uint16_t Renglon[TAM_RENGLON];

int longitudes[] = {3,3,3,3,3,3,3,3,1,3,3,3,5,4,3,3,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5}; //sin contar Ñ (+ espacio + numeros + FULL)

Renglon char_index[] = {{0x4000, 0xA000, 0xE000, 0xA000, 0xA000}, //A
                            {0xC000, 0xA000, 0xC000, 0xA000, 0xC000},
                            {0x4000, 0xA000, 0x8000, 0xA000, 0x4000},
                            {0xC000, 0xA000, 0xA000, 0xA000, 0xC000},
                            {0xE000, 0x8000, 0xC000, 0x8000, 0xE000},
                            {0xE000, 0x8000, 0xC000, 0x8000, 0x8000},
                            {0x6000, 0x8000, 0xA000, 0xA000, 0x6000},
                            {0xA000, 0xA000, 0xE000, 0xA000, 0xA000},
                            {0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
                            {0x2000, 0x2000, 0xA000, 0xA000, 0x4000},
                            {0xA000, 0xA000, 0xC000, 0xA000, 0xA000},
                            {0x8000, 0x8000, 0x8000, 0x8000, 0xE000},
                            {0x8800, 0xD800, 0xA800, 0xA800, 0x8800},
                            {0x9000, 0xD000, 0xB000, 0x9000, 0x9000},
                            {0x4000, 0xA000, 0xA000, 0xA000, 0x4000},
                            {0xC000, 0xA000, 0xA000, 0xC000, 0x8000},
                            {0x4000, 0xA000, 0xA000, 0xA000, 0x6000},
                            {0xC000, 0xA000, 0xC000, 0xA000, 0xA000},
                            {0x6000, 0x8000, 0x4000, 0x2000, 0xC000},
                            {0xE000, 0x4000, 0x4000, 0x4000, 0x4000},
                            {0xA000, 0xA000, 0xA000, 0xA000, 0x4000},
                            {0xA000, 0xA000, 0xA000, 0x4000, 0x4000},
                            {0x8800, 0xA800, 0xA800, 0x5000, 0x5000},
                            {0xA000, 0xA000, 0x4000, 0xA000, 0xA000},
                            {0xA000, 0xA000, 0x4000, 0x4000, 0x4000},
                            {0xE000, 0x2000, 0x4000, 0x8000, 0xE000}, //Z
                            {0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //espacio
                            {0x4000, 0xA000, 0xA000, 0xA000, 0x4000}, //0
                            {0x4000, 0xC000, 0x4000, 0x4000, 0xE000},
                            {0x4000, 0xA000, 0x2000, 0x4000, 0xE000},
                            {0xC000, 0x2000, 0x4000, 0x2000, 0xC000},
                            {0xA000, 0xA000, 0xE000, 0x2000, 0x2000},
                            {0xE000, 0x8000, 0xC000, 0x2000, 0xC000},
                            {0x4000, 0x8000, 0xC000, 0xA000, 0x8000},
                            {0xE000, 0x2000, 0x2000, 0x4000, 0x4000},
                            {0x4000, 0xA000, 0x4000, 0xA000, 0x4000},
                            {0x4000, 0xA000, 0x6000, 0x2000, 0x4000}, //9
                            {0xF800, 0xF800, 0xF800, 0xF800, 0xF800}}; //TODO

typedef struct Mensaje{
    char msj[L_MAX];
    int posicion;
    int index;
    int index_inicio;
    int j_inicio;
    int longitud;
    int mover;
    Renglon renglon;
    Renglon reserva;
    Renglon renglon_inicio;
    Renglon reserva_inicio;
} mensaje_t;

void printRenglon(Renglon r){
    for(int i=0; i<TAM_RENGLON; i++, putchar('\n'))
        for(int j=0; j<CANT_FILAS; j++)
            putchar((r[i] & (0b1000000000000000 >> j)) ? '1' : '.'); 
    
    putchar('\n');
}

void printRenglonDoble(Renglon r1, Renglon r2){
    for(int i=0; i<TAM_RENGLON; i++, putchar('\n')){
        for(int j=0; j<CANT_FILAS; j++)
            putchar((r1[i] & (0b1000000000000000 >> j)) ? '1' : '.');
        putchar('|');
        for(int j=0; j<CANT_FILAS; j++)
            putchar((r2[i] & (0b1000000000000000 >> j)) ? '1' : '.');
    }

    putchar('\n');
}

void borrarRenglon(Renglon r){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] = 0;
}

void renglonShiftDer(Renglon r, uint16_t s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] >>= s;
}

void renglonShiftIzq(Renglon r, uint16_t s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] <<= s;
}

void renglonOr(Renglon r, Renglon s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] |= s[i];
}

void renglonAnd(Renglon r, Renglon s){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] &= s[i];
}

void renglonNot(Renglon r){
    for (int i=0; i<TAM_RENGLON; i++)
        r[i] = ~r[i];
}

void renglonDobleShiftDer(Renglon r1, Renglon r2, unsigned int s){
    for (int i=0; i<TAM_RENGLON; i++){
        r2[i] >>= s;
        r2[i] |= (r1[i] & ((1 << s) - 1)) << (CANT_COLUMNAS - s); //pego los últimos bits de r1
        r1[i] >>= s;
    }
}

void renglonDobleShiftIzq(Renglon r1, Renglon r2, unsigned int s){
    for (int i=0; i<TAM_RENGLON; i++){
        r1[i] <<= s;
        r1[i] |= (r2[i] & ((uint16_t)(0b11111111111111110000000000000000 >> s))) >> (CANT_COLUMNAS-s);//pego los últimos bits de r2
        r2[i] <<= s;
    }
}

void copiarRenglon(Renglon r1, Renglon r2){
    for (int i=0; i<TAM_RENGLON; i++){
        r2[i] = r1[i];
    }
}

int renglonBool(Renglon r){
    for (int i=0; i<TAM_RENGLON; i++)
        if(r[i]) return 1;
    return 0;
}

void CharARenglon(char c, Renglon r){
    int indice;
    if(c == ' ' || !c){
        indice = INDEX_ESPACIO;
    }
    else if('0' <= c && c <= '9'){
        indice = c - '0' + INDEX_ESPACIO;
    }
    else {
        indice = c - 'A';
    }    
    copiarRenglon(char_index[indice], r);
}

mensaje_t mensaje(char* msj, int pos){
    mensaje_t mensaje = {0};
    mensaje.posicion = pos;
    int i=0;
    char c;
    while(c = msj[i]){
        if(c >= 'a' && c <= 'z') c -= ('a'-'A');
        if (!(c >= 'A' && c <= 'Z')) c = '\0';
        mensaje.msj[i] = c;
        i++;
    }
    mensaje.msj[i] = '\0';

    int j = 0; //a partir de donde voy a escribir la proxima vez
    int resto = CANT_COLUMNAS; //cuantos espacios me quedarían si escribo la próxima letra
    int mover = NO_MOVER_TEXTO; //si debo o no mover el mensaje despues (se activa cuando termino de escribir en renglon y quedan letras aún)
    int longitud = i+1;

    for(i=0; i<(longitud-1); i++){ //rellena el mensaje por primera vez
        char c = msj[i] ? msj[i] : ' '; //el caracter que debo escribir (si es el terminador escribo espacio)

        Renglon letra;
        CharARenglon(c, letra); //letra contiene la letra provisoria pasada a renglón

        int espacios = c == ' ' ? longitudes[INDEX_ESPACIO] : longitudes[c-'A']; //calculo los espacios horizontales que ocupará la letra
        resto = (CANT_COLUMNAS-j) - espacios; //lo que me quedaría libre si escribo

        if(resto < 0){
            if(mover) break;
            else{
                renglonDobleShiftDer(letra, mensaje.reserva, j); //muevo la letra para que quede entre medio de ambos renglones (sin perder información)
                j = j + espacios + 1 - CANT_COLUMNAS; //dejo un espacio entre letra y letra
                renglonOr(mensaje.renglon, letra);
                mover = MOVER_TEXTO;
                continue;
            }
        }

        renglonShiftDer(letra, j); //muevo la letra sobre renglon
        j += espacios + 1;
        if(mover) renglonOr(mensaje.reserva, letra);
        else renglonOr(mensaje.renglon, letra);

    }

    copiarRenglon(mensaje.renglon, mensaje.renglon_inicio);
    copiarRenglon(mensaje.reserva, mensaje.reserva_inicio);
    mensaje.index = i;
    mensaje.index_inicio = i;
    mensaje.j_inicio = j;
    mensaje.longitud = longitud;
    mensaje.mover = mover;

    return mensaje;
}

void moverMensaje(mensaje_t* msj, int repetir){
    if(msj->mover == NO_MOVER_TEXTO){
        if (repetir) return;
        else{
            borrarRenglon(msj->renglon);
            return;
        }
    }
    renglonDobleShiftIzq(msj->renglon, msj->reserva, 1);

    if(!renglonBool(msj->reserva)){ //si la reserva queda vacía, dejo un espacio y relleno la reserva con letras nuevas
        int j=1;
        int resto = CANT_COLUMNAS;
        for(;; msj->index++){
            if(msj->index == msj->longitud){ //si termino la palabra
                if(repetir) msj->index = 0; // vuelvo a empezar desde el principio
                else break; //o bien, dejo de mostrar mensaje
            }
            char c = msj->msj[msj->index] ? msj->msj[msj->index] : ' ';

            int espacios = c == ' ' ? longitudes[INDEX_ESPACIO] : longitudes[c-'A'];                
            resto = (CANT_COLUMNAS-j) - espacios; //lo que me quedaría libre
            if(resto < 0) break;

            
            Renglon letra;
            CharARenglon(c, letra);
            renglonShiftDer(letra, j);

            j += espacios + 1; //dejo un espacio entre letra y letra
            renglonOr(msj->reserva, letra);
        }
    }
}

#endif