#include <stdio.h>
#include "menu.c"
#include "display.c"
#include "joystick.c"

#define TAM_MENU 4

int main(){
    if(iniciarDisplay() || iniciarJoystick())
        return 1;

    char* menu[TAM_MENU] = {"JUGAR", "DIFICULTAD", "OPCIONES", "SALIR"};
    nuevoMenu(menu, TAM_MENU);
    int elegido = iniciarMenu();
    printf("%d\n", elegido);
    destruirMenu();

}
