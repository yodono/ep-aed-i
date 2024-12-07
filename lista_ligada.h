#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef char * Elemento;

typedef struct _no_ {

	Elemento valor;
	struct _no_ * proximo;

} No;

typedef struct {
	
	No * primeiro;
  int tamanho;

} ListaLigada;

ListaLigada * cria_lista();
void destroi_lista(ListaLigada * lista);
int tamanho(ListaLigada * lista);
void imprime(ListaLigada * lista);
int busca(ListaLigada * lista, Elemento e);
Boolean insere_distinto(ListaLigada * lista, Elemento e);
Boolean remove_elemento(ListaLigada * lista, Elemento e);
