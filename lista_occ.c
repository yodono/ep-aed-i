#include <stdio.h>
#include <stdlib.h>

#include "lista_occ.h"

ListaOcc * cria_lista_occ(){
  ListaOcc * lista = (ListaOcc *) malloc (sizeof(ListaOcc));
  lista->primeiro = NULL;
  lista->tamanho = 0;

  return lista;
}

Boolean insere_occ_sem_repeticao(ListaOcc * lista, int l){
  return insere_occ(lista, l, TRUE);
}

Boolean insere_occ(ListaOcc * lista, int l, Boolean semRepeticao){
  No_occ * p;
  No_occ * anterior;
  No_occ * novo = (No_occ *) malloc(sizeof(No_occ));
    
  novo->valor = l;
	anterior = NULL;
	p = lista->primeiro;

	while(p){
    if (l == p->valor && semRepeticao) {
      free(novo);
      return FALSE;
    }

		if(l < p->valor) break;

		anterior = p;
		p = p->proximo;
	}
	
	novo->proximo = p;
		
	if(anterior) anterior->proximo = novo;
	else lista->primeiro = novo;

  lista->tamanho++;
	return TRUE;
}

void imprime_occ(ListaOcc * lista){
  No_occ * p; 
  printf("Aparece nas linhas:");

  for(p = lista->primeiro; p; p = p->proximo){
    printf(" %03d", p->valor);
  }

  printf("\n");
}

