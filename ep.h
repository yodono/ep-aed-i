typedef struct {

  char * valor;
  int quantidade;
  int * ocorrencias;

} Indice

typedef char * Elemento;
typedef int Boolean;
Boolean eq(Elemento a, Elemento b);
Boolean lt(Elemento a, Elemento b);
Boolean gt(Elemento a, Elemento b);
