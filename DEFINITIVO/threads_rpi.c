#include "threads_rpi.h"

void *thread_joystick(){
    while(p2CurrentState){
	    event_t joystick = leerJoystick();
	    if(joystick > 0) //Si hay movimiento de joystick
		    queue_insert(joystick);
    }
}

void *thread_display_menu(){
    while((p2CurrentState == en_menu_ppal) || (p2CurrentState == en_pausa) || (p2CurrentState == en_game_over)){
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
        moverOpcionActual();
    }
    queue_insert(CTE_OPCION+menu.opcion_actual);
}

void *thread_tiempo(){
    clock_t ref = clock();
    while((p2CurrentState == jugando) && (jugador.tiempo < jugador.tiempo_limite)){
        jugador.tiempo = jugador.inicio + clock() - ref;
        if(jugador.tiempo > acc){
            jugador.tiempo_bits >>= 1;
            acc += frac;
        }
    }
    jugador.inicio = jugador.tiempo;
    queue_insert(TIMEOUT);
}

void *thread_autos(){
    while(p2CurrentState == jugando){
    clock_t meta = clock() + REFRESH_CLOCKS;
    while(clock() < meta);
    
    uint16_t tmp = jugador.jugador_1;
    jugador.jugador_1 = jugador.jugador_2;
    jugador.jugador_2 = tmp;

    int i;
    for(i=POS_AUTOS; i<POS_AUTOS+10; i+=2){
        uint16_t carril = jugador.mapa[i] << 1;
        if(jugador.agua){
            if(!(carril & 0b111111) && (rand() & 1))
                carril |= 0b11;
            else if(!(carril & 0b11111111) && (rand() & 1))
                carril |= 0b1111;
        }
        else{
            if(!(carril & 0b1111) && (rand() & 1))
            carril |= 0b11;
            else if(!(carril & 0b111111) && (rand() & 1))
                carril |= 0b1111;
        }
        jugador.mapa[i] = carril;
        jugador.mapa[i+1] = carril;
        
    }
    }
}

void *thread_display_juego(){
    while(p2CurrentState == jugando){
    Matriz m;
    m[0] = jugador.vidas;
    m[1] = jugador.tiempo_bits;
    
    if((jugador.jugador_1 & jugador.mapa[jugador.posicion_sur-1]) | (jugador.jugador_2 & jugador.mapa[jugador.posicion_sur]))
        queue_insert(jugador.agua? AGUA : CHOCAR);
    
    else if(jugador.posicion_sur == 3)
        queue_insert(META);

    matrizOr(m, jugador.mapa);
    m[(jugador.posicion_sur)-1] |= jugador.jugador_1;
    m[jugador.posicion_sur] |= jugador.jugador_2;
    escribirMatrizDisplay(m);

    }
}

void *thread_display_ranking(){
    FILE* pFile;
    char linea[100];
    pFile = fopen ("ranking.txt" , "r");
    if (pFile == NULL){
        perror ("mostrarRanking(): Error opening file");
        return;
    }
    int puesto = 1;
    while(fgets(linea, 100, pFile) != NULL){
        Renglon puesto_;
        uintARenglon(puesto++, puesto_);
        escribirRenglonDisplay(puesto_, POS_MSJ1);
        mostrarTexto(linea, POS_MSJ2);
        limpiarDisplay();
        clock_t meta = clock() + SLEEP_CLOCKS;
        while(clock() < meta);
    }
    fclose (pFile);
    queue_insert(ENTER);
}