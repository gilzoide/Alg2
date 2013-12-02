/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  main.c
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include "AVL.h"

void print_int(void* x) {
    printf("%d ", *((int*)x));
}

int compare_int(void* a, void* b) {
    return *((int*)a) - *((int*)b);
}

int main(int argc, const char * argv[])
{
    
    AVL integers;
    AVL_create(&integers, &compare_int);
    
    int a = 2, b = 3, c =8, d = 20, e = 7;
    
    
    AVL_insert(&integers, &a);
    AVL_insert(&integers, &b);
    AVL_insert(&integers, &c);
    AVL_insert(&integers, &d);
    
    AVL_in_order(&integers, &print_int);
    
    printf("\n\nApaga o 2");
    AVL_delete(&integers, &a);
    
    printf("\n");
    AVL_in_order(&integers, &print_int);
    
    printf("\n\nTenta apagar o 2 denovo");
    AVL_delete(&integers, &a);
    
    printf("\n");
    AVL_in_order(&integers, &print_int);
    
    printf("\n\nInsere o 7");
    AVL_insert(&integers, &e);
    
    printf("\n");
    AVL_in_order(&integers, &print_int);
    
    printf("\n\nApaga o 8");
    AVL_delete(&integers, &c);
    
    printf("\n");
    AVL_in_order(&integers, &print_int);
    
    return 0;
    
}

