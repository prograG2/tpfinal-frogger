#include "nombre_rpi.h"
#include "mensajes_rpi.h"
#include "display_rpi.h"

Renglon nombreDisp;
static char nombre[L_MAX];
static int index, j;

void nuevoNombre(){
    index = 0;
    j = 0;
    nombre[index] = 'A';
    nombre[index+1] = '\0';
}

void subirLetra(){
	if(--nombre[index] < 'A')
		nombre[index] = 'Z';
    reemplazarLetra(nombreDisp, nombre[index], j);
    escribirRenglonDisplay(nombreDisp, POS_MSJ2);
}

void bajarLetra(){
    if(++nombre[index] > 'Z')
		nombre[index] = 'A';
    reemplazarLetra(nombreDisp, nombre[index], j);
    escribirRenglonDisplay(nombreDisp, POS_MSJ2);
}

void siguienteLetra(){
    if(index == L_MAX-2)
		return;
	index++;
	nombre[index] = 'A';
	nombre[index+1] = '\0';
    int resto = (CANT_COLUMNAS-j) - 6; //Considero el peor caso para calcular el espacio
    if(resto < 0){
        renglonShiftIzq(nombreDisp, -resto); //Me corro lo que necesito para que entre la sig letra
        j = CANT_COLUMNAS - 6;
    }
    else  
		j += getLongitud(nombre[index]) + 1;
    
    reemplazarLetra(nombreDisp, nombre[index], j);
    escribirRenglonDisplay(nombreDisp, POS_MSJ2);
}

void agregarLetra(){
}