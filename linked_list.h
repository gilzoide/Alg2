/*! @file linked_list.h __TAD Lista Encadeada__
 */
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
 * Cria uma lista encadeada
 *
 * @param L
 * ponteiro para lista que sera criada
 *
 * @param compare
 * ponteiro para a funcao de comparacao dos elementos
 */
void LL_create(linked_list* L, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Insere um novo elemento na lista
 *
 * @param L
 * ponteiro para a lista
 *
 * @param info
 * ponteiro para o elemento que sera inserido
 */
int LL_insert(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Insere, de forma ordenada, um novo elemento na lista
 *
 * @param L
 * ponteiro para a lista
 *
 * @param info
 * ponteiro para o elemento que sera inserido
 */
int LL_insert_ordered(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Retira um elemento da lista
 *
 * @param L
 * ponteiro para a lista
 *
 * @param info
 * ponteiro para o elemento que sera retirado
 *
 * @result
 * retorna o elemento retirado ou NULL em caso de erro
 */
void* LL_delete(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Retira o enésimo elemento da lista
 *
 * @param L
 * ponteiro para a lista
 *
 * @param n
 * posição do elemento
 *
 * @result
 * retorna o elemento retirado ou NULL em caso de erro
 */
void* LL_delete_nth_element(linked_list* L, int n);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Retira um elemento da lista, mas recebe uma funcao de
 * comparacao diferente da padrao, util para buscas
 * diferenciadas
 *
 * @param L
 * ponteiro para a lista
 *
 * @param info
 * ponteiro para o elemento que sera retirado
 *
 * @param compare
 * funcao que substitui o padrão de comparacao
 *
 * @result
 * retorna o elemento retirado, ou NULL em caso de erro
 */
void* LL_delete_with_another_compare(linked_list* L, void* info, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Destroi a lista encadeada
 *
 * @param L
 * ponteiro para a lista
 */

void LL_destroy(linked_list* L);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Destroi a lista encadeada, aplicando uma função, 
 * passada como parâmetro, em cada elemento apagado
 *
 * @param L
 * ponteiro para a lista
 *
 * @param destroy_elem
 * função que será aplicada nos elementos
 */

void LL_destroy_with_function(linked_list* L, void (*destroy_elem)(void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime o conteudo da lista encadeada
 *
 * @param L
 * ponteiro para a lista
 *
 * @param print
 * funcao que imprime elementos na tela
 */
void LL_print(linked_list* L, void (*print)(void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 *
 * Busca elemento na lista
 *
 * @param L
 * ponteiro para a lista
 *
 * @param info
 * elemento que sera buscado
 *
 * @return
 * retorna o elemento encontrado ou NULL em caso de erro
 */
void* LL_search(linked_list* L, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Busca elemento na lista, mas recebe uma funcao de
 * comparacao diferente da padrao, util para buscas
 * diferenciadas
 *
 * @param L
 * ponteiro para a lista
 *
 * @param info
 * elemento que sera buscado
 *
 * @param compare
 * funcao que substitui o padrão de comparacao
 *
 * @return
 * retorna o elemento encontrado ou NULL em caso de erro
 */
void* LL_search_with_another_compare(linked_list* L, void* info, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Conta a quantidade de elementos na lista
 *
 * @param L
 * ponteiro para a lista
 *
 * @return
 * o total de elementos na lista
 */
int LL_count(linked_list* L);

#endif
