#ifndef BST_H
#define BST_H
#include "../sgbd.h"



// typedef struct livro {
// 	char titulo[81];
// 	char autor[51];
// 	char isbn[21];
// 	int codigo;
// } dado;

// typedef struct indice {
// 	int chave;
// 	int indice; //posição no arquivo do primeiro byte do registro
// } tipo_dado;

// typedef struct no_bst {
// 	tipo_dado *dado;
// 	struct no_bst *esq, *dir;
// } no_bst;


// typedef struct tabela {
// 	FILE *arquivo_dados;
// 	arvoreBST indices;
// } tabela;

// typedef no_bst* arvoreBST;

void inicializarBST(arvoreBST *raiz)
arvoreBST inserir(int valor, arvoreBST raiz);
void pre_orderBST(arvoreBST raiz);
void in_order(arvoreBST raiz);
void pos_order(arvoreBST raiz);
int somatorio(arvoreBST raiz);
arvoreBST busca(int valor, arvoreBST raiz);
void dobrar(arvoreBST raiz);
arvoreBST mesclar(arvoreBST a, arvoreBST b);
void exibir_reverso(arvoreBST raiz);
int qtd_par(arvoreBST raiz);
int somatorio_par(arvoreBST raiz);
int pai(arvoreBST raiz, int i);
arvoreBST podar(arvoreBST raiz, int i);
int alturaBST(arvoreBST raiz);
arvoreBST descendentes(int valor,arvoreBST raiz);
arvoreBST remover(arvoreBST raiz, int valor);

#endif


