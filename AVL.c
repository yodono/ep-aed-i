#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "AVL.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Funções auxiliares. Não fazem parte do conjunto de operações elementares da estrutura //
///////////////////////////////////////////////////////////////////////////////////////////

int balanco(NoArvore * no);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementações comuns tanto para a árvore binária de "propósito geral", quanto para a árvore binária de busca //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arvore_AVL * cria_arvore(){

	Arvore_AVL * arvore = (Arvore_AVL *) malloc (sizeof(Arvore_AVL));
	arvore->raiz = NULL;	
	return arvore;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprime_rec(NoArvore * no){

	// percurso in-ordem para a impressão dos elementos

	if(no && no->elemento && no->elemento->valor){
		imprime_rec(no->esq);
		printf(" %s", no->elemento->valor);
		imprime_rec(no->dir);
	}
}

void imprime_AVL(Arvore_AVL * arvore){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}

///////////////////////////////////////////////////////////////
// Implementações específicas para a árvore binária de busca //
///////////////////////////////////////////////////////////////

NoArvore * busca_AVL_rec(NoArvore * no, Elemento * e){

	if(no){
		if(eq(no->elemento, e)) return no;
		if(lt(e, no->elemento)) return busca_AVL_rec(no->esq, e);
		return busca_AVL_rec(no->dir, e);
	}

	return NULL;
}

NoArvore * busca_AVL(Arvore_AVL * arvore, Elemento * e){
	
	return busca_AVL_rec(arvore->raiz, e);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int max(int a, int b){

	return a > b ? a : b;
}

int balanco(NoArvore * no){

	if(no->esq && no->dir) return (no->dir->h) - (no->esq->h);
	if(no->esq) return -1 * (no->esq->h + 1);
	if(no->dir) return no->dir->h + 1;
	return 0;
}

void atualiza_altura(NoArvore * no){

	// assuminos que todos os nós na (sub)arvore definida por 'no' já estão com suas alturas atualizadas.

	if(no->esq && no->dir) no->h = max(no->esq->h, no->dir->h) + 1;
	else if(no->dir) no->h = no->dir->h + 1;
	else if(no->esq) no->h = no->esq->h + 1;
	else no->h = 0;
}

NoArvore * rotacaoL(NoArvore * p){

	NoArvore * v;
	NoArvore * u = p->esq;
		
	if(balanco(u) == -1) { // rotação LL

		p->esq = u->dir;
		u->dir = p;
		p->h -= 2;
		return u;
	}
	else if(balanco(u) == 1) { // rotação LR
	
		v = u->dir;

		u->dir = v->esq;
		v->esq = u;
		p->esq = v->dir;
		v->dir = p;

		p->h -= 2;
		u->h -= 1;
		v->h += 1;

		return v;
	}

	return NULL;
}

NoArvore * rotacaoR(NoArvore * p){

	NoArvore * v;
	NoArvore * u = p->dir;
		
	if(balanco(u) == 1) { // rotação RR

		p->dir = u->esq;
		u->esq = p;
		p->h -= 2;
		return u;
	}
	else if(balanco(u) == -1) { // rotação RL
	
		v = u->esq;

		u->esq = v->dir;
		v->dir = u;
		p->dir = v->esq;
		v->esq = p;

		p->h -= 2;
		u->h -= 1;
		v->h += 1;

		return v;
	}

	return NULL;
}

Boolean insere_AVL_rec(Arvore_AVL * arvore, NoArvore * raiz, NoArvore * pai, NoArvore * novo){

	Boolean r;
	NoArvore * rot;

	if(neq(novo->elemento, raiz->elemento)){
		if(lt(novo->elemento, raiz->elemento)){
			if(raiz->esq){

				r = insere_AVL_rec(arvore, raiz->esq, raiz, novo);
				atualiza_altura(raiz);
			
				if(abs(balanco(raiz)) >= 2) {
					rot = rotacaoL(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}
	
				return r;
			}
			else {
				raiz->esq = novo;
				if(!raiz->dir) raiz->h = 1;
			}
		}
		else{
			if(raiz->dir){
		
				r = insere_AVL_rec(arvore, raiz->dir, raiz, novo);
				atualiza_altura(raiz);
			
				if(abs(balanco(raiz)) >= 2){
					rot = rotacaoR(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}

				return r; 
			}
			else {
				raiz->dir = novo;
				if(!raiz->esq) raiz->h = 1;
			}
		}
	
		return TRUE;
	}

  free(novo->elemento);
  novo->elemento = raiz->elemento;
	return FALSE;
}

Boolean insere_AVL(Arvore_AVL * arvore, Elemento * e){

	NoArvore * novo = (NoArvore *) malloc(sizeof(NoArvore));
	
	novo->elemento = e;
	novo->esq = novo->dir = NULL;
	novo->h = 0;

	if(arvore->raiz) return insere_AVL_rec(arvore, arvore->raiz, NULL, novo);
		
	arvore->raiz = novo;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NoArvore * encontra_menor(NoArvore * raiz){

	if(raiz->esq) return encontra_menor(raiz->esq);
	
	return raiz;
}

NoArvore * encontra_maior(NoArvore * raiz){

	if(raiz->dir) return encontra_maior(raiz->dir);
	
	return raiz;
}

/*
NoArvore * encontra_pai_ord(NoArvore * raiz, NoArvore * no){

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;
		if(no->valor < raiz->valor) return encontra_pai_ord(raiz->esq, no);
		if(no->valor > raiz->valor) return encontra_pai_ord(raiz->dir, no);
	}
		
	return NULL;
}
*/

Boolean remove_AVL_rec(Arvore_AVL * arvore, NoArvore * raiz, NoArvore * pai, Elemento * e){

	NoArvore * a_remover;
	NoArvore * rot;
	Boolean retorno;

	if(raiz) {

		if(eq(raiz->elemento, e)){

			if(raiz->dir){

				a_remover = encontra_menor(raiz->dir);
				raiz->elemento = a_remover->elemento;
				retorno = remove_AVL_rec(arvore, raiz->dir, raiz, a_remover->elemento);

				// atualizar altura da raiz
				atualiza_altura(raiz);

				if(abs(balanco(raiz)) >= 2){
					rot = rotacaoL(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}

				return retorno;
			}
			else if(raiz->esq){

				a_remover = encontra_maior(raiz->esq);
				raiz->elemento = a_remover->elemento;
				retorno = remove_AVL_rec(arvore, raiz->esq, raiz, a_remover->elemento);

				// atualizar altura da raiz
				atualiza_altura(raiz);

				if(abs(balanco(raiz)) >= 2){
					rot = rotacaoR(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}
			
				return retorno;
			}
			else{
				if(pai){
					if(pai->esq == raiz) pai->esq = NULL;
					if(pai->dir == raiz) pai->dir = NULL;
					atualiza_altura(pai);
				}
				else{
					arvore->raiz = NULL;
				}

				free(raiz);
				return TRUE;
			}
		}
		else if(lt(e, raiz->elemento)){

			retorno = remove_AVL_rec(arvore, raiz->esq, raiz, e);
			atualiza_altura(raiz);

			if(abs(balanco(raiz)) >= 2){
				rot = rotacaoR(raiz);

				if(pai){
					if(pai->esq == raiz) pai->esq = rot;
					if(pai->dir == raiz) pai->dir = rot;
				}
				else arvore->raiz = rot;
			}

			return retorno;
		}
		else {
			retorno = remove_AVL_rec(arvore, raiz->dir, raiz, e);
			atualiza_altura(raiz);

			if(abs(balanco(raiz)) >= 2){
				rot = rotacaoL(raiz);

				if(pai){
					if(pai->esq == raiz) pai->esq = rot;
					if(pai->dir == raiz) pai->dir = rot;
				}
				else arvore->raiz = rot;
			}

			return retorno;
		}
	}

	return FALSE;
}

Boolean remove_AVL(Arvore_AVL * arvore, Elemento * e){

	return remove_AVL_rec(arvore, arvore->raiz, NULL, e);
}
