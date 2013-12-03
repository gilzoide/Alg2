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
    int height;
	struct node *left, *right;      /*!< encadeamento esquerda e direita */
    
} node;

/*!
 *  Registro que define a AVL
 */
typedef struct {
    
	node *root;                     /*!< raiz da AVL */
    int (*compare)(void*, void*);   /*!< ponteiro para funcao que compara elementos */
    
} AVL;


// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Cria uma arvore AVL
 
 @param A
 ponteiro para arvore que sera criada
 
 @param int(*compare)(void*,void*)
 ponteiro para a funcao de comparacao dos elementos
 
 */
void AVL_create (AVL *A, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Insere um novo elemento na AVL
 
 @param A
 ponteiro para a arvore AVL
 
 @param x
 ponteiro para o elemento que sera inserido
 
 */
void AVL_insert (AVL *A, void* x);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Retira um elemento da AVL
 
 @param A
 ponteiro para a arvore AVL
 
 @param x
 ponteiro para o elemento que sera retirado
 
 @result
 retorna o elemento retirado, ou NULL em caso de erro
 
 */
void* AVL_delete (AVL* A, void* x);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Imprime o conteudo de uma AVL em pre-ordem 
 de acordo com a funcao de impressao
 passada como parametro
 
 @param A
 ponteiro para a arvore AVL
 
 @param print_content
 funcao que imprime elementos na tela
 
 */
void AVL_pre_order(AVL* A, void (*print_content)(void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /
/*!
 
 Imprime o conteudo de uma AVL em ordem
 de acordo com a funcao de impressao
 passada como parametro
 
 @param A
 ponteiro para a arvore AVL
 
 @param print_content
 funcao que imprime elementos na tela
 
 */
void AVL_in_order(AVL* A, void (*print_content)(void*));
