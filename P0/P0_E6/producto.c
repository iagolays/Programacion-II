#include "matriz.h"

matriz* producto(matriz *M1, matriz *M2) {
    matriz *aux = 0;
    int i, k, l;
    if (M1 != 0 && M2 != 0) {
        //if (M1->filas != M2->columnas) { O que debemos comprobar realmente é que o nº de columnas da primeira matriz coincida co de filas da segunda para poder multiplicalas
        if (M1->columnas != M2->filas) {
            printf("El numero de columnas de la primera matriz y de filas de la segunda deben ser iguales\n");
            return aux;
        }

        aux = crearMatriz(M1->filas, M2->columnas);
        for (i = 0; i < M1->filas; i++)
            for (k = 0; k < M2->columnas; k++) {
                *(aux->datos + i * M2->columnas + k) = 0;
                for (l = 0; l < M1->columnas; l++) {
                    *(aux->datos + i * M2->columnas + k) += *(M1->datos + i * M1->columnas + l) * *(M2->datos + l * M2->columnas + k);
                }
            }

        return aux;
    // Falta o return de aux, xa que debe devolver un valor, logo tamen debemos engadir {}
    } else{
        printf("Alguna de las matrices no existe\n");
        return aux;
    }
}
