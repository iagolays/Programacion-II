/*Ejercicio 5 (versión 1) (la versión entregable se realizará con makefile)
Implementa un programa para realizar la raíz cuadrada de cada uno de los elementos de un array a: int
a[4]; de modo que el vector raíz c se calcule mediante la función sqrt(). Puedes usar como base la
función sqrt utilizada en el ejercicio 3.
Ejecuta paso a paso el programa, visualizando en todo momento las variables, y observando cómo se
modifican las componentes de los arrays.
a) Utilizando el panel “Watch”, visualiza las siguientes expresiones, que indican la dirección de memoria
de los respectivos elementos del array: &a[0] &a[1] &a[2] &a[3].

&a[0]:0x7fffffffdbf0
&a[1]:0x7fffffffdbf4
&a[2]:0x7fffffffdbf8
&a[3]:0x7fffffffdbfc
b) ¿Cuál es el mayor y cuál el menor? Calcula la diferencia entre las direcciones de dos elementos
consecutivos. Trata de justificar los resultados.

O maior é &a[3], o menor é &a[0], a diferencia é de 4, xa que ao tratarse dun dato tipo int é a cantidade de bits de cada un*/

#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main(int argc, char** argv){
    int a[4];
    double c[4];
    int i = 0;

    if (argc == 1){
        printf ("Introduce catro enteiros\n");
        for (i=0; i<4; i++){
            printf("Elemento %d:", i+1);
            scanf("%d", &a[i]);
        }
    } else if (argc ==5){
        for (i=0; i<4; i++){
            a[i]=atoi (argv[i+1]);
        }
    } else{
        printf("Error ao introducir os datos");
        return 1;
    }

    for(i = 0; i<4; i++){
        if(a[i] < 0){
            printf("Produciuse un erro de cálculo no elemento c[%d]\n", i);
        }
        else{
            c[i] = sqrt(a[i]);
            printf("Elemento c[%d] = %f\n", i, c[i]);
        }
    }   
    return (EXIT_SUCCESS);
}