#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clave.h"
int main(int argc, char** argv) {
    srand(time(NULL));
    clave clave1 = NULL;
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
        printf("\nb) Liberar clave");
        printf("\nc) Recuperar posición dunha clave");
        printf("\nd) Lonxitude da clave");
        printf("\ne) Imprimir clave sen ocultar caracteres");
        printf("\nf) Imprimir clave ocultando todos os caracteres");
        printf("\ng) Imprimir clave ocultando alguns dos caracteres");
        printf("\nh) Crea clave a partir dunha cadea de texto");
        printf("\ni) Comproba contraseña (completa)");
        printf("\nj) Comproba contraseña (partes)");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf(" %c",&opcion);
        switch(opcion){
            case 'a':
                liberar(&clave1);
                printf("\nIntroduce el tamaño de la clave: ");
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
                }
                break;
            case 'b':
                liberar(&clave1);
                break;
            case 'c':
                printf("\nIntroduce a posición que queres recuperar: ");
                scanf(" %hu", &posicion);
                TELEMENTO v_r = recuperar(clave1, posicion);
                if(v_r != NULL){
                    printf("\nO elemento é: %c", v_r);
                }
                break;
            case 'd':
                if(lonxitude(clave1) != 0){
                    printf("A lonxitude é: %d", lonxitude(clave1));
                }
                else  
                    printf("A lonxitude é 0 ou a clave non existe");
                break;
            case 'e':
                imprimir(clave1,0);
                break;
            case 'f':
                imprimir(clave1,1);
                break;
            case 'g':
                imprimir(clave1,2);
                break;
            case 'h':
                char cadea[100];
                printf("\nIntroduce a tua cadea: ");
                scanf(" %s", cadea);
                printf("\nIntroduce o número de cifrado: ");
                scanf(" %hu", &cifrado);
                cadena2clave(cadea, &clave1, cifrado);
                break;
            case 'i':
                compruebaclave(clave1, 0);
                break;
            case 'j':
                compruebaclave(clave1, 1);
                break;
            case 's':
                printf("\nSalimos del programa\n");
                break;
            default:
                printf("Opcion incorrecta\n");
        }
        
    }while (opcion!='s');

    return (EXIT_SUCCESS);
}