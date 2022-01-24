/**
 * @file mensajes.c
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

#include "mensajes.h"

#include <stdio.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define INDEX_ESPACIO 26
#define INDEX_CERO 27
#define INDEX_FULL 37
#define CANT_SIMBOLOS 38


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static const int longitudes[] = {3,3,3,3,3,3,3,3,1,3,3,3,5,4,3,3,3,3,3,3,3,3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5}; //sin contar Ñ (+ espacio + numeros + FULL)



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static Renglon char_index[] = {{0x4000, 0xA000, 0xE000, 0xA000, 0xA000}, //A
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
                            {0x4000, 0x8000, 0xC000, 0xA000, 0xC000},
                            {0xE000, 0x2000, 0x2000, 0x4000, 0x4000},
                            {0x4000, 0xA000, 0x4000, 0xA000, 0x4000},
                            {0x4000, 0xA000, 0x6000, 0x2000, 0x4000}, //9
                            {0xF800, 0xF800, 0xF800, 0xF800, 0xF800}}; //TODO (FULL)




/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

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

void copiarMatrizRenglon(Matriz m, Renglon r, int pos){
    for(int i=0; i<TAM_RENGLON; i++)
        m[pos+i] = r[i];
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
        indice = c - '0' + INDEX_CERO;
    }
    else {
        indice = c - 'A';
    }    
    copiarRenglon(char_index[indice], r);
}

void uintARenglon(uint16_t n, Renglon r){
    Renglon renglon_aux;
    int j=0, resto = CANT_COLUMNAS;
    uint16_t div = 10000;
    while(n%div == n){
        div /= 10;
    }
    while(n){
        uint16_t aux = n%div;
        n = (n-aux)/div;
        resto = CANT_COLUMNAS - j - longitudes[INDEX_CERO+n];
        if(resto < 0)
            break;
        copiarRenglon(char_index[INDEX_CERO+n], renglon_aux);
        renglonShiftDer(renglon_aux, j);
        renglonOr(r, renglon_aux);
        j +=  longitudes[INDEX_CERO+n] + 1;
        n = aux;
        div /= 10;
    }
}

void reemplazarLetra(Renglon r, char c, int j){
    Renglon full, letra;
    CharARenglon(c, letra);
    renglonShiftDer(letra, j);
    copiarRenglon(char_index[INDEX_FULL], full);
    renglonShiftDer(full, j);
    renglonNot(full);
    renglonAnd(r, full);
    renglonOr(r, letra);
}

mensaje_t mensaje(char* msj, int pos){
    mensaje_t mensaje = {0};
    mensaje.posicion = pos;
    int i=0;
    char c;
    while((c = msj[i]) && c != '\n'){
        mensaje.msj[i] = c;
        i++;
    }
    mensaje.msj[i] = ' ';
    mensaje.msj[i+1] = '\0';

    int j = 0; //a partir de donde voy a escribir la proxima vez
    int resto = CANT_COLUMNAS; //cuantos espacios me quedarían si escribo la próxima letra
    int mover = NO_MOVER_TEXTO; //si debo o no mover el mensaje despues (se activa cuando termino de escribir en renglon y quedan letras aún)
    int longitud = i+2;

    for(i=0; i<(longitud-1); i++){ //rellena el mensaje por primera vez
        char c = msj[i]; //el caracter que debo escribir

        Renglon letra;
        CharARenglon(c, letra); //letra contiene la letra provisoria pasada a renglón

        int index;
        if(c == ' ')
            index = INDEX_ESPACIO;
        else if('0' <= c && c <= '9')
            index = INDEX_CERO + c - '0';
        else if('A' <= c && c <= 'Z')
            index = c - 'A';
        else
            index = INDEX_FULL;

        int espacios = longitudes[index];
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
        if (!repetir)
            borrarRenglon(msj->renglon);
        return;
    }
    renglonDobleShiftIzq(msj->renglon, msj->reserva, 1);

    if(!renglonBool(msj->reserva)){ //si la reserva queda vacía, dejo un espacio y relleno la reserva con letras nuevas
        int j=1;
        int resto = CANT_COLUMNAS;
        for(;; msj->index++){
            if(msj->index == msj->longitud){ //si termino la palabra
                if(repetir) msj->index = 0; // vuelvo a empezar desde el principio
                else{
                    borrarRenglon(msj->renglon); //o bien, dejo de mostrar mensaje
                    break;
                }
            }
            char c = msj->msj[msj->index];

            int index;
            if(c == ' ')
                index = INDEX_ESPACIO;
            else if('0' <= c && c <= '9')
                index = INDEX_CERO + c - '0';
            else if('A' <= c && c <= 'Z')
                index = c - 'A';
            else
                index = INDEX_FULL;

            int espacios = longitudes[index];

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

int getLongitud(char c){
    if(c == ' ')
        return longitudes[INDEX_ESPACIO];
    else if('0' <= c && c <= '9')
        return longitudes[INDEX_CERO + c - '0'];
    else if('A' <= c && c <= 'Z')
        return longitudes[c - 'A'];
    else
        return longitudes[INDEX_FULL];
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
