#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quicksort.h"
#include "insertionsort.h"

#define ARRAYSIZE 1000

void generararray(int array[], int tam, int max_valor) {
    for (int i = 0; i < tam; i++) {
        array[i] = (rand() % max_valor) + 1; // xera números aleatorios entre 0 e o numero desexado
    }
}

//garda os resultados no arquivo
//o formato do arquivo e: tam tempo
void gardar_resultados(const char *archivo, int tam, double tempo){
    //abrimos o arquivo en modo append
    FILE *f = fopen(archivo, "a");
    if (f == NULL) {
        printf("Error ao abrir o archivo %s\n", archivo);
        return;
    }
    //gardamos os resultados no arquivo
    fprintf(f, "%d %f\n", tam, tempo);
    fclose(f);

}

void gardar_parametros(const char *archivo, int tam_inicial, int tam_final, int paso){
    //abremos o arquivo en modo escritura
    //se o arquivo xa existe, o seu contido será borrado
    //se non existe, será creado
    FILE *f = fopen(archivo, "w");
    if (f == NULL) {
        printf("Error ao abrir o archivo %s\n", archivo);
        return;
    }
    //gardamos os parametros no arquivo
    fprintf(f, "----------\n%d %d %d\n-----------\n", tam_inicial, tam_final, paso);
    fclose(f);
}


void inicializaVectorRand(int *v1, int tam) {
    for (int i = 0; i < tam; i++) {
        v1[i] = rand() % 101; // Números entre 0 y 100
    }
}

// Función que busca y cuenta pares que sumen la cantidad dada (imprime también)
int buscarPares(int *vector, int tam, int cantidad) {
    int contador = 0;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (vector[i] + vector[j] == cantidad) {
                //printf("Par encontrado: (%d, %d)\n", vector[i], vector[j]);
                contador++;
            }
        }
    }
    printf("Total de pares encontrados: %d\n", contador);
    return contador;
}


int main(int argc, char *argv[]) {
    if(argc !=4){
        printf("Uso: %s <tam> <max_valor> <archivo>\n", argv[0]);
        return 1;
    }
    
    //seleccionamos o tamaño inicial, o final e o paso
    int tam_inicial = atoi(argv[1]);
    int tam_final = atoi(argv[2]);
    int paso = atoi(argv[3]);

    if(tam_inicial <= 0 || tam_final <= 0 || paso <= 0) {
        printf("Os valores deben ser maiores ca 0\n");
        return 1;
    }

    int opcion;
    
    printf("\n--- Menú ---\n");
    printf("1. Ordenar con QuickSort\n");
    printf("2. Ordenar con Insertion Sort\n");
    printf("3. Buscar por pares \n");
    printf("Seleccione unha opción: ");
    scanf("%d", &opcion);
    //valor pordefecto para a opción 3
    //se non se selecciona a opción 3, a cantidad de pares a buscar será 100
    int cantidadObjetivo = 100;

    if(opcion < 1 || opcion > 4) {
        printf("Opción non válida\n");
        return 1;
    }

    int max_valor;
    const char *archivo_final;

    //definimos o tamaño máximo do array e o arquivo de resultados segundo a opción seleccionada
    if (opcion == 1) {
        max_valor = 10000;
        archivo_final = "resultados_quicksort.txt";
    } else if (opcion == 2) {
        max_valor = 10000;
        archivo_final = "resultados_insertion.txt";
    } else if (opcion == 3) {
        max_valor = 100;
        archivo_final = "resultados_pares.txt";
        //pedimos a cantidade que deben sumar os pares
        printf("Introduce a cantidade que deben sumar os pares: ");
        scanf("%d", &cantidadObjetivo);
    }


    //gardamos os parametros no arquivo
    gardar_parametros(archivo_final, tam_inicial, tam_final, paso);
    // Inicializamos o xerador de números aleatorios
    srand(time(NULL));

    //incializamos un contador para dar feedback de por onde vai o proceso
    int total_iteraciones = ((tam_final - tam_inicial) / paso) + 1;
    int contador_iteracion = 0;

    //Reservanos memoria para o array
    for(int tam = tam_inicial; tam <= tam_final; tam += paso) {
        
        contador_iteracion++;

        int *array = (int *)malloc(tam * sizeof(int));
        if(array == NULL) {
            printf("Error ao alocar memoria\n");
            return 1;
        }

        //xeramos o array
        generararray(array, tam, max_valor);
        if (opcion == 3) {
            //se a opción seleccionada é a 3, inicializamos o array con números entre 0 e 100
            inicializaVectorRand(array, tam);
        }
        
        //preparamos o temporizador
        clock_t inicio = clock();


        if(opcion == 1) {
            //ordenamos co quicksort
            quickSort(array, 0, tam - 1);
        } else if(opcion == 2) {
            //ordenamos co insertionsort
            insertionSort(array, tam);
        } else if(opcion == 3) {
            buscarPares(array, tam, cantidadObjetivo);
        }
        //medimos o tempo final
        clock_t fin = clock();
        //calculamos o tempo total
        double tempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;
        //gardamos os resultados no arquivo
        gardar_resultados(archivo_final, tam, tempo_total);

        int porcentaje = (contador_iteracion * 100) / total_iteraciones;
        printf("[Progreso: %d%%] Tamaño: %d Tiempo: %.6f segundos\n", porcentaje, tam, tempo_total);

        //liberamos a memoria
        free(array);

        
    }
    printf("O proceso foi realizado correctamente");
    return 0;
    
}