#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Para getopt()
#include "clave.h"
#include "lista-1.h"
#include "usuario.h"
#include "cola-1.h"

void _strip_line(char *linea) {
    linea[strcspn(linea, "\r\n")] = 0;
}


int comproba_email(TIPOELEMENTOLISTA *novo_usario){
    if(novo_usario->email == NULL || strlen(novo_usario->email) == 0){
        return 0;
    }
    
    char *arroba = strchr(novo_usario->email, '@');
    if(arroba == NULL || arroba == novo_usario->email || *(arroba+1) == '\0'){
        return 0;
    }
    return 1;

}

int comproba_usuario(TLISTA lista, const char *email){

    if (esListaVacia(lista)) { 
        return 0; // si esta vacia o usuario no existe.
    }

    TPOSICION p = primeroLista(lista);
    TIPOELEMENTOLISTA usuario;
    
    while (p != finLista(lista)) {
        recuperarElementoLista(lista, p, &usuario);
        if (strcmp(usuario.email, email) == 0) {
            return 1; // usuario xa existe
        }
        p = siguienteLista(lista, p);
    }
    return 0; // usuario non existe
}


void gardarlistaarquivo(TLISTA *lista_usuarios, const char *nombre_fichero){
    FILE *fichero;
    TPOSICION p = primeroLista(*lista_usuarios);
    TIPOELEMENTOLISTA usuario;
    
    fichero = fopen(nombre_fichero, "w");
    if (fichero == NULL) {
        printf("Error ao abrir o arquivo.\n");
        return;
    }
    
    while (siguienteLista(*lista_usuarios, p) != NULL) {
        recuperarElementoLista(*lista_usuarios, p, &usuario);
        fprintf(fichero, "%s,%s,%s,%d,%s\n", usuario.email, usuario.nome, usuario.apelidos, usuario.idade, usuario.contrasinal);
        p = siguienteLista(*lista_usuarios, p);
    }
    
    fclose(fichero);
}


void cargarlista(TLISTA *lista_usuarios, const char *nombre_fichero){
    FILE *fichero;
    TIPOELEMENTOLISTA usuario;
    char linea[250];
    

    fichero = fopen(nombre_fichero, "r");

    // si o arquivo non existe, creamolo e abrimolo en modo escritura
    if (fichero == NULL) {
        printf("O arquivo '%s' non existe. Creando...\n", nombre_fichero);
        fichero = fopen(nombre_fichero, "w");
        if (fichero == NULL) {
            printf("Erro ao crear o arquivo.\n");
            return;
        }
        fclose(fichero);
        fichero = fopen(nombre_fichero, "r");
        if (fichero == NULL) {
            printf("Erro ao reabrir o arquivo.\n");
            return;
        }
    }

    if (fichero == NULL) {
        printf("Error ao abrir o arquivo.\n");
        return;
    }
    
    while (fgets(linea, sizeof(linea), fichero) != NULL) {
        _strip_line(linea);
        sscanf(linea, "%[^,],%[^,],%[^,],%d,%s", usuario.email, usuario.nome, usuario.apelidos, &usuario.idade, usuario.contrasinal);
        insertarElementoLista(lista_usuarios, finLista(*lista_usuarios), usuario);
    }
    
    fclose(fichero);
}



void baixa_usuario(TLISTA *lista_usuarios, TIPOELEMENTOLISTA *usuario, const char *nombre_fichero){
    
    char email[50];
    char contrasinal[50];
    TPOSICION p = primeroLista(*lista_usuarios);
    printf("\nIntroduce o correo do usuario a eliminar: ");
    scanf("%s", email);
    printf("\nIntroduce o contrasinal do usuario a eliminar: ");
    scanf("%s", contrasinal);
    

    while (p != finLista(*lista_usuarios)) {
        recuperarElementoLista(*lista_usuarios, p, usuario);

        if(strcmp(usuario->email, email) == 0 && strcmp(usuario->contrasinal, contrasinal) == 0) {
            printf("\nUsuario encontrado\n");
            TPOSICION temp = p;
            p = siguienteLista(*lista_usuarios, p);
            suprimirElementoLista(lista_usuarios, temp);
            printf("\nUsuario eliminado correctamente\n");
            
            // actualizamos o arquivo usuarios.txt eliminando o usuario
            gardarlistaarquivo(lista_usuarios, nombre_fichero);
            printf("\nO arquivo usuarios.txt foi actualizado\n");
            return;
        }
        p = siguienteLista(*lista_usuarios, p);
    }
    
}



void alta_usuario(TLISTA *lista_usuarios, TIPOELEMENTOLISTA *novo_usuario, const char *nombre_fichero){

    clave clave1 = NULL;
    
    printf("\nIntroduce o teu correo electronico: ");
    scanf("%s", novo_usuario ->email);
    

    // comprobamos se o correo ten un formato válido
    if (comproba_email(novo_usuario)) {
        printf("Email válido\n");
    } else {
        printf("Email inválido\n");
        return;
    }
    // comprobamos se o correo xa está rexistrado (devolviamos 0 ou 1 asi q co if xa podemos decidir)
    if (comproba_usuario(*lista_usuarios, novo_usuario->email)) {
        printf("O correo xa está rexistrado.\n");
        return;  
    }


    printf("\nIntroduce o teu nome: ");
    scanf("%s", novo_usuario ->nome);

    printf("\nIntroduce os teu apelidos: "); // usamos fgets para ler toda a liña evitando os problemas cos espazos
    getchar(); // limpamos o buffer para evitar problemas co '\n'
    fgets(novo_usuario->apelidos, sizeof(novo_usuario->apelidos), stdin);
    //eliminamos o '\n' que queda ao final da lectura
    size_t len = strlen(novo_usuario->apelidos);
    if (len > 0 && novo_usuario->apelidos[len - 1] == '\n') {
        novo_usuario->apelidos[len - 1] = '\0';
    }

    printf("\nIntroduce a tua idade: ");
    scanf("%d", &novo_usuario ->idade);

    while (novo_usuario ->idade < 18){
        printf("\nA idade introducida debe ser igual ou superior a 18");
        printf("\nIntroduce unha idade válida: ");
        scanf("%d", &novo_usuario ->idade);
    }
    
    printf("\nIntroduce o teu contrasinal: ");
    scanf("%s", novo_usuario ->contrasinal);
    //cadena2clave(novo_usuario ->contrasinal, &clave1);
    printf("\nO usuario foi creado correctamente");
    

    insertarElementoLista(lista_usuarios, finLista(*lista_usuarios), *novo_usuario);
    gardarlistaarquivo(lista_usuarios, nombre_fichero);
    printf("\nOs datos foron gardados no arquivo usuarios.txt\n");
}

void metercola(TLISTA *lista_usuarios, TCOLA *cola, int modo, int *n_solicitudes){
    char email[50];
    char contrasinal[50];
    TIPOELEMENTOLISTA usuario;
    TPOSICION p;

    // comprobamos se a lista de usuarios está vacia
    if(esListaVacia(*lista_usuarios)){
        printf("Non hai usuarios dados de alta\n");
        return;
    }
    if(modo == 1){
        printf("O numero de solicitudes na cola é: %d\n", *n_solicitudes);
        return;
    }
    //creamos o bucle infinito para que o usuario poida introducir varios usuarios
    while(1) {
        printf("\nIntroduce o teu correo electrónico (0 para sair): ");
        scanf("%s", email);

        if (strcmp(email, "0") == 0) {  // si o email é "0", salimos do bucle
            break;
        }

        printf("Introduce o teu contrasinal: ");
        scanf("%s", contrasinal);

        // anicializamos a variable para comprobar si encontramos al usuario
        int encontrado = 0;

        // recorremos la lista de usuarios para buscar el email y la contraseña
        p = primeroLista(*lista_usuarios);
        while (p != finLista(*lista_usuarios)) {
            recuperarElementoLista(*lista_usuarios, p, &usuario);

            // verificamos si o email e a contraseña coinciden
            if (strcmp(usuario.email, email) == 0 && strcmp(usuario.contrasinal, contrasinal) == 0) {
                printf("Datos correctos\n");

                // engadimos o usuario á cola usando o seu email
                anadirElementoCola(cola, usuario.email);

                printf("Usuario engadido á cola correctamente\n");
                encontrado = 1;
                (*n_solicitudes) ++; // incrementamos o número de solicitudes
                break;  // aalimos do bucle si encontramos o usuario
            }
            p = siguienteLista(*lista_usuarios, p);
        }

        // si non encontramos ao usuario ou a contraseña é incorrecta
        if (!encontrado) {
            printf("Usuario non atopado ou contrasinal incorrecto.\n");
        }
    }


    printf("Saindo da solicitude de cola\n");
    
}

void venderentradas(TCOLA *cola, int *n_solicitudes){
    TIPOELEMENTOCOLA usuario;
    int n_entradas = 0;

    //primeiro comprobamos se a cola está vacia
    if (esColaVacia(*cola)) {
        printf("A cola para as entradas está vacía\n");
        printf("Quedaron %d entradas por vender\n", n_entradas);
        return;
    }

    printf("Introduce o número de entradas a vender: ");
    scanf("%d", &n_entradas);

    for(int i = 0; i < n_entradas; i++) {
        if (esColaVacia(*cola)) {
            printf("Non hai máis usuarios na cola\n");
            break;
        }
        //consultamos o primeiro elemento da cola
        consultarPrimerElementoCola(*cola, &usuario);
        printf("A entrada vendeselle a %s\n", usuario);
        //suprimimos o primeiro elemento da cola
        suprimirElementoCola(cola);
        //actualizamos o número de solicitudes
        (*n_solicitudes)--;
        n_entradas--;
    }
    printf("Entradas vendidas correctamente\n");
    printf("Quedaron %d entradas por vender\n", n_entradas);
    
    

    
}