#ifndef LISTA_OCC_H
#define LISTA_OCC_H

#include "utils.h"

ListaOcc * cria_lista_occ();
void imprime_occ(ListaOcc * lista);
Boolean insere_occ(ListaOcc * lista, int l, Boolean semRepeticao);
Boolean insere_occ_sem_repeticao(ListaOcc * lista, int l);

#endif // LISTA_OCC_H

