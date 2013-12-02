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



void AVL_create (AVL *A, int (*compare)(void*, void*)) {
    
	A->root = NULL;
    A->compare = compare;
    
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
    
	// lugar correto da insersao encontrado
	if (*p == NULL) {
        
        // aloca memoria
		*p = (node*) malloc (sizeof (node));
        if (p == NULL) return 0;
        
        // insere na arvore
		(*p)->info = x;
		(*p)->balance_factor = 0;
		(*p)->left = (*p)->right = NULL;
        
        // indica que a subarvore cresceu
		*grew = 1;
        
		return 1;
	}
	// x == info // erro na insercao
	else if ((*compare)(x, (*p)->info) == 0)
		return 0;
	// x < info
	else if ((*compare)(x, (*p)->info) < 0) {
        // tenta inserir na subarvore esquerda
		if (AVL_aux_insert (&(*p)->left, x, grew, compare)) {
            
            // se a subarvore cresceu
			if (*grew) {
				switch ((*p)->balance_factor) {
					// haveria desbalanceamento
                    case -1:
						((*p)->left->balance_factor == -1) ? AVL_left_left_rotation (p) : AVL_left_right_rotation (p);
						*grew = 0;
						break;
                    // estava perfeitamente balanceada
					case 0:
						(*p)->balance_factor = -1;
						*grew = 1;
						break;
                    // estava "pesada" na direita
					case 1:
						(*p)->balance_factor = 0;
						*grew = 0;
						break;
				}
			}
			return 1;
		}
        // se ocorreu erro na insercao
		else
			return 0;
	}
	else {	// x > info
		// tenta inserir na subarvore direita
        if (AVL_aux_insert (&(*p)->right, x, grew, compare)) {
			// se a subarvore cresceu
            if (*grew) {
				switch ((*p)->balance_factor) {
					// estava "pesada" na esquerda
                    case -1:
						(*p)->balance_factor = 0;
						*grew = 0;
						break;
					// estava perfeitamente balanceada
                    case 0:
						(*p)->balance_factor = -1;
						*grew = 1;
						break;
					// haveria desbalanceamento
                    case 1:
						((*p)->right->balance_factor == 1) ? AVL_right_right_rotation (p) : AVL_right_left_rotation (p);
						*grew = 0;
						break;
				}
			}
			return 1;
		}
        // se ocorreu erro na insersao
		else
			return 0;
	}
    
}


int AVL_insert (AVL *A, void* x) {
    
	int grew;
	return AVL_aux_insert (&A->root, x, &grew, A->compare);
    
}

node* AVL_delete_aux (node* root, void* x, int* decreased, int (*compare)(void*, void*)) {
    
    // parte 1: deletar o nó da arvore
    
    if (root == NULL)
        return root;
    
    // busca na subarvore da esquerda
    if ((*compare)(x, root->info) < 0)
        root->left = AVL_delete_aux(root->left, x, decreased, compare);
    
    // busca na subarvore da direita
    else if((*compare)(x, root->info) > 0)
        root->right = AVL_delete_aux(root->right, x, decreased, compare);
    
    // o valor foi encontrado
    else { // root == x
        // no com 1 ou nenhum filho
        if( (root->left == NULL) || (root->right == NULL) ) {
            node *temp = root->left ? root->left : root->right;
            
            // no sem filhos
            if(temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // no com um filho
                *root = *temp;
            
            free(temp);
        }
        
        // no com os dois filhos
        else {
            
            // encontra o menor no da arvore direita
            node* temp = AVL_min_value_node(root->right);
            
            // copia o valor deste no
            root->info = temp->info;
            
            // apaga o no onde estava o mesmo
            root->right = AVL_delete_aux(root->right, temp->info, decreased, compare);
        }
    }
    
    // se a arvore so tinha este no, fim
    if (root == NULL)
        return root;
    
    return root;
    
}

node* AVL_delete(AVL* A, void* x) {
    
    int decreased;
    node* deleted = AVL_delete_aux(A->root, x, &decreased, A->compare);
    return deleted;
    
}









