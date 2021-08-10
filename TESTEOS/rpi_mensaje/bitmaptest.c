#include "bitmap.c"
#include "disdrv.h"
#include <stdint.h>
#include <pthread.h>
#include <time.h>


Renglon renglon = {0}, reserva = {0};
Matriz matriz = {0};
int i;
char msj[] = "ABMMMAB";

void *thread(){
    while(1){
        clock_t inicio = clock();
	    while((clock() - inicio)/(CLOCKS_PER_SEC) < 0.05);
        renglonDobleShiftIzq(renglon, reserva, 1);
        escribirRenglon(matriz, renglon, 5);
        actualizarDisplay(matriz);

        if(!renglonBool(reserva)){
            inicio = clock();
            while((clock() - inicio)/(CLOCKS_PER_SEC) < 0.05);
            renglonDobleShiftIzq(renglon, reserva, 1);
            escribirRenglon(matriz, renglon, 5);
            actualizarDisplay(matriz);

            int j=0;
            int resto = 16;
            for(; resto >= 0; i++){
                if(i == sizeof(msj)) i = 0;
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
  
    int j = 0; //donde voy a escribir la proxima vez
    int mover = 0; //si debo o n mover el mensaje despues
    int resto = 16;

    for(i=0; i<(sizeof(msj)) && !(mover && resto < 0); i++){
        char c = msj[i] ? msj[i] : ' ';

        Renglon letra;
        CharARenglon(c, letra);

        int espacios = c == ' ' ? longitudes[26] : longitudes[c-'A'];

        if(!mover && resto < 0){//paso entre el display y la reserva
            mover = 1;
            renglonDobleShiftDer(letra, reserva, j);
            renglonOr(renglon, letra);
            j = j + espacios + 1 - 16;
        }
        else if(mover){
            renglonShiftDer(letra, j);
            renglonOr(reserva, letra);
            j += espacios + 1; //dejo un espacio entre letra y letra
            
        }
        else{
            renglonShiftDer(letra, j);
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