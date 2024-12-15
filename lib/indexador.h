#ifndef INDEXADOR_H
#define INDEXADOR_H
#define MAX_INPUT 100

#include "utils.h"
#include "types.h"
#include "comparador.h"
#include "AVL.h"
#include "lista_ligada.h"
#include "lista_occ.h"
#include "lista_sequencial_ordenada.h"

typedef struct {
  Elemento * elemento;
} NoGenerico;

typedef struct _indexador {
    void * estrutura;
    char * estrategia;
    char ** lista_linhas;
    Boolean (* insere)(void * estrutura, Elemento ** e);
    NoGenerico * (* busca)(void * estrutura, Elemento * e);
    void (* otimizar)(struct _indexador * indexador);
    void (* imprimir_detalhes)(struct _indexador * indexador);
} Indexador;

Indexador * cria_estrategia(char * tipo);
void menu_busca(Indexador * indexador);
void setListaLinhas(Indexador * indexador, char ** lista_linhas);
void otimizar_lista(Indexador * indexador);
void imprimir_detalhes_arvore(Indexador * indexador);

#endif

