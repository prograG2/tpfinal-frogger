#include "display.h"

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

void escribirRenglonDisplay(Renglon r, int pos){
    pthread_mutex_lock(&lock);
    for(int i=0; i<TAM_RENGLON; i++)
        disp_matriz[pos+i] = r[i];
    actualizarDisplay();
    pthread_mutex_unlock(&lock);
}

void escribirMatrizDisplay(Matriz m){
    pthread_mutex_lock(&lock);
    for(int i=0; i<CANT_FILAS; i++)
        disp_matriz[i] = m[i];
    actualizarDisplay();
    pthread_mutex_unlock(&lock);
}

void limpiarDisplay(){
    pthread_mutex_lock(&lock);
    limpiarMatriz(disp_matriz);
    actualizarDisplay();
    pthread_mutex_unlock(&lock);
}

void mostrarTexto(char* txt, int pos){
    mensaje_t msj = mensaje(txt, pos);
    while(renglonBool(msj.renglon)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverMensaje(&msj, NO_REPETIR);
        escribirRenglonDisplay(msj.renglon, pos);
    }
}

