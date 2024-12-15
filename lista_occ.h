#ifndef LISTA_OCC_H
#define LISTA_OCC_H

#include "types.h"
#include "comparador.h"

// lista sem elementos repetidos
ListaOcc * cria_lista_occ();
void imprime_occ(ListaOcc * lista, char ** lista_linhas);
Boolean insere_occ(ListaOcc * lista, int l);

#endif // LISTA_OCC_H

