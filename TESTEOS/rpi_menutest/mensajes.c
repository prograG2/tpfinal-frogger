#include "bitmap.c"
#include <stdint.h>
#include <pthread.h>
#include <time.h>


#define TAM_RENGLON 5
#define INDEX_ESPACIO 26
#define CANT_SIMBOLOS 27
typedef uint16_t Renglon[TAM_RENGLON];

const int char_index[][TAM_RENGLON] = {{0x4000, 0xA000, 0xE000, 0xA000, 0xA000}, //A
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
                            {0x0000, 0x0000, 0x0000, 0x0000, 0x0000}}; //espacio

Renglon renglon = {0}, reserva = {0}; //RENGLON: el renglón que aparece en la matriz física, RESERVA: el renglón imaginario que extiende a RENGLON para mover el mensaje (RENGLON:RESERVA)
Matriz matriz = {0};//donde se graba renglón 
int index;//por cuál letra voy leyendo a msj
int posicion;
int longitud;
char msj[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

void CharARenglon(char c, Renglon r){
    if(!c) c = ' ';
    int indice = c == ' ' ? INDEX_ESPACIO : c - 'A';
    for(int i=0; i<TAM_RENGLON; i++)
        r[i] = char_index[indice][i];
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

void escribirRenglon(Matriz m, Renglon r, int fila){
    for(int i=0; i<TAM_RENGLON; i++)
        m[fila+i] = r[i];
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

int renglonBool(Renglon r){
    for (int i=0; i<TAM_RENGLON; i++)
        if(r[i]) return 1;
    return 0;
}

int revisarMensaje(char* msj){
    int i=0;
    while(msj[i]){
        if(msj[i] <= 'a' && msj[i] <= 'z') msj[i] -= ('a'-'A');
        if (!(msj[i] <= 'A' && msj[i] <= 'Z')) msj[i] = '\0';
        i++;
    }
    
    return i+1;
}

pthread_t escribirTexto(char* msj, int pos, int fijar_mensaje){
    int i;
    int j = 0; //a partir de donde voy a escribir la proxima vez
    int resto = CANT_COLUMNAS; //cuantos espacios me quedarían si escribo la próxima letra
    int mover = 0; //si debo o no mover el mensaje despues (se activa cuando termino de escribir en renglon y quedan letras aún)

    longitud = revisarMensaje(msj);

    for(i=0; i<longitud; i++){ //rellena el mensaje por primera vez
        char c = msj[i] ? msj[i] : ' '; //el caracter que debo escribir (si es el terminador escribo espacio)

        Renglon letra;
        CharARenglon(c, letra); //letra contiene la letra provisoria pasada a renglón

        int espacios = c == ' ' ? longitudes[INDEX_ESPACIO] : longitudes[c-'A']; //calculo los espacios horizontales que ocupará la letra
        resto = (CANT_COLUMNAS-j) - espacios; //lo que me quedaría libre si escribo

        if(resto < 0){
            if(mover) break;
            else{
                renglonDobleShiftDer(letra, reserva, j); //muevo la letra para que quede entre medio de ambos renglones (sin perder información)
                j = j + espacios + 1 - CANT_COLUMNAS; //dejo un espacio entre letra y letra
                renglonOr(renglon, letra);
                if(fijar_mensaje) break;
                mover = 1;
                continue;
            }
        }

        renglonShiftDer(letra, j); //muevo la letra sobre renglon
        j += espacios + 1;
        if(mover) renglonOr(reserva, letra);
        else renglonOr(renglon, letra);

    }
    
    escribirRenglon(matriz, renglon, pos);
    actualizarDisplay(matriz);

    if(mover){
        index = i;
        posicion = pos;
        pthread_t tid;
        pthread_create(&tid, NULL, thread, NULL);
        return tid;
    }
    else return (pthread_t){0};
}

void destruirTexto(pthread_t tid, int pos){
    pthread_join(tid, NULL);
    borrarRenglon(renglon);
    borrarRenglon(reserva);
    escribirRenglon(matriz, renglon, pos);
}

void *thread(){
    while(1){
        clock_t inicio = clock();
	    while((clock() - inicio)/(CLOCKS_PER_SEC) < 0.05);
        renglonDobleShiftIzq(renglon, reserva, 1);

        escribirRenglon(matriz, renglon, posicion);
        actualizarDisplay(matriz);

        if(!renglonBool(reserva)){ //si la reserva queda vacía, espero un tiempo (para agregar el espacio) y relleno la reserva con letras nuevas
            inicio = clock();
            while((clock() - inicio)/(CLOCKS_PER_SEC) < 0.05);
            renglonDobleShiftIzq(renglon, reserva, 1);

            escribirRenglon(matriz, renglon, posicion);
            actualizarDisplay(matriz);

            int j=0;
            int resto = CANT_COLUMNAS;
            for(;; index++){
                if(index == longitud) index = 0; //si termino la palabra vuelvo a empezar desde el principio
                char c = msj[index] ? msj[index] : ' ';
                Renglon letra;
                CharARenglon(c, letra);

                int espacios = c == ' ' ? longitudes[INDEX_ESPACIO] : longitudes[c-'A'];                
                resto = (CANT_COLUMNAS-j) - espacios; //lo que me quedaría libre

                if(resto < 0) break;

                renglonShiftDer(letra, j);

                j += espacios + 1; //dejo un espacio entre letra y letra
                renglonOr(reserva, letra);
            }
        }

    }
}