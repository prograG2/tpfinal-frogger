#include "mensajes.h"

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

void uintARenglon(unsigned int n, Renglon r){
    Renglon renglon_aux;
    int j=0, resto = CANT_COLUMNAS;
    unsigned int div = 1000000000;
    while(n%div == n){
        div /= 10;
    }
    while(n){
        unsigned int aux = n%div;
        n = (n-aux)/div;
        resto = CANT_COLUMNAS - j - longitudes[CERO_INDEX+n];
        if(resto < 0)
            break;
        copiarRenglon(char_index[CERO_INDEX+n], renglon_aux);
        renglonShiftDer(renglon_aux, j);
        renglonOr(r, renglon_aux);
        j +=  longitudes[CERO_INDEX+n] + 1;
        n = aux;
        div /= 10;
    }
}

void reemplazarLetra(Renglon r, char c, int j){
    Renglon full, letra;
    CharARenglon(c, letra);
    renglonShiftDer(letra, j);
    copiarRenglon(char_index[FULL_INDEX], full);
    renglonShiftDer(full, j);
    renglonNot(full);
    renglonAnd(r, full);
    RenglonOr(r, letra);
}

mensaje_t mensaje(char* msj, int pos){
    mensaje_t mensaje = {0};
    mensaje.posicion = pos;
    int i=0;
    char c;
    while(c = msj[i]){
        if(c >= 'a' && c <= 'z') c -= ('a'-'A');
        if (!(c >= 'A' && c <= 'Z')) break;
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