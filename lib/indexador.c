#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <time.h> 

#include "indexador.h"

Indexador * cria_estrategia(char * tipo) {
	Indexador * indexador = (Indexador *) malloc (sizeof(Indexador));

  if (eq_char(tipo, ARVORE)) {
    indexador->estrutura = cria_arvore();
    indexador->estrategia = ARVORE;
    indexador->insere = insere_AVL;
    indexador->busca = busca_AVL;
    indexador->otimizar = null_fn;
    indexador->imprimir_detalhes = imprimir_detalhes_arvore;
    return indexador;
  }

  if (eq_char(tipo, LISTA)) {
    indexador->estrutura = cria_lista_ligada();
    indexador->estrategia = LISTA;
    indexador->insere = insere_lista_ligada;  
    indexador->busca = busca_lista_ligada;
    indexador->otimizar = otimizar_lista;
    indexador->imprimir_detalhes = null_fn;
    return indexador;
  }

  puts("Opcao invalida!");
  exit(1);
}

void menu_busca(Indexador * indexador) {
  char input[MAX_INPUT];
  char comando[MAX_INPUT];
  char argumento[MAX_INPUT];

  while (TRUE) {
    printf("> ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }

    input[strcspn(input, "\n")] = '\0';

    // Divide a entrada em comando e argumento (separados por espaço)
    int argumentosLidos = sscanf(input, "%s %s", comando, argumento);

    if (argumentosLidos == 1 && eq_char(comando, "fim")) {
      // puts("Encerrando o programa...");
      break;
    }
        
    if (argumentosLidos == 2 && eq_char(comando, "busca")) {
      double tempo_busca, tempo_diff;
      tempo_busca = clock();
	    
      Elemento * aux = (Elemento *) malloc (sizeof(Elemento));
      aux->valor = argumento;
      strlwr(aux->valor);
      
      Elemento * elemento = indexador->busca(indexador->estrutura, aux);

      if (elemento == NULL) {
        printf("Palavra '%s' nao encontrada.\n", argumento);
        
        tempo_diff = clock() - tempo_busca;
        printf("Tempo de busca: %.3lf ms\n", tempo_diff);
        
        continue;
      }
      
      printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", elemento->quantidade, argumento);
      imprime_occ(elemento->ocorrencias, indexador->lista_linhas);

      tempo_diff = clock() - tempo_busca;
      printf("Tempo de busca: %.3lf ms\n", tempo_diff);
      
      continue;
    }
      
    puts("Opcao invalida!");
    continue;
  } 
}

void setListaLinhas(Indexador * indexador, char ** lista_linhas) {
  indexador->lista_linhas = lista_linhas;
}

void otimizar_lista(Indexador * indexador) {
  ListaLigada * lista_ligada = indexador->estrutura;
  int tamanho_lista = tamanho_lista_ligada(lista_ligada);

  indexador->estrutura = cria_lista_sequencial(tamanho_lista);
  indexador->busca = busca_lista_sequencial;

  NoLista * p = lista_ligada->primeiro;
  for (int i = 0; i < tamanho_lista; i++) {
    insere_lista_sequencial(indexador->estrutura, p->elemento);
    p = p->proximo;
  }

  destroi_lista_ligada(lista_ligada);
}

void imprimir_detalhes_arvore(Indexador * indexador) {
  int altura = (( Arvore_AVL *) indexador->estrutura)->raiz->h;

  printf("Altura da arvore: %d\n", altura);
}

