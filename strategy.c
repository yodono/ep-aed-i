#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#include "strategy.h"

Indexador * cria_estrategia(char * tipo) {
	Indexador * indexador = (Indexador *) malloc (sizeof(Indexador));

  if (eq_char(tipo, "arvore")) {
    puts("Tipo de indice: 'arvore'");     
    indexador->estrutura = cria_arvore();
    indexador->insere = insere_AVL;
    indexador->busca = busca_AVL;
    return indexador;
  }

  if (eq_char(tipo, "lista")) {
    puts("Tipo de indice: 'lista'");     
    indexador->estrutura = cria_lista_ligada();
    indexador->insere = insere_sem_repeticao_lista_ligada;  
    indexador->busca = busca_lista_ligada;  
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
      
      NoGenerico * no = indexador->busca(indexador->estrutura, aux);

      if (no == NULL) {
        printf("Palavra '%s' nao encontrada.\n", argumento);
        continue;
      }
      
      printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", no->elemento->quantidade, argumento);
      imprime_occ(no->elemento->ocorrencias, indexador->lista_linhas);

      continue;
    }
      
    puts("Comando inválido. Use 'busca <palavra>' ou 'fim'.");
    continue;
  } 
}

void setListaLinhas(Indexador * indexador, char ** lista_linhas) {
  indexador->lista_linhas = lista_linhas;
}

