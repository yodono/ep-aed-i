#include "utils.h"

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef struct _no_arvore_ {

	Elemento * elemento;
	int h;

	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;

} NoArvore;

typedef struct {

	NoArvore * raiz;

} Arvore_AVL;

Arvore_AVL * cria_arvore();
void imprime_AVL(Arvore_AVL * arvore);

NoArvore * busca_AVL(Arvore_AVL * arvore, Elemento * e);
Boolean insere_AVL(Arvore_AVL * arvore, Elemento * e);
Boolean remove_AVL(Arvore_AVL * arvore, Elemento * e);

