#ifndef TYPES_H
#define TYPES_H

#define FALSE 0
#define TRUE 1

#define ARVORE "arvore"
#define LISTA "lista"

#define TAMANHO 10000

typedef struct no_occ {
    int valor; 
    struct no_occ * proximo;
} No_occ;

typedef struct {
    No_occ * primeiro;
    int tamanho;
} ListaOcc;

typedef struct {

  char * valor;
  int quantidade;
  ListaOcc * ocorrencias;

} Elemento;

typedef int Boolean;

#endif

