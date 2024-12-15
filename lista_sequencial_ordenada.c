#include <stdio.h>
#include <stdlib.h>

#include "lista_sequencial_ordenada.h"

ListaSequencial * cria_lista_sequencial(int capacidade){

	ListaSequencial * lista = (ListaSequencial *) malloc (sizeof(ListaSequencial));
	lista->a = (Elemento **) malloc (capacidade * sizeof(Elemento));
	lista->capacidade = capacidade;
	lista->livre = 0;

	return lista;
}

void destroi_lista_sequencial(ListaSequencial * lista){
	free(lista->a);
	free(lista);
}

int tamanho_lista_sequencial(ListaSequencial * lista){
	return lista->livre;
}

int busca_lista_sequencial(ListaSequencial * lista, Elemento * e){

	// busca binária! ;)

	int ini = 0;
	int fim = lista->livre - 1;
	int meio;

	while(ini <= fim){

		meio = (ini + fim) / 2;

		if(eq(e, lista->a[meio])) return meio;
		if(lt(e, lista->a[meio])) fim = meio - 1;
		if(gt(e, lista->a[meio])) ini = meio + 1;
	}
		
	return -1;
}

Boolean insere_lista_sequencial(ListaSequencial * lista, Elemento * e){

	int i;

	if(lista->livre < lista->capacidade) {

		for(i = lista->livre; i > 0 && gt(lista->a[i - 1], e); i--){
			lista->a[i] = lista->a[i - 1];
		}

		lista->a[i] = e;
		lista->livre++;

		return TRUE;
	}

	return FALSE;
}

