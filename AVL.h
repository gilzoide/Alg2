/*! @file AVL.h __TAD AVL__
 *
 *  @authors Gil Barbosa Reis - 8532248
 *  @authors Leonardo Sampaio Ferraz Ribeiro - 8532300
 */

/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  ALG1 - Trabalho 2
 *  AVL.h
 *
 *  Gil Barbosa Reis                    Nº8532248
 *  gil.reis@usp.br
 *
 *  Leonardo Sampaio Ferraz Ribeiro     Nº8532300
 *  leonardo.sampaio.ribeiro@usp.br
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * */


/*!
 *  Registro que define um no/folha/subarvore da AVL
 */
typedef struct node {
	
    void* info;                     /*!< elemento que será guardado na AVL, void para suportar polimorfismo */
	char balance_factor;            /*!< fator de balanceamento: altura esquerda - altura direita */
	struct node *left, *right;      /*!< encadeamento esquerda e direita */
    
} node;

/*!
 *  Registro que define a AVL
 */
typedef struct {
    
	node *root;                     /*!< raiz da AVL */
    int (*compare)(void*, void*);   /*!< ponteiro para função que compara elementos */
    
} AVL;


/*!
 * Cria uma arvore AVL
 *
 * @param A
 * ponteiro para árvore que será criada
 *
 * @param compare
 * ponteiro para a função de comparação dos elementos
 *
 */
void AVL_create (AVL *A, int (*compare)(void*, void*));

/*!
 * Insere um novo elemento na AVL
 *
 * @param A
 * ponteiro para a árvore AVL
 *
 * @param x
 * ponteiro para o elemento que será inserido
 *
 * @result
 * retorna 1 se a inserção foi bem sucedida, 0 caso contrário
 *
 */
int AVL_insert (AVL *A, void* x);

/*!
 * Apaga um elemento da AVL
 *
 * @param A
 * ponteiro para a árvore AVL
 *
 * @param x
 * ponteiro para o elemento que será apagado
 *
 * @result
 * retorna 1 se a operação foi bem sucedida, 0 caso contrário (elemento não encontrado)
 *
 */
node* AVL_delete (AVL *A, void* x);
