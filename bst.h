#ifndef BST_H
#define BST_H
#include "projeto.h"

arvoreBST procuraMaiorEsquerda(arvoreBST raiz);
void inicializarBST(arvoreBST *raiz);
arvoreBST inserirBST(tipo_dado *valor, arvoreBST raiz);
// void in_orderBST(arvoreBST raiz, tabela *tabela);
int alturaBST(arvoreBST raiz);
arvoreBST removerBST(arvoreBST raiz, int valor);


#endif