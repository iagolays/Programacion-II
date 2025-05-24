#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char *argv[]){

    //abrimos o arquivo pasado por argumento
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Error al abrir el fichero");
        return 1;
    }

    //contamos os procesos
    //e alocamos memoria para eles
    int n = contarprocesos(f);
    proceso *procesos = malloc(n * sizeof(proceso));
    if (!procesos) {
        perror("Error de memoria");
        fclose(f);
        return 1;
    }

    //leemos os procesos do arquivo
    //e almacenamos na estrutura
    leerarchivo(f, procesos, &n);
    fclose(f);

    //menu para elexir o modo de ordenacion
    int modo;
    printf("Elixa o modo de ordenación:\n");
    printf("1. Crecente\n");
    printf("2. Decrecente\n");
    printf("Ingrese o número correspondente: ");
    scanf("%d", &modo);

    //ordenamos os procesos segundo o modo elixido usando quicksort
    //e mostramos o resultado
    if (modo == 1) {
        qsort(procesos, n, sizeof(proceso), compararCreciente);
    } else if (modo == 2) {
        qsort(procesos, n, sizeof(proceso), compararDecreciente);
    } else {
        printf("Modo no valido\n");
        free(procesos);
        return 1;
    }

    
    mostrarYCalcular(procesos, n);

    free(procesos);
    return 0;
}
