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

void imprime_lista_ligada(ListaLigada * lista){

	NoLista * p;

	printf("Lista:");

	for(p = lista->primeiro; p; p = p->proximo){

		printf(" %s", p->elemento->valor);
	}

	printf("\n");
}

int busca_lista_ligada(ListaLigada * lista, Elemento * e){

	int i = 0;
	NoLista * p = lista->primeiro;

	while(p && lt(p->elemento, e)){

		p = p->proximo;
		i++;
	}
	return p ? (eq(p->elemento, e) ? i : -1) : -1;
}

Boolean insere_sem_repeticao_lista_ligada(ListaLigada * lista, Elemento * e){
  return insere_lista_ligada(lista, e, TRUE);
}

Boolean insere_lista_ligada(ListaLigada * lista, Elemento * e, Boolean semRepeticao){

	NoLista * p;
	NoLista * anterior;
	NoLista * novo = (NoLista *) malloc(sizeof(NoLista));

	novo->elemento = e;
	anterior = NULL;
	p = lista->primeiro;

	while(p){

    if (eq(e, p->elemento) && semRepeticao) {
      free(e);
      e = p->elemento;
      return FALSE;
    }

		if(lt(e, p->elemento)) break;

		anterior = p;
		p = p->proximo;
	}
	
	novo->proximo = p;
		
	if(anterior) anterior->proximo = novo;
	else lista->primeiro = novo;

  lista->tamanho++;
	return TRUE;
}

Boolean remove_elemento_lista_ligada(ListaLigada * lista, Elemento * e){

	int i, antecessor;
	int indice = busca_lista_ligada(lista, e);
	NoLista * p;
	NoLista * tmp;

	if(indice >= 0) {

		if(indice == 0){

			tmp = lista->primeiro;
			lista->primeiro = tmp->proximo;
			free(tmp);
		}
		else{

			i = 0;
			antecessor = indice - 1;
			p = lista->primeiro;

			while(i < antecessor){

				i++;
				p = p->proximo;
			}
			
			tmp = p->proximo;
			p->proximo = tmp->proximo;
			free(tmp);
		}
		
    lista->tamanho--;
		return TRUE;
	}

	return FALSE;
}
