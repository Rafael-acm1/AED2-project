#include "projeto.h"
#include "string.h"
#include <stdlib.h>
#include "avl.h"
#include "rb.h"
#include "bst.h"

arvoreBST procuraMaiorEsquerda(arvoreBST raiz);
void inicializarBST(arvoreBST *raiz);
arvoreBST inserirBST(tipo_dado *valor, arvoreBST raiz);
int alturaBST(arvoreBST raiz);
arvoreBST removerBST(arvoreBST raiz, int valor);
void imprimir_elemento_bst(arvoreBST raiz, tabela * tb);
void in_orderBST(arvoreBST raiz, tabela *tabela);
void in_orderAVL(arvoreAVL raiz,tabela *tabela);
void in_orderRB(arvoreRB raiz, tabela *tabela);



// void in_orderBST(arvoreBST raiz){
//     if(raiz != NULL){
//         in_orderBST(raiz->esq);
//         printf("[%d]", raiz->valor);
//         in_orderBST(raiz->dir);
//     }
// }

void imprimir_elemento_bst(arvoreBST raiz, tabela * tb) {
  jogadorSP *temp = (jogadorSP*) malloc(sizeof(jogadorSP));
  temp->numerocamisa = 999;
  printf("Indice: %d\n", raiz->valor->indice);
  fseek(tb->arquivo_dados, raiz->valor->indice, SEEK_SET);
  fread(temp, sizeof(jogadorSP), 1, tb->arquivo_dados);
  printf("[%s, %s, %s, %d, %d, ]\n",temp->nome, temp->posicao, temp->nacionalidade, temp->numerocamisa, temp->idade);
  free(temp);
}

void imprimir_elemento_avl(arvoreAVL raiz, tabela * tb) {
  jogadorSP *temp = (jogadorSP*) malloc(sizeof(jogadorSP));
  temp->numerocamisa = 999;
  printf("Indice: %d\n", raiz->valor->indice);
  fseek(tb->arquivo_dados, raiz->valor->indice, SEEK_SET);
  fread(temp, sizeof(jogadorSP), 1, tb->arquivo_dados);
  printf("[%s, %s, %s, %d, %d, ]\n",temp->nome, temp->posicao, temp->nacionalidade, temp->numerocamisa, temp->idade);
  free(temp);
}

void imprimir_elemento_rb(arvoreRB raiz, tabela * tb) {
  jogadorSP *temp = (jogadorSP*) malloc(sizeof(jogadorSP));
  temp->numerocamisa = 999;
  printf("Indice: %d\n", raiz->dado->indice);
  fseek(tb->arquivo_dados, raiz->dado->indice, SEEK_SET);
  fread(temp, sizeof(jogadorSP), 1, tb->arquivo_dados);
  printf("[%s, %s, %s, %d, %d, ]\n",temp->nome, temp->posicao, temp->nacionalidade, temp->numerocamisa, temp->idade);
  free(temp);
}
  
void in_orderBST(arvoreBST raiz, tabela *tabela){
    if(raiz != NULL){
        in_orderBST(raiz->esq, tabela);
        imprimir_elemento_bst(raiz, tabela);
        in_orderBST(raiz->dir, tabela);
    }
}
void in_orderAVL(arvoreAVL raiz, tabela *tabela){
    if(raiz != NULL){
        in_orderAVL(raiz->esq, tabela);
        imprimir_elemento_avl(raiz, tabela);
        in_orderAVL(raiz->dir, tabela);
    }
}

void in_orderRB(arvoreRB raiz, tabela *tabela) {
	if(raiz != NULL) {
		in_orderRB(raiz->esq,tabela);
		imprimir_elemento_rb(raiz, tabela);
		in_orderRB(raiz->dir,tabela);
	}
}

void adicionarIndice(tabela *tab, tipo_dado *valor) {
    int cresceu;
    tab->indice_bst = inserirBST(valor, tab->indice_bst);
    tab->indice_avl = inserirAVL(tab->indice_avl, valor, &cresceu);
    inserirRB(valor, &tab->indice_rb);
}
void removerIndice(tabela *tab, int valor) {
    int cresceu;
    tab->indice_bst = removerBST(tab->indice_bst, valor);
    tab->indice_avl = removerAVL(tab->indice_avl, valor);
    removerRB(valor, &tab->indice_rb);
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
            tab->indice_avl = inserirAVL(tab->indice_avl, temp, &cresceu);
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
    fgets(novo->posicao, 20, stdin);
    tirarEnter(novo->posicao);

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
        int cresceu;
        tabela->indice_bst = inserirBST(novo_dado, tabela->indice_bst);
        tabela->indice_avl = inserirAVL(tabela->indice_avl, novo_dado, &cresceu);
        inserirRB(novo_dado, &tabela->indice_rb);
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

// void busca(tabela *tab, arvoreAVL raiz, int chave) {
//     if (raiz == NULL)
//         return;

//     if (raiz->valor->chave == chave)
//         imprimir_elemento_bst(raiz, tab);
//     if (chave > raiz->valor->chave)
//         busca(tab, raiz->dir, chave);
//     else
//         busca(tab, raiz->esq, chave);
// }

void buscaBST(int valor, arvoreBST raiz, tabela *tabela) {
    if (raiz == NULL) {
        return;
    }

    if (raiz->valor->chave == valor) {
        imprimir_elemento_bst(raiz, tabela);
    } else {
        if (valor >= raiz->valor->chave) {
            buscaBST(valor, raiz->dir, tabela);
        } else {
            buscaBST(valor, raiz->esq, tabela);
        }
    }
}