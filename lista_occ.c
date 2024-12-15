#include <stdio.h>
#include <stdlib.h>

#include "lista_occ.h"

ListaOcc * cria_lista_occ(){
  ListaOcc * lista = (ListaOcc *) malloc (sizeof(ListaOcc));
  lista->primeiro = NULL;
  lista->tamanho = 0;

  return lista;
}

Boolean insere_occ(ListaOcc * lista, int l){
  No_occ * p;
  No_occ * anterior;
  No_occ * novo = (No_occ *) malloc(sizeof(No_occ));
    
  novo->valor = l;
	anterior = NULL;
	p = lista->primeiro;

	while(p){
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

  for(p = lista->primeiro; p; p = p->proximo){
    // soma uma unidade para o valor "apresentavel" da linha
    printf("%05d", p->valor + 1);
  }

  printf("\n");
}

