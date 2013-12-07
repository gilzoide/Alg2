/*! @file AVL.h @brief __TAD__ _AVL_
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
	
    void* info;             /*!< elemento que sera guardado na AVL, _void_ para suportar polimorfismo */
    int height;				/*!< Altura do nó */
	struct node *left;		/*!< Filho esquerdo */
	struct node *right;     /*!< Filho direito direita */
    
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
 * Cria uma arvore AVL
 *
 * @param A
 * ponteiro para arvore que sera criada
 *
 * @param compare
 * ponteiro para a funcao de comparacao dos elementos
 */
void AVL_create (AVL *A, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Insere um novo elemento na AVL
 *
 * @param A
 * ponteiro para a arvore AVL
 *
 * @param x
 * ponteiro para o elemento que sera inserido
 */
void AVL_insert (AVL *A, void* x);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Retira um elemento da AVL
 *
 * @param A
 * ponteiro para a arvore AVL
 *
 * @param x
 * ponteiro para o elemento que sera retirado
 *
 * @result
 * retorna o elemento retirado, ou NULL em caso de erro
 */
void* AVL_delete (AVL* A, void* x);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Retira um elemento da AVL, mas recebe uma funcao de
 * comparacao diferente da padrao, util para buscas
 * diferenciadas
 *
 * @param A
 * ponteiro para a arvore AVL
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
void* AVL_delete_with_another_compare(AVL* A, void* info, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime o conteudo de uma AVL em pre-ordem 
 * de acordo com a funcao de impressao
 * passada como parametro
 *
 * @param A
 * ponteiro para a arvore AVL
 *
 * @param print_content
 * funcao que imprime elementos na tela
 */
void AVL_pre_order(AVL* A, void (*print_content)(void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Imprime o conteudo de uma AVL em ordem
 * de acordo com a funcao de impressao
 * passada como parametro
 *
 * @param A
 * ponteiro para a arvore AVL
 *
 * @param print_content
 * funcao que imprime elementos na tela
 */
void AVL_in_order(AVL* A, void (*print_content)(void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Busca elemento na AVL
 *
 * @param A
 * ponteiro para a arvore AVL
 *
 * @param info
 * elemento que sera buscado
 *
 * @return
 * retorna o elemento encontrado ou NULL em caso de erro
 */
void* AVL_search(AVL* A, void* info);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Busca elemento na AVL, mas recebe uma funcao de
 * comparacao diferente da padrao, util para buscas
 * diferenciadas
 *
 * @param A
 * ponteiro para a arvore AVL
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
void* AVL_search_with_another_compare(AVL* A, void* info, int (*compare)(void*, void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Conta a quantidade de elementos na AVL
 *
 * @param A
 * ponteiro para a árvore AVL
 *
 * @return
 * o total de elementos na AVL
 */
int AVL_count(AVL* A);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Conta a quantidade de elementos na AVL aplicando uma
 * função de peso em cada elemento
 *
 * @param A
 * ponteiro para a árvore AVL
 *
 * @param counter
 * função que define o peso de um elemento
 *
 * @return
 * o total de elementos na AVL de acordo com os pesos
 */
int AVL_count_with_function(AVL* A, int (*counter)(void*));

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Destroi a AVL
 *
 * @param A
 * ponteiro para a árvore AVL
 *
 */
void AVL_destroy(AVL* A);

// / / / / / / / / / / / / / / / / / / / / / / / / / / /

/*!
 * Destroi a AVL, aplicando uma função,
 * passada como parâmetro, em cada elemento apagado
 *
 * @param A
 * ponteiro para árvore AVL
 *
 * @param destroy_elem
 * função que será aplicada nos elementos
 */
void AVL_destroy_with_function(AVL* A, void (*destroy_elem)(void*));


