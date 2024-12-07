#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef char * Elemento;
typedef int Boolean;

typedef struct _no_arvore_ {

	Elemento valor;
	int h;

	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;

} No;

typedef struct {

	No * raiz;

} Arvore_AVL;

Arvore_AVL * cria_arvore();
void imprime(Arvore_AVL * arvore);

No * busca_AVL(Arvore_AVL * arvore, Elemento e);
Boolean insere_AVL(Arvore_AVL * arvore, Elemento e);
Boolean remove_AVL(Arvore_AVL * arvore, Elemento e);

////////////////////////////////////////////////////////////////////////////////

// funções auxiliares para exibição da árvore, fora
// do conjunto de operações elementares da estrutura.

void display(Arvore_AVL * arvore);
void debug_on();
void debug_off();

