#include "bitmap.c"
#include "disdrv.h"
#include <stdint.h>
#include <pthread.h>
#include <time.h>


Renglon renglon = {0}, reserva = {0}; //RENGLON: el renglón que aparece en la matriz física, RESERVA: el renglón imaginario que extiende a RENGLON para mover el mensaje (RENGLON:RESERVA)
Matriz matriz = {0};//donde se graba renglón 
int i;//por cuál letra voy leyendo a msj
char msj[] = "ABMMMAB";

void *thread(){
    while(1){
        clock_t inicio = clock();
	    while((clock() - inicio)/(CLOCKS_PER_SEC) < 0.05);
        renglonDobleShiftIzq(renglon, reserva, 1);
        escribirRenglon(matriz, renglon, 5);
        actualizarDisplay(matriz);

        if(!renglonBool(reserva)){ //si la reserva queda vacía, espero un tiempo (para agregar el espacio) y relleno la reserva con letras nuevas
            inicio = clock();
            while((clock() - inicio)/(CLOCKS_PER_SEC) < 0.05);
            renglonDobleShiftIzq(renglon, reserva, 1);
            escribirRenglon(matriz, renglon, 5);
            actualizarDisplay(matriz);

            int j=0;
            int resto = 16;
            for(; resto >= 0; i++){
                if(i == sizeof(msj)) i = 0; //si termino la palabra vuelvo a empezar desde el principio
                char c = msj[i] ? msj[i] : ' ';
                Renglon letra;
                CharARenglon(c, letra);

                int espacios = c == ' ' ? longitudes[26] : longitudes[c-'A'];

                renglonShiftDer(letra, j);
                renglonOr(reserva, letra);
                j += espacios + 1; //dejo un espacio entre letra y letra
                
                resto = (16-j) - espacios; //lo que me queda libre
            }
        }

    }
}

int main(){
    disp_init();       //inicializa el display
    disp_clear();      //limpia todo el display
  
    int j = 0; //a partir de donde voy a escribir la proxima vez
    int mover = 0; //si debo o no mover el mensaje despues (se activa cuando termino de escribir en renglon y quedan letras aún)
    int resto = 16; //cuantos espacios me quedarían si escribo la próxima letra

    for(i=0; i<(sizeof(msj)) && !(mover && resto < 0); i++){ //rellena el mensaje por primera vez
        char c = msj[i] ? msj[i] : ' '; //el caracter que debo escribir (si es el terminador escribo espacio)

        Renglon letra;
        CharARenglon(c, letra); //letra contiene la letra provisoria pasada a renglón

        int espacios = c == ' ' ? longitudes[26] : longitudes[c-'A']; //calculo los espacios horizontales que ocupará la letra

        if(!mover && resto < 0){//paso entre el display y la reserva
            mover = 1;
            renglonDobleShiftDer(letra, reserva, j); //muevo la letra para que quede entre medio de ambos renglones (sin perder información)
            renglonOr(renglon, letra);
            j = j + espacios + 1 - 16; //dejo un espacio entre letra y letra
        }
        else if(mover){
            renglonShiftDer(letra, j); //muevo la letra sobre renglon
            renglonOr(reserva, letra);
            j += espacios + 1; //dejo un espacio entre letra y letra
            
        }
        else{
            renglonShiftDer(letra, j); //muevo la letra sobre reserva
            renglonOr(renglon, letra);
            j += espacios + 1; //dejo un espacio entre letra y letra
        }
        resto = (16-j) - espacios; //lo que me queda libre
    }

    escribirRenglon(matriz, renglon, 5);
    actualizarDisplay(matriz);

    if(mover){
        pthread_t tid;
        pthread_create(&tid, NULL, thread, NULL);
        pthread_join(tid, NULL);
    }
    else while(1);
    return 0;
}