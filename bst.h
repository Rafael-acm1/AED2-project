#ifndef BST_H
#define BST_H
#include "projeto.h"

void inicializarBST(arvoreBST *raiz);
arvoreBST inserirBST(int valor, arvoreBST raiz);
void pre_orderBST(arvoreBST raiz);
void in_order(arvoreBST raiz);
void pos_order(arvoreBST raiz);
int somatorio(arvoreBST raiz);
arvoreBST buscaBST(int valor, arvoreBST raiz);
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


