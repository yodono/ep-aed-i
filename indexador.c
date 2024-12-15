#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#include "indexador.h"

Indexador * cria_estrategia(char * tipo) {
	Indexador * indexador = (Indexador *) malloc (sizeof(Indexador));

  printf("Tipo de indice: '%s'\n", tipo);

  if (eq_char(tipo, ARVORE)) {
    indexador->estrutura = cria_arvore();
    indexador->estrategia = ARVORE;
    indexador->insere = insere_AVL;
    indexador->busca = busca_AVL;
    indexador->otimizar = null_fn;
    return indexador;
  }

  if (eq_char(tipo, LISTA)) {
    indexador->estrutura = cria_lista_ligada();
    indexador->estrategia = LISTA;
    indexador->insere = insere_lista_ligada;  
    indexador->busca = busca_lista_ligada;
    indexador->otimizar = otimizar_lista;
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
      puts("Encerrando o programa...");
      break;
    }
        
    if (argumentosLidos == 2 && eq_char(comando, "busca")) {
	    Elemento * aux = (Elemento *) malloc (sizeof(Elemento));
      aux->valor = argumento;
      strlwr(aux->valor);
      
      Elemento * elemento = indexador->busca(indexador->estrutura, aux);

      if (elemento == NULL) {
        printf("Palavra '%s' nao encontrada.\n", argumento);
        continue;
      }
      
      printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", elemento->quantidade, argumento);
      imprime_occ(elemento->ocorrencias, indexador->lista_linhas);

      continue;
    }
      
    puts("Comando inválido. Use 'busca <palavra>' ou 'fim'.");
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

