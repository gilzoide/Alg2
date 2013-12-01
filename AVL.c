/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  AVL.c
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "AVL.h"
#include <stdlib.h>



void AVL_create (AVL *A) {
	A->root = NULL;
}


void AVL_right_right_rotation (node **p) {
	node *parent = *p;
	node *child = parent->right;
	
	parent->right = child->left;	// colisao
	child->left = parent;
	parent->balance_factor = child->balance_factor = 0;
	*p = child;
}


void AVL_left_left_rotation (node **p) {
	node *parent = *p;
	node *child = parent->left;
	
	parent->left = child->right;	// colisao
	child->right = parent;
	parent->balance_factor = child->balance_factor = 0;
	*p = child;
}


void AVL_left_right_rotation (node **p) {
	node *parent = *p;
	node *child = parent->left;
	node *grandchild = child->right;
	
	parent->left = grandchild->right;	// colisao
	child->right = grandchild->left;
	grandchild->right = parent;
	
	switch (grandchild->balance_factor) {
		case 1:
			parent->balance_factor = 0;
			child->balance_factor = -1;
			break;
		case 0:
			parent->balance_factor = 0;
			child->balance_factor = 0;
			break;
		case -1:
			parent->balance_factor = 1;
			child->balance_factor = 0;
			break;
	}
	
	grandchild->balance_factor = 0;
	*p = grandchild;
}


void AVL_right_left_rotation (node **p) {
	node *parent = *p;
	node *child = parent->right;
	node *grandchild = child->left;
	
	parent->right = grandchild->left;	// colisao
	child->left = grandchild->right;
	grandchild->right = parent;
	
	switch (grandchild->balance_factor) {
		case -1:
			parent->balance_factor = 1;
			child->balance_factor = 0;
			break;
		case 0:
			parent->balance_factor = 0;
			child->balance_factor = 0;
			break;
		case 1:
			parent->balance_factor = 0;
			child->balance_factor = -1;
			break;
	}
	
	grandchild->balance_factor = 0;
	*p = grandchild;
}


int AVL_aux_insert (node **p, void* x, int *grew, int (*compare)(void*, void*)) {
	// lugar certo pra por o novo No
	if (*p == NULL) {
		*p = (node*) malloc (sizeof (node));
		(*p)->info = x;
		(*p)->balance_factor = 0;
		(*p)->left = (*p)->right = NULL;
		*grew = 1;
		return 1;
	}
	// x == info
	else if ((*compare)((*p)->info, x) == 0)
		return 0;
	// x < info
	else if ((*compare)((*p)->info, x) < 0) {
		if (AVL_aux_insert (&(*p)->left, x, grew, compare)) {
			if (*grew) {
				switch ((*p)->balance_factor) {
					case -1:	// ia desbalancear, arruma
						((*p)->left->balance_factor == -1) ? AVL_left_left_rotation (p) : AVL_left_right_rotation (p);
						*grew = 0;
						break;
					case 0:
						(*p)->balance_factor = -1;
						*grew = 1;
						break;
					case 1:
						(*p)->balance_factor = 0;
						*grew = 0;
						break;
				}
			}
			return 1;
		}
		else
			return 0;
	}
	else {	// x > info
		if (AVL_aux_insert (&(*p)->right, x, grew, compare)) {
			if (*grew) {
				switch ((*p)->balance_factor) {
					case -1:
						(*p)->balance_factor = 0;
						*grew = 0;
						break;
					case 0:
						(*p)->balance_factor = -1;
						*grew = 1;
						break;
					case 1:		// ia desbalancear, arruma
						((*p)->right->balance_factor == 1) ? AVL_right_right_rotation (p) : AVL_right_left_rotation (p);
						*grew = 0;
						break;
				}
			}
			return 1;
		}
		else
			return 0;
	}	
}


int AVL_insert (AVL *A, void* x) {
	int cresceu;
	return AVL_aux_insert (&A->root, x, &cresceu, A->compare);
}
