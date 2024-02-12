#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
                       
#include <string.h>


void inicializarBST(arvoreBST *raiz) {
	*raiz = NULL;
}

arvoreBST inserir(int valor, arvoreBST raiz){
    if(raiz == NULL){
        arvoreBST novo = (arvoreBST) malloc(sizeof(struct no_bst));
        novo ->dir = NULL;
        novo-> esq = NULL;
        novo->valor = valor;
        return novo;
    }else{
        if(valor >= raiz->valor){
            raiz->dir = inserir(valor, raiz->dir);
        } else{
            raiz->esq  = inserir(valor, raiz->esq);
        }
    return raiz;
    }
    
}

void pre_orderBST(arvoreBST raiz){
    if(raiz != NULL){
        printf("[%d]", raiz->valor);

        pre_orderBST(raiz->esq);
        pre_orderBST(raiz->dir);
    }
}

void in_orderBST(arvoreBST raiz){
    if(raiz != NULL){
        

        in_orderBST(raiz->esq);
        printf("[%d]", raiz->valor);
        in_orderBST(raiz->dir);
    }
}


void pos_orderBST(arvoreBST raiz){
    if(raiz != NULL){
        pre_orderBST(raiz->esq);
        pre_orderBST(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}

void exibir_reverso(arvoreBST raiz){
    if(raiz != NULL) {
      
    exibir_reverso(raiz->dir);
    printf("[%d]", raiz->valor);
    exibir_reverso(raiz->esq);
}
}

int qtd_par(arvoreBST raiz){
    if (raiz == NULL) {
        return 0; 
    }
    int contador = 0;

    if(raiz->valor % 2 == 0){
       contador++; 
    }  
    contador += qtd_par(raiz->esq);
    contador += qtd_par(raiz->dir);

    return contador;
}

int pai(arvoreBST raiz, int i){


   if (raiz->valor == i ){
            printf("-1");
        }
    if ((raiz->esq != NULL && raiz->esq->valor == i) || (raiz->dir != NULL && raiz->dir->valor == i)){
            printf("[%d]", raiz->valor);
            
        }else {
        
        if (i < raiz->valor) {
            pai(raiz->esq, i);
        } else if (i > raiz->valor) {
            pai(raiz->dir, i);
        } else {
            printf("-1\n");
        }
    }

}

int somatorio(arvoreBST raiz) {
    if (raiz == NULL) {
        return 0; 
    }

    int soma = raiz->valor; 
    soma += somatorio(raiz->esq);
    soma += somatorio(raiz->dir); 

    return soma;
}

int somatorio_par(arvoreBST raiz){
     if (raiz == NULL) {
        return 0; 
    }

    int soma = 0;

    if (raiz->valor % 2 == 0){
        soma += raiz->valor;
    }
    soma += somatorio_par(raiz->esq);
    soma += somatorio_par(raiz->dir);

    return soma;

    }

arvoreBST podar(arvoreBST raiz, int i){
    if (raiz == NULL) {
        return 0; 
    }
    if (raiz->valor == i){
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    podar(raiz->esq, i);
    podar(raiz->dir, i);

    return raiz;
}

arvoreBST busca(int valor, arvoreBST raiz) {
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

void dobrar(arvoreBST raiz){
    int dobro;
    if(raiz != NULL){
        dobro = (raiz->valor) * (raiz->valor);
        printf("[%d]", dobro);
        dobrar(raiz->esq);
        dobro = (raiz->valor) * (raiz->valor);  
        dobrar(raiz->dir);
    }

}

arvoreBST mesclar(arvoreBST a, arvoreBST b){
    if (a == NULL) {
        return b; // Se a árvore 'a' é nula, retornamos 'b'
    }

    if (b == NULL) {
        return a; // Se a árvore 'b' é nula, retornamos 'a'
    }
    if(b->valor >= a->valor){
            a->dir = inserir(b->valor, a->dir);
        } else{
            a->esq  = inserir(b->valor, a->esq);
        }
    return b;
    }
void filhos(arvoreBST filha) {
    if (filha != NULL) {
        filhos(filha->esq);
        printf("[%d]", filha->valor);
        filhos(filha->dir);
    }
}
arvoreBST descendentes(int valor,arvoreBST raiz){
    
    if (raiz->valor == valor ){
        printf("Descendentes de [%d]: ", raiz->valor);
        filhos(raiz);
        printf("\n");
    } else{
        if(valor >= raiz->valor){
            return  descendentes(valor, raiz->dir);
        } else{
            return  descendentes(valor, raiz->esq);
        }
    }
}


int alturaBST(arvoreBST raiz){
    if (raiz == NULL) {
        return 0; 
    }
    int contadoresq = 0;
    if(raiz->valor % 1 == 0){
        contadoresq++; 
        } 
    int contadordir = 0;
    if(raiz->valor % 1 == 0){
        contadordir++; 
        } 
    contadoresq += alturaBST(raiz->esq);
    contadordir += alturaBST(raiz->dir);

    if(contadordir > contadoresq){
        return contadordir;
    } else{
        return contadoresq;
    }
}

arvoreBST procuraMaiorEsquerda(arvoreBST raiz);

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