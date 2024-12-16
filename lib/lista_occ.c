#include <stdio.h>
#include <stdlib.h>

#include "lista_occ.h"

ListaOcc * cria_lista_occ(){
  ListaOcc * lista = (ListaOcc *) malloc (sizeof(ListaOcc));
  lista->primeiro = NULL;
  lista->tamanho = 0;

  return lista;
}

typedef enum { FALSE, TRUE } Boolean;

// Função para criar uma lista de ocorrências
ListaOcc *cria_lista_occ() {
    ListaOcc *lista = (ListaOcc *)malloc(sizeof(ListaOcc));
    if (lista == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memória para a lista.\n");
        exit(EXIT_FAILURE);
    }
    lista->primeiro = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para inserir uma ocorrência na lista (mantendo ordenação)
Boolean insere_occ(ListaOcc *lista, int l) {
    No_occ *p, *anterior, *novo;

    novo = (No_occ *)malloc(sizeof(No_occ));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memória para o nó.\n");
        exit(EXIT_FAILURE);
    }

    novo->valor = l;
    novo->proximo = NULL;

    anterior = NULL;
    p = lista->primeiro;

    // Insere na posição correta, mantendo a lista ordenada
    while (p) {
        if (l == p->valor) {
            free(novo);  // Valor já existe, libera memória
            return FALSE;
        }
        if (l < p->valor)
            break;

        anterior = p;
        p = p->proximo;
    }

    novo->proximo = p;

    if (anterior)
        anterior->proximo = novo;
    else
        lista->primeiro = novo;

    lista->tamanho++;
    return TRUE;
}

// Função para imprimir as ocorrências
void imprime_occ(ListaOcc *lista, char **lista_linhas, int num_linhas) {
    No_occ *p = lista->primeiro;

    while (p) {
        if (p->valor < 0 || p->valor >= num_linhas) {
            fprintf(stderr, "Erro: índice %d fora dos limites do array de linhas.\n", p->valor);
            exit(EXIT_FAILURE);
        }

        printf("%05d %s\n", p->valor + 1, lista_linhas[p->valor]);
        p = p->proximo;
    }
}
