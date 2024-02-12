#ifndef BST_H
#define BST_H
#include "projeto.h"



void inicializarAVL(arvoreAVL *raiz); 
arvoreAVL inserirAVL(arvoreAVL raiz, int valor, int *cresceu);
void pre_orderAVL(arvoreAVL raiz);
void in_orderAVL(arvoreAVL raiz);
void pos_orderAVL(arvoreAVL raiz);
int somatorio(arvoreAVL raiz);
arvoreAVL buscaAVL(int valor, arvoreAVL raiz);
void dobrar(arvoreAVL raiz);
void exibir_reverso(arvoreAVL raiz);
int qtd_par(arvoreAVL raiz);
int somatorio_par(arvoreAVL raiz);
int pai(arvoreAVL raiz, int i);
arvoreAVL podar(arvoreAVL raiz, int i);
int alturaAVL(arvoreAVL raiz);
arvoreAVL descendentes(int valor, arvoreAVL raiz);
arvoreAVL remover_avl(arvoreAVL raiz, int valor);


#endif
