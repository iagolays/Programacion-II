#ifndef PROCESOS_H
#define PROCESOS_H
#include <stdio.h>

// Definición da estrutura proceso
// que contén o nome do proceso e o seu tempo
typedef struct{
    char nomeproceso[20];
    int tempo;
}proceso;

void leerarchivo(FILE *archivo, proceso *procesos, int *nprocesos);
int contarprocesos(FILE *archivo);
void ordenarProcesos(proceso *procesos, int n, int modo);
int compararCreciente(const void *a, const void *b);
int compararDecreciente(const void *a, const void *b);
void mostrarYCalcular(proceso *procesos, int n);

#endif