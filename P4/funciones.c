
#include <stdlib.h>
#include <string.h>
#include "funciones.h"


int contarprocesos(FILE *archivo){
    // Contamos o número de líneas no arquivo
    // para determinar o número de procesos
    int nprocesos = 0;
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), archivo)){
        nprocesos++;
    }
    //volvemos o ponteiro do arquivo ao inicio
    //para que se poida ler de novo
    rewind(archivo);
    return nprocesos;
}

void leerarchivo(FILE *archivo, proceso *procesos, int *nprocesos){
    // Lemos os procesos do arquivo e almacenamos na estrutura
    for(int i = 0; i < *nprocesos; i++){
        fscanf(archivo, "%s %d", procesos[i].nomeproceso, &procesos[i].tempo);
    }
}


int compararCreciente(const void *a, const void *b) {
    // Comparamos os tempos dos procesos
    // para ordenalos de menor a maior
    proceso *p1 = (proceso *)a;
    proceso *p2 = (proceso *)b;
    return p1->tempo - p2->tempo;
}

int compararDecreciente(const void *a, const void *b) {
    //ordenamos de maior a menor
    proceso *p1 = (proceso *)a;
    proceso *p2 = (proceso *)b;
    return p2->tempo - p1->tempo;
}

void mostrarYCalcular(proceso *procesos, int n) {
    // Mostramos a ordenacion final e calculamos o tempo de espera
    int tempoEspera = 0;
    int sumatempos = 0;

    printf("Orden final: ");
    
    for (int i = 0; i < n; i++) {
        printf("%s ", procesos[i].nomeproceso);
        sumatempos += procesos[i].tempo;
        if (i < n - 1) {
            tempoEspera += sumatempos;
        }
    }
    printf("\nTempo total de espera: %d\n", tempoEspera);
}

