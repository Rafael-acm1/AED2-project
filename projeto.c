#include "projeto.h"
#include "string.h"
#include <stdlib.h>
#include "avl.h"
#include "rb.h"
#include "bst.h"


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
            adicionarRB(temp, &(tab->indice_rb));
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arqRB);
    }

    arqBST = fopen("indices_bst.dat", "rb");
    if(arqBST != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arqBST)) {
            tab->indice_bst = inserirBST(tab->indice_bst, temp);
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arqBST);
    }
}


void carregarIndices(tabela *tab) {
    carregar_arquivos(tab);
}

int inicializarTabela(tabela *tabela) {
    inicializarIndices(tabela);
    tabela->arquivo_dados = fopen("dados.dat", "a+b");
    carregarIndices(tabela);

    return (tabela->arquivo_dados != NULL);
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

void tirarEnter(char *string){
    string[strlen(string) - 1] = '\0';
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