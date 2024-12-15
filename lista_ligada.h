#include "utils.h"

typedef struct _no_ {

	Elemento * elemento;
	struct _no_ * proximo;

} NoLista;

typedef struct {
	
	NoLista * primeiro;
  int tamanho;

} ListaLigada;

ListaLigada * cria_lista_ligada();
void destroi_lista_ligada(ListaLigada * lista);
int tamanho_lista_ligada(ListaLigada * lista);
NoLista * busca_lista_ligada(ListaLigada * lista, Elemento * e);
Boolean insere_sem_repeticao_lista_ligada(ListaLigada * lista, Elemento * e);
Boolean insere_lista_ligada(ListaLigada * lista, Elemento * e, Boolean semRepeticao);

