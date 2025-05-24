#include <stdio.h>
#include <stdlib.h>
#include "clave.h"
int main(int argc, char** argv) {
    clave clave1;
    unsigned short longitud, cifrado, posicion;
    TELEMENTO valor;
    char opcion;

    if(argc == 2){
        for( int i = 0; i < argc; i++){
            printf("%s\n",argv[i]);
        }
        printf("Número de argumentos invalido\n");
    }
    else if(argc >= 3){

        longitud = argc -2; //cantidad de caracteres de la clave

        cifrado = (unsigned short) strtoul(argv[argc - 1], NULL, 10);

        crear(&clave1, longitud, cifrado);

        for (posicion=0;posicion<longitud;posicion++){
            valor = (TELEMENTO) argv[posicion + 1][0]; 
            asignar(&clave1,posicion,valor);
        }

        printf("A clave ten %hu elementos e con cifrado %hu", longitud, cifrado);

    }
    do{
        printf("\n--------------------\n");
        printf("\na) Crea clave");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf(" %c",&opcion);
        switch(opcion){
            case 'a':
                printf("Introduce el tamaño de la clave: ");
                scanf("%hu",&longitud);
                printf("Introduce el número para cifrar la clave: ");
                scanf("%hu",&cifrado);
                crear(&clave1,longitud,cifrado);
                /*Asigno valores a la clave a partir de lo que teclea el
                usuario*/
                for (posicion=0;posicion<longitud;posicion++)
                {
                printf("Elemento %d de la clave: ",posicion);
                scanf(" %c",&valor);
                asignar(&clave1,posicion,valor);
                printf("%s\n",argv[posicion]);
                }
                for( int i = 0; i < sizeof(argc); i++){
                    printf(argv[i]);
                }
                break;
            case 's':
                printf("Salimos del programa\n");
                break;
            default:
                printf("Opcion incorrecta\n");
            }
    }while (opcion!='s');

    return (EXIT_SUCCESS);
}