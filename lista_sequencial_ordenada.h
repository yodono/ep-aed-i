#include "types.h"
#include "comparador.h"

typedef struct {

	Elemento ** a;
	int livre;
	int capacidade;

} ListaSequencial;

ListaSequencial * cria_lista_sequencial(int n);
void destroi_lista_sequencial(ListaSequencial * lista);
int tamanho_lista_sequencial(ListaSequencial * lista);
int busca_lista_sequencial(ListaSequencial * lista, Elemento * e);
Boolean insere_lista_sequencial(ListaSequencial * lista, Elemento * e);

