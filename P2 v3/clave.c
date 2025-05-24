#include <stdlib.h>  // para malloc, free, etc
#include <stddef.h>  // para non amosar erro co NULL
#include <stdio.h>  // para printf
#include <string.h> //para strlen

typedef char TELEMENTO;
/* tipo de datos de los elementos de la contraseña */

/* implementación, ahora ya no es opaca pues estamos en el .c de
la librería, del tipo clave */

typedef struct {
    TELEMENTO *datos; /*caracteres de la contraseña*/
    unsigned short tam; /*tamaño de la clave*/
    unsigned short cifrado; /*numero para el cifrado*/
}STCLAVE;   /*definición del tipo de datos estructura*/
typedef STCLAVE *clave; /*puntero a estructura*/        

/* para crear una clave se proporciona un puntero a la dirección de
memoria donde el TAD almacenará la clave, la función crear del TAD
asignará memoria, y guardará encapsuladamente la longitud y número
de cifrado de la clave */

void crear(clave *c, unsigned short longitud, unsigned short cifrado){
    unsigned short i;

    /* crea espacio para el struct */
    *c = (clave) malloc(sizeof(STCLAVE));

    /* dentro del struct creamos el bloque dinámico para almacenar los
    caracteres de la clave */
    (*c)->datos = (TELEMENTO *) malloc(longitud*sizeof(TELEMENTO));

    /* guardamos el tamaño y número de cifrado como datos encapsulados en el
    struct del TAD */
    (*c)->tam = longitud;
    (*c)->cifrado = cifrado;

    /* inicializamos la contraseña a letras a */

    for (i=0; i<longitud; i++)
        *((*c)->datos + i) = 'a';
}

/* para introducir individualmente cada posición de la clave */
void asignar(clave *c, unsigned short posicion, TELEMENTO valor){
    /* en lugar de asignar el valor que nos dan representamos el carácter
    ASCII correspondiente a ese carácter ASCII desplazado el offset que
    corresponda según su posición en la clave y el número de cifrado*/
    *((*c)->datos + posicion) = valor + posicion*(*c)->cifrado;
}

void liberar(clave *c){
    if (*c != NULL){
        if((*c)->datos != NULL){
            free((*c)->datos);
            (*c)->datos = NULL;
        }
        free((*c));
        (*c)= NULL;
        printf("\nA clave liberouse con éxito");
    }
    else{
        printf("\nNon hai ningunha clave que liberar");
    }
}

TELEMENTO recuperar(clave c, unsigned short posicion){
    TELEMENTO recuperado;
    if(c == NULL || posicion >= c->tam){
        printf("\nNon hai clave ou a posición introducida é invalida");
        return 0;
    }
    else{
        return recuperado = *((c)->datos + posicion) - posicion * (c)->cifrado; //Desciframos despexando "valor"
    }
}

unsigned short lonxitude(clave c){
    return c ? c->tam : 0;
}


void imprimir(clave c, int modo){
    if(c != NULL){

        if(modo == 0){
            for(unsigned short i=0; i<(c)->tam;i++){
                printf("%c", recuperar(c, i));
            }
        }
        else if(modo == 1){
            for(unsigned short i=0;i<(c)->tam;i++){
                printf("*");
            }
        }
        else if(modo == 2){
            for(unsigned short i=0; i<(c)->tam;i++){
                if(rand()%2 == 0){
                    printf("*");
                }
                else{
                    printf("%c", recuperar(c, i));
                }
            }
        }
    }
    else{
        printf("\nNon existe unha clave");
    }
}

void cadena2clave(const char *cadena, clave *c, unsigned short cifrado){
    unsigned short tam = strlen(cadena);
    crear(c, tam, cifrado);
    for(unsigned short i = 0; i<tam; i++){
        asignar(c,i,cadena[i]);
    }
}

int compruebaclave(clave c, int modo){
    if (c == NULL) {
        printf("Non hai clave gardada.\n");
        return 0;
    }

    char entrada[(c)->tam + 1];
    unsigned short tam = (c)->tam;
    
    if(modo == 0){
        printf("Introduce a clave completa: ");
        scanf("%s", entrada);

        if (strlen(entrada) != tam) {
            printf("A clave introducida non é correcta (lonxitude incorrecta).\n");
            return 0;
        }

        for (unsigned short i = 0; i < tam; i++) {
            if (entrada[i] != recuperar(c, i)) {
                printf("A clave introducida non é correcta.\n");
                return 0;
            }
        }
        printf("A clave introducida é correcta.\n");
        return 0;
    }
    else if(modo == 1){
        char claveOculta[tam + 1];
        int ind_ocultos[c->tam];
        unsigned short n_ocultos = 0;

        printf("\nClave real: ");
        for (unsigned short i = 0; i < c->tam; i++){
            //Proceso de ocultado dos caracteres
            if(rand() % 2 == 0){
                printf("*");
                claveOculta[i] = '*';
                //almacenamos as posición dos caracteres ocultos
                ind_ocultos[n_ocultos++] = i;
            }
            else{
                claveOculta[i] = recuperar(c, i);
                printf("%c", claveOculta[i]);
            }
        }

        claveOculta[c->tam] = '\0';
        printf("\nIntroduce os %hu caracteres ocultos por orden: ", n_ocultos);
        scanf(" %s", entrada);

        if (strlen(entrada) != n_ocultos) {
            printf("A clave introducida non é correcta (lonxitude incorrecta).\n");
            return 0;
        }

        for (unsigned short j = 0; j < n_ocultos; j++){
            if (entrada[j] != recuperar(c, ind_ocultos[j])){
                return 0;
            }
        }
        printf("\nA clave introducida foi correcta");
        return 1;
    }
    return 0;
} 


