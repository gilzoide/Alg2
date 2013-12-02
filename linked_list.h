/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  linked_list.h
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ALGI_linked_list_h
#define ALGI_linked_list_h

/*!
 *  Registro que define um no da lista encadeada
 */
typedef struct LL_node {
	
    void* info;             /*!< elemento que sera guardado na lista,
                                 void para suportar polimorfismo */
	struct LL_node *next;   /*!< proximo elemento da lista */
    
} LL_node;

/*!
 *  Registro que define a Lista Encadeada
 */
typedef struct {
    
	LL_node *head;                  /*!< cabeca da lista */
    int (*compare)(void*, void*);   /*!< ponteiro para funcao que compara elementos */
    
} linked_list;


// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Cria uma lista encadeada
 
 @param A
 ponteiro para lista que sera criada
 
 @param int(*compare)(void*,void*)
 ponteiro para a funcao de comparacao dos elementos
 
 */
int LL_create(linked_list* L, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Insere um novo elemento na lista
 
 @param A
 ponteiro para a lista
 
 @param x
 ponteiro para o elemento que sera inserido
 
 */
int LL_insert(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Insere, de forma ordenada, um novo elemento na lista
 
 @param A
 ponteiro para a lista
 
 @param x
 ponteiro para o elemento que sera inserido
 
 */
int LL_insert_ordered(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Retira um elemento da lista
 
 @param A
 ponteiro para a lista
 
 @param x
 ponteiro para o elemento que sera retirado
 
 @result
 retorna o elemento retirado ou NULL em caso de erro
 
 */
void* LL_delete(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Destroi a lista encadeada
 
 @param A
 ponteiro para a lista
 
 @param must_free
 flag que indica se a memoria dos elementos da lista deve ser liberada
 
 */

void LL_destroy(linked_list* L, int must_free);

#endif
