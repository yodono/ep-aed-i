#include <stdio.h>
#include <stdlib.h>

#include "lista_ligada.h"

ListaLigada * cria_lista_ligada(){

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->primeiro = NULL;
	lista->tamanho = 0;
	
	return lista;
}

void destroi_lista_ligada(ListaLigada * lista){

	NoLista * p = lista->primeiro;
	NoLista * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(lista);
}

int tamanho_lista_ligada(ListaLigada * lista){
  return lista->tamanho;
}

Elemento * busca_lista_ligada(ListaLigada * lista, Elemento * e){
	NoLista * p = lista->primeiro;

	while(p && lt(p->elemento, e)){
		p = p->proximo;
	}

	return p ? (eq(p->elemento, e) ? p->elemento : NULL) : NULL;
}

Boolean insere_lista_ligada(ListaLigada * lista, Elemento ** e){

	NoLista * p;
	NoLista * anterior;
	NoLista * novo = (NoLista *) malloc(sizeof(NoLista));

	novo->elemento = *e;
	anterior = NULL;
	p = lista->primeiro;

	while(p){

    if (eq(*e, p->elemento)) {
      free(novo);
      *e = p->elemento;
      return FALSE;
    }

		if(lt(*e, p->elemento)) break;

		anterior = p;
		p = p->proximo;
	}
	
	novo->proximo = p;
		
	if(anterior) anterior->proximo = novo;
	else lista->primeiro = novo;

  lista->tamanho++;
	return TRUE;
}

