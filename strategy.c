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
    indexador->imprime = imprime_AVL;
    indexador->busca = busca_AVL;
    return indexador;
  }

  if (eq_char(tipo, "lista")) {
    puts("Tipo de indice: 'lista'");     
    indexador->estrutura = cria_lista_ligada();
    indexador->insere = insere_sem_repeticao_lista_ligada;  
    indexador->imprime = imprime_lista_ligada;  
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
      indexador->busca(indexador->estrutura, argumento);
      continue;
    }
      
    puts("Comando inválido. Use 'busca <palavra>' ou 'fim'.");
    continue;
  } 
}

