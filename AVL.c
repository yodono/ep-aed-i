#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "AVL.h"

Arvore_AVL * cria_arvore(){

	Arvore_AVL * arvore = (Arvore_AVL *) malloc (sizeof(Arvore_AVL));
	arvore->raiz = NULL;	
	return arvore;
}

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

Boolean insere_AVL_rec(Arvore_AVL * arvore, NoArvore * raiz, NoArvore * pai, NoArvore ** novo){

	Boolean r;
	NoArvore * rot;

	if(neq((*novo)->elemento, raiz->elemento)){
		if(lt((*novo)->elemento, raiz->elemento)){
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
				raiz->esq = *novo;
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
				raiz->dir = *novo;
				if(!raiz->esq) raiz->h = 1;
			}
		}
	
		return TRUE;
	}

  (*novo)->elemento = raiz->elemento;
	return FALSE;
}

Boolean insere_AVL(Arvore_AVL * arvore, Elemento ** e){

	NoArvore * novo = (NoArvore *) malloc(sizeof(NoArvore));
	
	novo->elemento = *e;
	novo->esq = novo->dir = NULL;
	novo->h = 0;

	if(arvore->raiz) {
    Boolean r = insere_AVL_rec(arvore, arvore->raiz, NULL, &novo);

    *e = novo->elemento;

    return r;
  } 
		
	arvore->raiz = novo;
	return TRUE;
}

