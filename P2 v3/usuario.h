#ifndef USUARIO_H
#define USUARIO_H
#include "lista-1.h"
#include "cola-1.h"


// Declaramos las funciones relacionadas con USUARIO.


int comproba_email(TIPOELEMENTOLISTA *novo_usuario);
void alta_usuario(TLISTA *lista_usuarios, TIPOELEMENTOLISTA *novo_usuario, const char *nombre_fichero);
void baixa_usuario(TLISTA *lista_usuarios, TIPOELEMENTOLISTA *usuario, const char *nombre_fichero);
int comproba_usuario(TLISTA lista, const char *email);
void gardarlistaarquivo(TLISTA *lista_usuarios, const char *nombre_fichero);
void cargarlista(TLISTA *lista_usuarios, const char *nombre_fichero);
void _strip_line(char *linea);
void metercola(TLISTA *lista_usuarios, TCOLA *cola, int modo, int *n_solicitudes);
void numerocola(TCOLA cola);
void venderentradas(TCOLA *cola, int *n_solicitudes);

#endif // USUARIO_H