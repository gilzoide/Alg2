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

typedef void elem;

/*!
 *  Registro que define um no/folha/subarvore da AVL
 */
typedef struct node {
	
    elem* info;                     /*!< elemento que sera guardado na AVL */
	char balance_factor;            /*!< fator de balanceamento: altura esquerda - altura direita */
	struct node *left, *right;      /*!< encadeamento esquerda e direita */
    
} node;

/*!
 *  Registro que define a AVL
 */
typedef struct {
    
	node *root;                     /*!< raiz da AVL */
    int (*compare)(elem*, elem*);   /*!< ponteiro para funcao que compara elementos */
    int size_of_elem;               /*!< tamanho de um elemento */
    
} AVL;
