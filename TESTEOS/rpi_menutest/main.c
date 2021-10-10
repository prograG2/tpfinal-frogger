#include <stdio.h>
#include "menu.c"
#include "display.c"
#include "gamedata.c"


#define TAM_MENU 4

int dificultad;

int main(){
    if(iniciarDisplay() || iniciarJoystick())
        return 1;
    
    int elegido = -1;
    char* menu[TAM_MENU] = {"JUGAR", "DIFICULTAD", "RANKING", "SALIR"};
    menu_t principal = Menu(menu, TAM_MENU);

    while((elegido = obtenerOpcion(&principal)) != 3){
        limpiarDisplay();
        switch(elegido){
            case 0:;
                gamedata_t yo = nuevoJugador();
            break;
            case 1:;
                char* diftxt[3] = {"FACIL", "NORMAL", "DIFICIL"};
                menu_t dificultad = Menu(diftxt, 3);
                elegido = obtenerOpcion(&dificultad);
                printf("%d\n", elegido);
                destruirMenu(&dificultad);
            break;
            case 2:; //¿porque el ;?
                FILE* pFile;
                char linea[100];
                pFile = fopen ("ranking.txt" , "r");
                if (pFile == NULL){
                    perror ("Error opening file");
                    break;
                }
                int i = 1;
                while(fgets(linea, 100, pFile) != NULL){
                    printf("%s", linea);
                }
                fclose (pFile);
            break;
        }
        limpiarDisplay();
    }
    limpiarDisplay();
    printf("%d\n", elegido);
    destruirMenu(&principal);
}
