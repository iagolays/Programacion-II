#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "usuario.h"
#include "clave.h"


int main(int argc, char** argv){
    
    TIPOELEMENTOLISTA *user1 = (TIPOELEMENTOLISTA *) malloc(sizeof(TIPOELEMENTOLISTA)); //reservamos memoria para o usuario
    if(user1 == NULL){
        printf("Erro reservando memoria para o usuario\n");
        return(EXIT_FAILURE);
    }

    char opcion;
    clave clave1 = NULL;
    TLISTA lista_usuarios;
    TCOLA cola;
    int n_solicitudes = 0; //inicializamos o contador de solicitudes a 0

    char *nombre_fichero = "usuarios.txt";  // valor por defecto

    // Procesas línea de comandos
    int opt;
    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                nombre_fichero = optarg;
                break;
            default:
                fprintf(stderr, "Uso: %s [-f nome_arquivo]\n", argv[0]);
                return 1;
        }
    }

    

    crearCola(&cola); //creamos a cola
    crearLista(&lista_usuarios);
    cargarlista(&lista_usuarios, nombre_fichero); //cargamos a lista de usuarios
    
    do{
        printf("\n--------------------\n");
        printf("\nElixa unha opción: ");
        printf("\na) Dar de alta un usuario");
        printf("\nb) Dar de baixa un usuario");
        printf("\nc) Engadir un usuario á cola");
        printf("\nd) Mostrar o número de usuarios na cola");
        printf("\ne) Vender entradas");
        printf("\ns) Sair do programa");
        printf("\nOpcion: ");
        scanf(" %c",&opcion);
        printf("\n--------------------\n");


        switch(opcion){
            case 'a':
            alta_usuario(&lista_usuarios,user1, nombre_fichero);
            break;
            case 'b':
            baixa_usuario(&lista_usuarios,user1, nombre_fichero);
            break;
            case 'c':
            metercola(&lista_usuarios,&cola,0, &n_solicitudes);
            break;
            case 'd':
            metercola(&lista_usuarios,&cola,1, &n_solicitudes);
            break;
            case 'e':
            venderentradas(&cola, &n_solicitudes);
            break;
            

        }
            
    }while(opcion != 's');
    destruirLista(&lista_usuarios); //destruimos a lista de usuarios
    free(user1); //liberamos a memoria do usuario
    destruirCola(&cola); //destruimos a cola
    printf("\nSaiuse do programa\n");
    printf("\n--------------------\n");

    return(EXIT_SUCCESS);
}