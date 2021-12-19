#include "nombre_pc.h"

void nuevoNombre(){
    index = 0;
    j = 0;
    nombre[index] = 'A';
    nombre[index+1] = '\0';
}

void subirLetra(){
	if(--nombre[index] < 'A')
		nombre[index] = 'Z';
    mostrarTexto(nombre, ALTO/2);
}

void bajarLetra(){
    if(++nombre[index] > 'Z')
		nombre[index] = 'A';
    mostrarTexto(nombre, ALTO/2);
}

void siguienteLetra(){
    if(index == L_MAX-2)
		return;
	index++;
	nombre[index] = 'A';
	nombre[index+1] = '\0';
    mostrarTexto(nombre, ALTO/2);
}

void agregarLetra(){
    if(index == L_MAX-2)
		return;
	char letra[2];
	letra[0] = (char) last_key;
	letra[1] = '\0';
	strcat(nombre, letra);      //cambiar por agregar caracteres al string que vive acá (en fsm.c)
	index++;

    mostrarTexto(nombre, ALTO/2);
}