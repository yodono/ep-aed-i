#ifndef INDEXADOR_H
#define INDEXADOR_H
#define MAX_INPUT 100

#include "utils.h"
#include "AVL.h"
#include "lista_ligada.h"

typedef struct {
  Elemento * elemento;
} NoGenerico;

typedef struct {
    void * estrutura;
    Boolean (* insere)(void * estrutura, Elemento * e);
    void (* imprime)(void * estrutura);
    NoGenerico (* busca)(void * estrutura, char * palavra);
} Indexador;

Indexador * cria_estrategia(char * tipo);
void menu_busca(Indexador * indexador);

#endif

