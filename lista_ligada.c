#include <stdio.h>
#include <stdlib.h>

#include "comparador.h"
#include "lista_ligada.h"

ListaLigada * cria_lista(){

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->primeiro = NULL;
	lista->tamanho = 0;
	
	return lista;
}

void destroi_lista(ListaLigada * lista){

	No * p = lista->primeiro;
	No * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}

	free(lista);
}

int tamanho(ListaLigada * lista){
  return lista->tamanho;
}

void imprime(ListaLigada * lista){

	No * p;

	printf("Lista:");

	for(p = lista->primeiro; p; p = p->proximo){

		printf(" %d", p->valor);
	}

	printf("\n");
}

int busca(ListaLigada * lista, Elemento e){

	int i = 0;
	No * p = lista->primeiro;

	while(p && lt(p->valor, e)){

		p = p->proximo;
		i++;
	}
	return p ? (eq(p->valor, e) ? i : -1) : -1;
}

Boolean insere_distinto(ListaLigada * lista, Indice e){

	No * p;
	No * anterior;
	No * novo = (No *) malloc(sizeof(No));

	novo->valor = e->valor;

	anterior = NULL;
	p = lista->primeiro;

	while(p){

		if(lt(e, p->valor)) break;
 	
    if (eq(e, p->valor)) {
      return TRUE;
    }

		anterior = p;
		p = p->proximo;
	}
	
	novo->proximo = p;
		
	if(anterior) anterior->proximo = novo;
	else lista->primeiro = novo;

  lista->tamanho++;
	return TRUE;
}

Boolean remove_elemento(ListaLigada * lista, Elemento e){

	int i, antecessor;
	int indice = busca(lista, e);
	No * p;
	No * tmp;

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
