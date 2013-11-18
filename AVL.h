/* 
 * Arvore Binaria de Busca Balanceada: AVL
 * 
 * 
 */

typedef int elem;

typedef struct no {
	elem info;	// informacao guardada por no
	
	char fb;	// fator de balanceamento: altura esquerda - altura direita
	struct no *esq, *dir;	// encadeamento esquerda e direita
} No;

typedef struct {
	No *raiz;
} AVL;
