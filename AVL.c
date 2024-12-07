#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "AVL.h"
#include "comparador.h"

///////////////////////////////////////////////////////////////////////////////////////////
// Funções auxiliares. Não fazem parte do conjunto de operações elementares da estrutura //
///////////////////////////////////////////////////////////////////////////////////////////

Boolean __debug__ = FALSE;
void debug_on() { __debug__ = TRUE; }
void debug_off() { __debug__ = FALSE; }

#define ROWS 20
#define COLS 80

int balanco(No * no);

int display_rec(char ** buffer, No * no, int level, double h_position){

	char * ptr;
	int i, col, a, b;
	double offset;

	if(no){
		col = (int)(h_position * COLS);
		offset = 1.0 / pow(2, level + 2);

		ptr = buffer[1 + level * 3] + col;
		sprintf(ptr, "%03d (%d)", no->valor, balanco(no));
		*(ptr + strlen(ptr)) = ' ';

		if(no->esq || no->dir) *(buffer[2 + level * 3] + col + 1) = '|';

		if(no->esq){
		
			i = (int)((h_position - offset) * COLS);
			*(buffer[3 + level * 3] + 1 + i) = '|';
			i++;
			for(; i <= col; i++) *(buffer[3 + level * 3] + 1 + i) = '-';
		}
		
		if(no->dir){

			for(i = col; i < (int)((h_position + offset) * COLS); i++) *(buffer[3 + level * 3] + 1 + i) = '-';
			*(buffer[3 + level * 3] + 1 + i) = '|';
		}

		a = display_rec(buffer, no->esq, level + 1, h_position - offset);
		b = display_rec(buffer, no->dir, level + 1, h_position + offset);

		if(a > b) return a;
		return b;
	}

	return level;
}

void display_no(No * no){

	int i, j, r;

	char ** buffer = (char **) malloc(ROWS * sizeof(char *));

	for(i = 0; i < ROWS; i++) {

		buffer[i] = (char *) malloc((COLS + 1) * sizeof(char));

		for(j = 0; j < COLS; j++) buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}

	r = display_rec(buffer, no, 0, 0.5);

	if(__debug__) getchar();

	for(i = 0; i < 3 * r; i++) printf("%s\n", buffer[i]);
	printf("-----------------------------------------------------------------------------------------------\n");
}

void display(Arvore_AVL * arvore){

	display_no(arvore->raiz);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementações comuns tanto para a árvore binária de "propósito geral", quanto para a árvore binária de busca //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arvore_AVL * cria_arvore(){

	Arvore_AVL * arvore = (Arvore_AVL *) malloc (sizeof(Arvore_AVL));
	arvore->raiz = NULL;	
	return arvore;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprime_rec(No * no){

	// percurso in-ordem para a impressão dos elementos

	if(no){
		imprime_rec(no->esq);
		printf(" %d", no->valor);
		imprime_rec(no->dir);
	}
}

void imprime(Arvore_AVL * arvore){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}

///////////////////////////////////////////////////////////////
// Implementações específicas para a árvore binária de busca //
///////////////////////////////////////////////////////////////

No * busca_AVL_rec(No * no, Elemento e){

	if(no){

		if(__debug__) display_no(no);

		if(no->valor == e) return no;
		if(e < no->valor) return busca_AVL_rec(no->esq, e);
		return busca_AVL_rec(no->dir, e);
	}

	return NULL;
}

No * busca_AVL(Arvore_AVL * arvore, Elemento e){
	
	return busca_AVL_rec(arvore->raiz, e);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int max(int a, int b){

	return a > b ? a : b;
}

int balanco(No * no){

	if(no->esq && no->dir) return (no->dir->h) - (no->esq->h);
	if(no->esq) return -1 * (no->esq->h + 1);
	if(no->dir) return no->dir->h + 1;
	return 0;
}

void atualiza_altura(No * no){

	// assuminos que todos os nós na (sub)arvore definida por 'no' já estão com suas alturas atualizadas.

	if(no->esq && no->dir) no->h = max(no->esq->h, no->dir->h) + 1;
	else if(no->dir) no->h = no->dir->h + 1;
	else if(no->esq) no->h = no->esq->h + 1;
	else no->h = 0;
}

No * rotacaoL(No * p){

	No * v;
	No * u = p->esq;
		
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

No * rotacaoR(No * p){

	No * v;
	No * u = p->dir;
		
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

Boolean insere_AVL_rec(Arvore_AVL * arvore, No * raiz, No * pai, No * novo){

	Boolean r;
	No * rot;

	if(novo->valor != raiz->valor){

		if(novo->valor < raiz->valor){

			if(raiz->esq){

				r = insere_AVL_rec(arvore, raiz->esq, raiz, novo);
				atualiza_altura(raiz);
			
				if(abs(balanco(raiz)) >= 2) {

					printf("No %d desbalanceado! h = %d, bal = %d\n", raiz->valor, raiz->h, balanco(raiz));
					
					display(arvore);
					getchar();	

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

					printf("No %d desbalanceado! h = %d, bal = %d\n", raiz->valor, raiz->h, balanco(raiz));
					
					display(arvore);
					getchar();	

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

	return FALSE;
}

Boolean insere_AVL(Arvore_AVL * arvore, Elemento e){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->valor = e;
	novo->esq = novo->dir = NULL;
	novo->h = 0;

	if(arvore->raiz) return insere_AVL_rec(arvore, arvore->raiz, NULL, novo);
		
	arvore->raiz = novo;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

No * encontra_menor(No * raiz){

	if(raiz->esq) return encontra_menor(raiz->esq);
	
	return raiz;
}

No * encontra_maior(No * raiz){

	if(raiz->dir) return encontra_maior(raiz->dir);
	
	return raiz;
}

/*
No * encontra_pai_ord(No * raiz, No * no){

	if(raiz){

		if(raiz->esq == no) return raiz;
		if(raiz->dir == no) return raiz;
		if(no->valor < raiz->valor) return encontra_pai_ord(raiz->esq, no);
		if(no->valor > raiz->valor) return encontra_pai_ord(raiz->dir, no);
	}
		
	return NULL;
}
*/

Boolean remove_AVL_rec(Arvore_AVL * arvore, No * raiz, No * pai, Elemento e){

	No * a_remover;
	No * rot;
	Boolean retorno;

	if(raiz) {

		if(raiz->valor == e){

			if(raiz->dir){

				a_remover = encontra_menor(raiz->dir);
				raiz->valor = a_remover->valor;
				retorno = remove_AVL_rec(arvore, raiz->dir, raiz, a_remover->valor);

				// atualizar altura da raiz
				atualiza_altura(raiz);

				if(abs(balanco(raiz)) >= 2){

					printf("No %d desbalanceado! h = %d, bal = %d\n", raiz->valor, raiz->h, balanco(raiz));
					
					display(arvore);
					getchar();	

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
				raiz->valor = a_remover->valor;
				retorno = remove_AVL_rec(arvore, raiz->esq, raiz, a_remover->valor);

				// atualizar altura da raiz
				atualiza_altura(raiz);

				if(abs(balanco(raiz)) >= 2){

					printf("No %d desbalanceado! h = %d, bal = %d\n", raiz->valor, raiz->h, balanco(raiz));
					
					display(arvore);
					getchar();	

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
		else if(e < raiz->valor){

			retorno = remove_AVL_rec(arvore, raiz->esq, raiz, e);
			atualiza_altura(raiz);

			if(abs(balanco(raiz)) >= 2){

				printf("No %d desbalanceado! h = %d, bal = %d\n", raiz->valor, raiz->h, balanco(raiz));
				
				display(arvore);
				getchar();	

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

				printf("No %d desbalanceado! h = %d, bal = %d\n", raiz->valor, raiz->h, balanco(raiz));
				
				display(arvore);
				getchar();	

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

Boolean remove_AVL(Arvore_AVL * arvore, Elemento e){

	return remove_AVL_rec(arvore, arvore->raiz, NULL, e);
}
