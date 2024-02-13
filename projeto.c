#include "projeto.h"
#include "string.h"
#include <stdlib.h>
#include "avl.h"
#include "rb.h"
#include "bst.h"


// void in_orderBST(arvoreBST raiz){
//     if(raiz != NULL){
//         in_orderBST(raiz->esq);
//         printf("[%d]", raiz->valor);
//         in_orderBST(raiz->dir);
//     }
// }

void in_orderBST(arvoreBST raiz){
    if(raiz != NULL){
        

        in_orderBST(raiz->esq);
        printf("[%d]", raiz->valor);
        in_orderBST(raiz->dir);
    }
}
arvoreBST inserirBST(int valor, arvoreBST raiz){
    if(raiz == NULL){
        arvoreBST novo = (arvoreBST) malloc(sizeof(struct no_bst));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->valor->chave = valor;
        return novo;
    }else{
        if(valor >= raiz->valor->chave){
            raiz->dir = inserirBST(valor, raiz->dir);
        } else{
            raiz->esq  = inserirBST(valor, raiz->esq);
        }
    return raiz;
    }
    
}
void adicionarIndice(tabela *tab, tipo_dado *valor) {
    int cresceu;
    tab->indice_bst = inserirBST(tab->indice_bst, valor->chave);
    tab->indice_avl = inserirAVL(tab->indice_avl, valor->chave, cresceu);
    inserirRB(valor->chave, tab->indice_rb);
    // tab->indice_rb = inserirRB(tab->indice_rb, valor->chave);
}
void removerIndice(tabela *tab, int *valor) {
    int cresceu;
    tab->indice_bst = removerBST(tab->indice_bst, valor);
    tab->indice_avl = removerAVL(tab->indice_avl, valor);
    removerRB(valor, tab->indice_rb);
}
void inicializarIndices(tabela *tab) {
    inicializarAVL(&tab->indice_avl);
    inicializarRB(&tab->indice_rb);
    inicializarBST(&tab->indice_bst);
}

void carregarArquivos(tabela *tab) {
    tipo_dado *temp;
    FILE *arqBST,*arqAVL, *arqRB;
    arqAVL = fopen("indices_avl.dat", "rb");
    int cresceu;
    if(arqAVL != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arqAVL)) {
            tab->indice_avl = inserirAVL(tab->indice_avl, temp, cresceu);
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arqAVL);
    }

    arqRB = fopen("indices_arb.dat", "rb");
    if(arqRB != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arqRB)) {
            inserirRB(temp, &(tab->indice_rb));
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arqRB);
    }

    arqBST = fopen("indices_bst.dat", "rb");
    if(arqBST != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arqBST)) {
            tab->indice_bst = inserirBST(temp,tab->indice_bst);
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arqBST);
    }
}


void carregarIndices(tabela *tab) {
    carregarArquivos(tab);
}

int inicializarTabela(tabela *tabela) {
    inicializarIndices(tabela);
    tabela->arquivo_dados = fopen("dados.dat", "a+b");
    carregarIndices(tabela);

    return (tabela->arquivo_dados != NULL);
}
void tirarEnter(char *string){
    string[strlen(string) - 1] = '\0';
}
jogadorSP* lerDados() {
    jogadorSP *novo = (jogadorSP*) malloc(sizeof(jogadorSP));
    getchar();
    printf("Nome: ");
    fgets(novo->nome, 50, stdin);
    tirarEnter(novo->nome);

    printf("Posição: ");
    fgets(novo->posição, 20, stdin);
    tirarEnter(novo->posição);

    printf("Nacionalidade: ");
    fgets(novo->nacionalidade, 30, stdin);
    tirarEnter(novo->nacionalidade);

    printf("Idade: ");
    scanf("%d", &novo->idade);
    
    printf("Numero da camisa: ");
    scanf("%d", &novo->numerocamisa);
    return novo;
}



void adicionarJogador(tabela *tabela, jogadorSP *jogador) {
    if (tabela->arquivo_dados != NULL) {
        tipo_dado *novo_dado = (tipo_dado *) malloc(sizeof(tipo_dado));
        novo_dado->chave = jogador->numerocamisa;

        fseek(tabela->arquivo_dados, 0L, SEEK_END);
        novo_dado->indice = ftell(tabela->arquivo_dados);

        fwrite(jogador, sizeof(jogadorSP), 1, tabela->arquivo_dados);
        adicionarIndice(tabela, novo_dado);
    }
}

void salvar_auxiliar_bst(arvoreBST raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->valor, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar_bst(raiz->esq, arq);
		salvar_auxiliar_bst(raiz->dir, arq);
	}

}
void salvar_auxiliar_avl(arvoreAVL raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->valor, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar_avl(raiz->esq, arq);
		salvar_auxiliar_avl(raiz->dir, arq);
	}

}
void salvar_auxiliar_rb(arvoreRB raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar_rb(raiz->esq, arq);
		salvar_auxiliar_rb(raiz->dir, arq);
	}

}

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// e)

void salvarArquivo(tabela *tab) {
    FILE *arq;
    arq = fopen("indices_bst.dat", "wb");
    if(arq != NULL) {
        salvar_auxiliar_bst(tab->indice_bst, arq);
		fclose(arq);
    }

    arq = fopen("indices_avl.dat", "wb");
    if(arq != NULL) {
        salvar_auxiliar_avl(tab->indice_avl, arq);
		fclose(arq);
    }

    arq = fopen("indices_arb.dat", "wb");
    if(arq != NULL) {
        salvar_auxiliar_rb(tab->indice_rb, arq);
		fclose(arq);
    }
}

void finalizar(tabela *tab) {
    fclose(tab->arquivo_dados);
    salvarArquivo(tab);
}


    // h)

void busca(tabela *tab, arvoreAVL raiz, int chave) {
    if (raiz == NULL)
        return;
    
    if (raiz->valor->chave == chave)
        
    if (chave > raiz->valor->chave)
        busca(tab, raiz->dir, chave);
    else
        busca(tab, raiz->esq, chave);
}