#ifndef BST_H
#define BST_H
#include "projeto.h"



void inicializarAVL(arvoreAVL *raiz); 
arvoreAVL inserirAVL(arvoreAVL raiz, int valor, int *cresceu);
void in_orderAVL(arvoreAVL raiz);
int maiorAVL(arvoreAVL no);
arvoreAVL buscaAVL(int valor, arvoreAVL raiz);
int pai(arvoreAVL raiz, int i);
int alturaAVL(arvoreAVL raiz);
arvoreAVL descendentes(int valor, arvoreAVL raiz);
arvoreAVL removerAVL(arvoreAVL raiz, int valor);



#endif
