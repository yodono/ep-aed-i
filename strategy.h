#ifndef INDEXADOR_H
#define INDEXADOR_H
#define MAX_INPUT 100

#include "utils.h"
#include "types.h"
#include "comparador.h"
#include "AVL.h"
#include "lista_ligada.h"
#include "lista_occ.h"

typedef struct {
  Elemento * elemento;
} NoGenerico;

typedef struct {
    void * estrutura;
    Boolean (* insere)(void * estrutura, Elemento ** e);
    NoGenerico * (* busca)(void * estrutura, Elemento * e);
} Indexador;

Indexador * cria_estrategia(char * tipo);
void menu_busca(Indexador * indexador);

#endif

