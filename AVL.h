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
	
    void* info;                     /*!< elemento que sera guardado na AVL, void para suportar polimorfismo */
	char balance_factor;            /*!< fator de balanceamento: altura esquerda - altura direita */
	struct node *left, *right;      /*!< encadeamento esquerda e direita */
    
} node;

/*!
 *  Registro que define a AVL
 */
typedef struct {
    
	node *root;                     /*!< raiz da AVL */
    int (*compare)(void*, void*);   /*!< ponteiro para funcao que compara elementos */
    
} AVL;


/*!
 
 Cria uma arvore AVL
 
 @param A
 ponteiro para arvore que sera criada
 
 @param int(*compare)(void*,void*)
 ponteiro para a funcao de comparacao dos elementos
 
 */
void AVL_create (AVL *A, int (*compare)(void*, void*));

/*!
 
 Insere um novo elemento na AVL
 
 @param A
 ponteiro para a arvore AVL
 
 @param x
 ponteiro para o elemento que sera inserido
 
 @result
 retorna 1 se a insersão foi bem sucedida, 0 caso contrário
 
 */
int AVL_insert (AVL *A, void* x);

/*!
 
 Apaga um elemento da AVL
 
 @param A
 ponteiro para a arvore AVL
 
 @param x
 ponteiro para o elemento que sera apagado
 
 @result
 retorna 1 se a operacao foi bem sucedida, 0 caso contrário (elemento nao encontrado)
 
 */
int AVL_delete (AVL *A, void* x);
