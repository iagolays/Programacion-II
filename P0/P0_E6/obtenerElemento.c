#include "matriz.h"

float obtenerElemento(int fila, int columna, matriz *M) {
    int x;

    if (M != 0) {
        //if ((fila < 0 || fila > M->filas) || (columna < 0 || columna > M->columnas)) {; o primeiro elemento é 0 e o último é n-1; logo non poderá sobre este, entón requerimos o >=
        if ((fila < 0 || fila >= M->filas) || (columna < 0 || columna >= M->columnas)) {
            printf("Ese elemento no existe\n");
            return 0;
        }
        x = *((M->datos) + fila * M->columnas + columna);
        return x;
    } else{
        printf("La matriz no existe\n");
        // a función debe ter un return para finalizar, ademais debemos engadir as chaves  {}       
        return 0;
    }
}
