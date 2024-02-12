#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void inicializarBST(arvoreBST *raiz) {
	*raiz = NULL;
}

arvoreBST inserirBST(int valor, arvoreBST raiz){
    if(raiz == NULL){
        arvoreBST novo = (arvoreBST) malloc(sizeof(struct no_bst));
        novo ->dir = NULL;
        novo-> esq = NULL;
        novo->valor = valor;
        return novo;
    }else{
        if(valor >= raiz->valor){
            raiz->dir = inserirBST(valor, raiz->dir);
        } else{
            raiz->esq  = inserirBST(valor, raiz->esq);
        }
    return raiz;
    }
    
}


void in_orderBST(arvoreBST raiz){
    if(raiz != NULL){
        

        in_orderBST(raiz->esq);
        printf("[%d]", raiz->valor);
        in_orderBST(raiz->dir);
    }
}




arvoreBST buscaBST(int valor, arvoreBST raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->valor == valor) {
        return raiz;
    } else {
        if (valor >= raiz->valor) {
            return busca(valor, raiz->dir);
        } else {
            return busca(valor, raiz->esq);
        }
    }
}


arvoreBST remover(arvoreBST raiz, int valor){
    if(raiz == NULL){
    printf("Arvore vazia");
    return NULL;
    }
    if (raiz->valor == valor){
        //caso 1: elemento não possui filhos
        if(raiz->dir == NULL && raiz->esq == NULL){
            free(raiz);
            return NULL;
        }
        //caso 2a: elemento possui exatamente um filho(esq)
        if(raiz->dir == NULL && raiz->esq != NULL){
            arvoreBST retorno = raiz->esq;
            free(raiz);
            return retorno;
        }
        //caso 2b: elemento possui exatamente um filho(dir)
        if(raiz->esq == NULL && raiz->dir != NULL){
            arvoreBST retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        //caso 3: dois filhos if(//) {
           //localizar o maior elemento da sub arvore esquerda
        

        if(raiz->esq != NULL && raiz->dir != NULL){
            arvoreBST temp = raiz->esq;
            arvoreBST maiorEsqueda = procuraMaiorEsquerda(temp);
            //copiar o valor desse elemento para a raiz relativa
            raiz->valor = maiorEsqueda->valor;
            //remover a duplicata NA SUB-ÁRVORE ESQ
            raiz->esq = remover(raiz->esq, maiorEsqueda->valor);
        }


        //}
    }
    return raiz;
}

arvoreBST procuraMaiorEsquerda(arvoreBST raiz){
    arvoreBST no1 = raiz;
    arvoreBST no2 = raiz->dir;

    while(no2 != NULL){
        no1 = no2;
        no2 =no2->dir;
    }    
    return no1;
}