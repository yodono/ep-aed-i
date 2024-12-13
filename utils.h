#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1

typedef struct no_occ {
    int valor; 
    struct no_occ * proximo;
} No_occ;

typedef struct {
    No_occ * primeiro;
    int tamanho;
} ListaOcc;

typedef struct {

  char * valor;
  int quantidade;
  ListaOcc * ocorrencias;

} Elemento;

typedef int Boolean;

Boolean eq(Elemento * a, Elemento * b);
Boolean eq_char(char * a, char * b);
Boolean neq(Elemento * a, Elemento * b);
Boolean lt(Elemento * a, Elemento * b);
Boolean gt(Elemento * a, Elemento * b);
Boolean nornull(Elemento * a, Elemento * b);
Boolean is_null(Elemento * e);

void strlwr(char * s);

#endif

