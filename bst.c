#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void inicializarBST(arvoreBST *raiz) {
	*raiz = NULL;
}



arvoreBST inserirBST(tipo_dado *valor, arvoreBST raiz){
    if(raiz == NULL){
        arvoreBST novo = (arvoreBST) malloc(sizeof(struct no_bst));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->valor = valor;
        return novo;
    }else{
        if(valor->chave >= raiz->valor->chave){
            raiz->dir = inserirBST(valor, raiz->dir);
        } else{
            raiz->esq  = inserirBST(valor, raiz->esq);
        }
    return raiz;
    }
    
}


arvoreBST removerBST(arvoreBST raiz, int valor){
    if(raiz == NULL){
    printf("Arvore vazia");
        return NULL;
    }
     if(valor > raiz->valor->chave){
            raiz->dir = removerBST(raiz->dir, valor);
        }

    if(valor < raiz->valor->chave){
             raiz->esq = removerBST(raiz->esq, valor);
        }
    if (raiz->valor->chave == valor){
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
            arvoreBST maiorEsquerda = procuraMaiorEsquerda(temp);
            //copiar o valor desse elemento para a raiz relativa
            raiz->valor = maiorEsquerda->valor;
            //remover a duplicata NA SUB-ÁRVORE ESQ
            raiz->esq = removerBST(raiz->esq, raiz->valor->chave);
        }

       
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