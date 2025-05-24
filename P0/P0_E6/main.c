/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * DOCUMENTAR LAS CORRECCIONES INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - número de filas o columnas: 0
 * - acceder a un dato con índices negativos
 * - verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - número de filas y columnas distintos en las dos matrices
 *      - número de filas igual y de columnas distinto
 *      - número de columnas igual y de filas distinto
 * 
 * ¿Se está liberando correctamente la memoria en todos los casos? Una vez modificada la liberación de
memoria, prueba a crear las matrices, destruirlas y salir del programa (opción '0'). ¿Está finalizando la
ejecución de forma correcta?

R: Non, non se esta liberando de maneira correcta, debemos realizar certos cambios:
        -No case 0: debemos engadir destruirMatriz(a) e destruirMatriz(b)
        -Sobra un destruiMatriz(aux) no case 6
        -No case 7 precisamos de punteiros de candenseu matriz apuntando a NULL
 */

#include "matriz.h"

int main(int argc, char** argv) {
    //int i, k, f, c;
    int f,c;
    //as variables i e k non son usadas, podrianse eliminar
    float valor;
    matriz *a = 0, *b = 0, *aux = 0;
    char opcion, resp;



    do {
        printf("---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case '0':
            //Engadimos as funcions destruitMatriz para liberar a memoria de forma correcta, por si non se usa o caso 7
                destruirMatriz(a);
                destruirMatriz(b);
                printf("Saliendo del programa\n");
                break;
            case '1':
                printf("Introduzca el numero de filas de la matriz 'a': ");
                //scanf("%f", &f); f trátase dun inteiro e non un flotante
                scanf("%d", &f);
                printf("Introduzca el numero de co1lumnas de la matriz 'a': ");
                scanf("%d", &c);
                a = crearMatriz(f, c);
                printf("Introduzca el numero de filas de la matriz 'b': ");
                scanf("%d", &f); // aqui tamen debe ser un int e non un float
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);

                break;
            case '2':
                printf("Matriz A\n");
                for (f = 0; f < a->filas; f++) {
                    for (c = 0; c < a->columnas; c++) {
                        printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                        scanf("%f", &valor);
                        asignarElemento(f, c, valor, a);
                    }
                }
                printf("Matriz B\n");
                for (f = 0; f < b->filas; f++) {
                    for (c = 0; c < b->columnas; c++) {
                        printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                        scanf("%f", &valor);
                        //asignarElemento(f, c, valor, a); o ultimo argumento debe ser b xa que é a mtriz sobre a que estamos traballando
                        asignarElemento(f, c, valor, b);
                    }
                }
                break;
            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');
                printf("Introduce fila y columna (fila columna): ");
                scanf("%d %d", &f, &c);
                if (resp == 'a') {
                    //valor = obtenerElemento(f, c, b); o argumento final debe ser a, xa que é a matriz seleccionada
                    valor = obtenerElemento(f, c, a);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                } else if (resp == 'b') {
                    //valor = obtenerElemento(f, c, a); o argumento final debe ser b xa que é e a matriz seleccionada
                    valor = obtenerElemento(f, c, b);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                }
                break;
            case '4':
                printf("Matriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;
            case '5':
                aux = suma(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                break;
            case '6':
                aux = producto(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                //destruirMatriz(aux); non fai falla destruila mais dunha vez
                break;
            case '7':
                // poñemos os NULL para que cadanseu punteiro apunte e eles
                destruirMatriz(a);
                a = NULL;
                destruirMatriz(b);
                b = NULL;
                printf("Matrices eliminadas...\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != '0');

    return (EXIT_SUCCESS);
}