
#include "matriz.h"

matriz* suma(matriz *M1, matriz *M2) {
    matriz *aux = 0;
    int i, k;

    if (M1 != 0 && M2 != 0) {
        if (M1->filas != M2->filas || M1->columnas != M2->columnas) {
            printf("El numero de filas y columnas deben ser iguales\n");
            return aux;
        }
        aux = crearMatriz(M1->filas, M1->columnas);
        for (i = 0; i < aux->filas; i++)
            //for (k = 0; k < aux->filas; k++) este bucle debe iterar sobre as columnas xa que o anterior xa actua nas filas
            for (k = 0; k < aux->columnas; k++)
                //*(aux->datos + i * aux->columnas + (k - 1)) = *(M2->datos + i * M1->columnas + (k - 1)) + *(M2->datos + i * M2->columnas + (k - 1));
                //Debemos eliminar os -1, xa que no caso de que k sexa 0, o programa intentaria acceder a unha posicion negativa
                //Tamen debemos sustituir o  primeriro M2->datos por M1->datos, tendo asi para M1 e logo M2
                *(aux->datos + i * aux->columnas + (k)) = *(M2->datos + i * M1->columnas + (k)) + *(M2->datos + i * M2->columnas + (k));
        return aux;
    // debemos engadir o return xa que a función debe devolver algo, e engadir as {}
    } else{
        printf("Alguna de las matrices no existe\n");
        return aux;
    }
}

