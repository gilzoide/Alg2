#include "AVL.h"
#include <stdlib.h>


void AVLCria (AVL *A) {
	A->raiz = NULL;
}


void RotacaoDD (No **p) {
	No *pai = *p;
	No *filho = pai->dir;
	
	pai->dir = filho->esq;	// colisao
	filho->esq = pai;
	pai->fb = filho->fb = 0;
	*p = filho;
}


void RotacaoEE (No **p) {
	No *pai = *p;
	No *filho = pai->esq;
	
	pai->esq = filho->dir;	// colisao
	filho->dir = pai;
	pai->fb = filho->fb = 0;
	*p = filho;
}


void RotacaoED (No **p) {
	No *pai = *p;
	No *filho = pai->esq;
	No *neto = filho->dir;
	
	pai->esq = neto->dir;	// colisao
	filho->dir = neto->esq;
	neto->dir = pai;
	
	switch (neto->fb) {
		case 1:
			pai->fb = 0;
			filho->fb = -1;
			break;
		case 0:
			pai->fb = 0;
			filho->fb = 0;
			break;
		case -1:
			pai->fb = 1;
			filho->fb = 0;
			break;
	}
	
	neto->fb = 0;
	*p = neto;
}


void RotacaoDE (No **p) {
	No *pai = *p;
	No *filho = pai->dir;
	No *neto = filho->esq;
	
	pai->dir = neto->esq;	// colisao
	filho->esq = neto->dir;
	neto->dir = pai;
	
	switch (neto->fb) {
		case -1:
			pai->fb = 1;
			filho->fb = 0;
			break;
		case 0:
			pai->fb = 0;
			filho->fb = 0;
			break;
		case 1:
			pai->fb = 0;
			filho->fb = -1;
			break;
	}
	
	neto->fb = 0;
	*p = neto;
}


int aux_insere (No **p, int *x, int *cresceu) {
	// lugar certo pra por o novo No
	if (*p == NULL) {
		*p = (No*) malloc (sizeof (No));
		(*p)->info = *x;
		(*p)->fb = 0;
		(*p)->esq = (*p)->dir = NULL;
		*cresceu = 1;
		return 1;
	}
	// x == info
	else if ((*p)->info == *x)
		return 0;
	// x < info
	else if (*x < (*p)->info) {
		if (aux_insere (&(*p)->esq, x, cresceu)) {
			if (*cresceu) {
				switch ((*p)->fb) {
					case -1:	// ia desbalancear, arruma
						((*p)->esq->fb == -1) ? RotacaoEE (p) : RotacaoED (p);
						*cresceu = 0;
						break;
					case 0:
						(*p)->fb = -1;
						*cresceu = 1;
						break;
					case 1:
						(*p)->fb = 0;
						*cresceu = 0;
						break;
				}
			}
			return 1;
		}
		else
			return 0;
	}
	else {	// x > info
		if (aux_insere (&(*p)->dir, x, cresceu)) {
			if (*cresceu) {
				switch ((*p)->fb) {
					case -1:
						(*p)->fb = 0;
						*cresceu = 0;
						break;
					case 0:
						(*p)->fb = -1;
						*cresceu = 1;
						break;
					case 1:		// ia desbalancear, arruma
						((*p)->dir->fb == 1) ? RotacaoDD (p) : RotacaoDE (p);
						*cresceu = 0;
						break;
				}
			}
			return 1;
		}
		else
			return 0;
	}	
}


int AVLInsere (AVL *A, int *x) {
	int cresceu;
	return aux_insere (&A->raiz, x, &cresceu);
}
