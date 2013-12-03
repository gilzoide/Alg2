/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  linked_list.c
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


void LL_create(linked_list* L, int (*compare)(void*, void*)) {
    
    L->head = NULL;
    L->compare = compare;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int LL_insert(linked_list* L, void* info) {
    
    LL_node** p = NULL;
    
    // percorre a lista encadeada
    for (p = &(L->head); *p != NULL; p = &(*p)->next);
    
    // cria o novo no
    *p = (LL_node*) malloc(sizeof(LL_node));
    if (*p == NULL) return 0;
    (*p)->info = info;
    (*p)->next = NULL;
    
    return 1;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

int LL_insert_ordered(linked_list* L, void* info) {
    
    LL_node** p = NULL;
    
    
    // percorre a lista encadeada, buscando o lugar do novo no
    for (p = &(L->head); (*p != NULL) && ((*L->compare)(info, (*p)->info) > 0); p = &(*p)->next);
    
    LL_node* tmp = *p;
    
    // cria o novo no
    *p = (LL_node*) malloc(sizeof(LL_node));
    if (*p == NULL) return 0;
    
    // insere o no na lista
    (*p)->info = info;
    (*p)->next = tmp;
    
    return 1;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* LL_delete(linked_list* L, void* info) {
    
    LL_node** p = NULL;
    
    // percorre a lista encadeada, buscando o no
    for (p = &(L->head); (*p != NULL) && ((*L->compare)(info, (*p)->info) != 0); p = &(*p)->next);
    
    // verifica se foi encontrado
    if (*p != NULL) {
        
        // salva a informacao para o retorno
        void* deleted_info = (*p)->info;
        
        // apaga o no
        LL_node* tmp = *p;
        *p = (*p)->next;
        free(tmp);
        
        return deleted_info;
    }
    
    else
        return NULL;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void LL_destroy(linked_list* L, int must_free) {
    
    LL_node* p = L->head;
    
    // percorre a lista
    while (p != NULL) {
        
        LL_node* tmp = p;
        p = p->next;
        
        // liberando os nos (e, caso necessario, seus elementos)
        if (must_free) free(tmp->info);
        free(tmp);
        
    }
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void LL_print(linked_list* L, void (*print)(void*)) {
    
    LL_node* p = NULL;
    
    // percorre a lista encadeada e imprime os elementos
    for (p = L->head; p != NULL; p = p->next)
        (*print)(p->info);
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* LL_search(linked_list* A, void* info) {
    
    return NULL;
    
}

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

void* LL_search_with_another_compare(linked_list* A, void* info, int (*compare)(void*, void*)) {
    
    return NULL;
    
}






