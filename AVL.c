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
#include <stdio.h>
#include <string.h>



void AVL_create (AVL *A, int (*compare)(void*, void*)) {
    
	A->root = NULL;
    A->compare = compare;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

// A utility function to get height of the tree
int AVL_height(node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

// A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b)? a : b;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */
node* AVL_new_node(void* info) {
    
    node* new_node = (node*) malloc(sizeof(node));
    new_node->info   = info;
    new_node->left   = NULL;
    new_node->right  = NULL;
    new_node->height = 1;  // new node is initially added at leaf
    return(new_node);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
node* right_rotate(node *y) {
    
    node *x = y->left;
    node *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(AVL_height(y->left), AVL_height(y->right))+1;
    x->height = max(AVL_height(x->left), AVL_height(x->right))+1;
    
    // Return new root
    return x;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
node* left_rotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    //  Update heights
    x->height = max(AVL_height(x->left), AVL_height(x->right))+1;
    y->height = max(AVL_height(y->left), AVL_height(y->right))+1;
    
    // Return new root
    return y;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

// Get Balance factor of node N
int AVL_balance(node *N) {
    if (N == NULL)
        return 0;
    return AVL_height(N->left) - AVL_height(N->right);
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

node* AVL_insert_aux(node* root, void* info, int (*compare)(void*, void*)) {
    /* 1.  Perform the normal BST insertion */
    if (root == NULL)
        return(AVL_new_node(info));
    
    if ((*compare)(info, root->info) < 0)
        root->left  = AVL_insert_aux(root->left, info, compare);
    else
        root->right = AVL_insert_aux(root->right, info, compare);
    
    /* 2. Update height of this ancestor node */
    root->height = max(AVL_height(root->left), AVL_height(root->right)) + 1;
    
    /* 3. Get the balance factor of this ancestor node to check whether
     this node became unbalanced */
    int balance = AVL_balance(root);
    
    // If this node becomes unbalanced, then there are 4 cases
    
    // Left Left Case
    if (balance > 1 && (*compare)(info, root->left->info) < 0)
        return right_rotate(root);
    
    // Right Right Case
    if (balance < -1 && (*compare)(info, root->right->info) > 0)
        return left_rotate(root);
    
    // Left Right Case
    if (balance > 1 && (*compare)(info, root->left->info) > 0)
    {
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }
    
    // Right Left Case
    if (balance < -1 && (*compare)(info, root->right->info) < 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    /* return the (unchanged) node pointer */
    return root;
}

void AVL_insert(AVL* A, void* info) {
    
    A->root = AVL_insert_aux(A->root, info, A->compare);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/* Given a non-empty binary search tree, return the node with minimum
 key value found in that tree. Note that the entire tree does not
 need to be searched. */
node * AVL_min_value_node(node* root) {
    
    node* current = root;
    
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

node* AVL_delete_aux(node* root, void* info, void** deleted_element, int (*compare)(void*, void*)) {
    
    // STEP 1: PERFORM STANDARD BST DELETE
    
    if (root == NULL)
        return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ((*compare)(info, root->info) < 0)
        root->left = AVL_delete_aux(root->left, info, deleted_element, compare);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if((*compare)(info, root->info) > 0)
        root->right = AVL_delete_aux(root->right, info, deleted_element, compare);
    
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        
        // salva o elemento
        *deleted_element = root->info;
        
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) ) {
            node *temp = root->left ? root->left : root->right;
            
            // No child case
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            node* temp = AVL_min_value_node(root->right);
            
            // Copy the inorder successor's data to this node
            root->info = temp->info;
            
            // Delete the inorder successor
            root->right = AVL_delete_aux(root->right, temp->info, deleted_element, compare);
        }
    }
    
    // If the tree had only one node then return
    if (root == NULL)
        return root;
    
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(AVL_height(root->left), AVL_height(root->right)) + 1;
    
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = AVL_balance(root);
    
    // If this node becomes unbalanced, then there are 4 cases
    
    // Left Left Case
    if (balance > 1 && AVL_balance(root->left) >= 0)
        return right_rotate(root);
    
    // Left Right Case
    if (balance > 1 && AVL_balance(root->left) < 0) {
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && AVL_balance(root->right) <= 0)
        return left_rotate(root);
    
    // Right Left Case
    if (balance < -1 && AVL_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* AVL_delete(AVL* A, void* info) {
    
    void* deleted_element = NULL;
    A->root = AVL_delete_aux(A->root, info, &deleted_element, A->compare);
    return deleted_element;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* AVL_delete_with_another_compare(AVL* A, void* info, int (*compare)(void*, void*)) {
    
    void* deleted_element = NULL;
    A->root = AVL_delete_aux(A->root, info, &deleted_element, compare);
    return deleted_element;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void AVL_pre_order_aux(node *root, void (*print_content)(void*)) {
    
    if(root != NULL) {
        (*print_content)(root->info);
        AVL_pre_order_aux(root->left, print_content);
        AVL_pre_order_aux(root->right, print_content);
    }
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void AVL_pre_order(AVL* A, void (*print_content)(void*)) {
    
    AVL_pre_order_aux(A->root, print_content);
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void AVL_in_order_aux(node *root, void (*print_content)(void*)) {
    
    if(root != NULL) {
        AVL_pre_order_aux(root->left, print_content);
        (*print_content)(root->info);
        AVL_pre_order_aux(root->right, print_content);
    }
}

void AVL_in_order(AVL* A, void (*print_content)(void*)) {
    
    AVL_in_order_aux(A->root, print_content);
}

void* AVL_search_aux(node* root, void* info, int (*compare)(void*, void*)) {
    
    if (root == NULL)
        return NULL;
    
    if ((*compare)(info, root->info) == 0)
        return root;

    else if ((*compare)(info, root->info) < 0)
        root = AVL_search_aux(root->left, info, compare);

    else if((*compare)(info, root->info) > 0)
        root = AVL_search_aux(root->right, info, compare);
    
    return root;
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* AVL_search(AVL* A, void* info) {
    
    node* root = A->root;
    node* result = (node*) AVL_search_aux(root, info, A->compare);
    return (result == NULL) ? NULL : result->info;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* AVL_search_with_another_compare(AVL* A, void* info, int (*compare)(void*, void*)) {
    
    node* root = A->root;
    node* result = (node*) AVL_search_aux(root, info, compare);
    
    return (result == NULL) ? NULL : result->info;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int AVL_count_aux(node* root) {
    
    if (root == NULL)
        return 0;
    else
        return AVL_count_aux(root->left) + AVL_count_aux(root->right) + 1;
    
}

int AVL_count(AVL* A) {
    
    return AVL_count_aux(A->root);
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int AVL_count_with_function_aux(node* root, int (*counter)(void*)) {
    
    if (root == NULL)
        return 0;
    else
        return AVL_count_aux(root->left) + AVL_count_aux(root->right) + (*counter)(root->info);
    
}

int AVL_count_with_function(AVL* A, int (*counter)(void*)) {
    
    return AVL_count_with_function_aux(A->root, counter);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void AVL_destroy_aux(node* root, void (*destroy_elem)(void*)) {
    
    if(root != NULL) {
        AVL_destroy_aux(root->left, destroy_elem);
        AVL_destroy_aux(root->right, destroy_elem);
        
        if (destroy_elem != NULL)
            (*destroy_elem)(root->info);
        
        free(root);
    }
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void AVL_destroy(AVL* A) {
    
    AVL_destroy_aux(A->root, NULL);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void AVL_destroy_with_function(AVL* A, void (*destroy_elem)(void*)) {
    
    AVL_destroy_aux(A->root, destroy_elem);
    
}

