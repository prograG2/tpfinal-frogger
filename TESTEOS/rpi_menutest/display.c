#ifndef DISPLAY
#define DISPLAY

#include "bitmap.c"
#include "mensajes.c"
#include "disdrv.h"
#include <pthread.h>

pthread_mutex_t lock;

Matriz disp_matriz;

int iniciarDisplay(){
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    disp_init();       //inicializa el display
    disp_clear();      //limpia todo el display
    return 0;
}

void actualizarDisplay(){
    for(int i = DISP_MIN; i <= (DISP_MAX_Y); i++)
        for(int j = DISP_MIN; j <= (DISP_MAX_X) ; j++)
            disp_write((dcoord_t){j, i}, disp_matriz[i] & (0x8000 >> j));

    disp_update();
}

void escribirMensajeDisplay(mensaje_t* msj){
    pthread_mutex_lock(&lock);
    for(int i=0; i<TAM_RENGLON; i++)
        disp_matriz[(msj->posicion)+i] = (msj->renglon)[i];
    actualizarDisplay();
    pthread_mutex_unlock(&lock);
}

#endif