#include "sgbd.h"
#include "string.h"
#include <stdlib.h>
#include "AVL/avl.h"
#include "RB/rb.h"
#include "BST/bst.h"


void inicializar_indices(tabela *tab) {
    inicializarAVL(&tab->indice_avl);
    inicializarRB(&tab->indice_rb);
    inicializarBST(&tab->indice_bst);
}

void carregar_arquivos(tabela *tab) {
    tipo_dado *temp;
    FILE *arq;
    arq = fopen("indices_avl.dat", "rb");
    int cresceu;
    if(arq != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arq)) {
            tab->indice_avl = inserir_avl(tab->indice_avl, temp, &cresceu);
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arq);
    }

    arq = fopen("indices_arb.dat", "rb");
    if(arq != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arq)) {
            adicionar_rb(temp, &(tab->indice_rb));
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arq);
    }

    arq = fopen("indices_bst.dat", "rb");
    if(arq != NULL) {
        temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        while(fread(temp, sizeof(tipo_dado), 1, arq)) {
            tab->indice_bst = inserir_bst(tab->indice_bst, temp);
            temp = (tipo_dado*) malloc(sizeof(tipo_dado));
        }
        fclose(arq);
    }
}

// Carregar os valores de um arquivo "indices.dat" para cada árvore índice
void carregar_indices(tabela *tab) {
    carregar_arquivos(tab);
}

int inicializar_tabela(tabela *tabela) {
    inicializar_indices(tabela);
    tabela->arquivo_dados = fopen("dados.dat", "a+b");
    carregar_indices(tabela);

    if (tabela->arquivo_dados != NULL)
        return 1;
    else
        return -1;
}

void adicionar_indice(tabela *tab, tipo_dado *novo) {
    int cresceu;
    tab->indice_bst = inserir_bst(tab->indice_bst, novo);
    tab->indice_avl = inserir_avl(tab->indice_avl, novo, &cresceu);
    adicionar_rb(novo, &(tab->indice_rb));
}

void remover_indice(tabela *tab, int chave) {
    int diminuiu;
    tab->indice_bst = remover_bst(tab->indice_bst, chave);
    tab->indice_avl = remover_avl(tab->indice_avl, chave, &diminuiu);
    remover_rb(chave, &(tab->indice_rb));
}

info* ler_dados() {
    info *novo = (info*) malloc(sizeof(info));
    getchar();
    printf("Nome: ");
    fgets(novo->nome, 80, stdin);
    tirar_enter(novo->nome);

    printf("Posição: ");
    fgets(novo->posição, 36, stdin);
    tirar_enter(novo->posição);

    printf("Nacionalidade: ");
    fgets(novo->nacionalidade, 36, stdin);
    tirar_enter(novo->nacionalidade);

    printf("Idade: ");
    scanf("%d", &novo->idade);
    
    printf("Numero da camisa: ");
    scanf("%d", &novo->numerocamisa);
    return novo;
}

void tirar_enter(char *string){
    string[strlen(string) - 1] = '\0';
}

void in_order(tabela *tab) {
	in_orderBST(tab->indice_bst, tab);
	in_orderAVL(tab->indice_avl, tab);
	in_orderRB(tab->indice_rb, tab);
}

void adicionar_jogador(tabela *tabela, info *jogador) {
    if (tabela->arquivo_dados != NULL) {
        tipo_dado *novo_dado = (tipo_dado *) malloc(sizeof(tipo_dado));
        novo_dado->chave = jogador->CPF;

        // desloca o fluxo para o fim do arquivo
        fseek(tabela->arquivo_dados, 0L, SEEK_END);
        novo_dado->indice = ftell(tabela->arquivo_dados);

        fwrite(jogador, sizeof(info), 1, tabela->arquivo_dados);
        // Chama a função responsável por adicionar em cada índice
        adicionar_indice(tabela, novo_dado);
    }
}


// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// e)

void salvar_arquivo(tabela *tab) {
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
    salvar_arquivo(tab);
}


    // h)

void busca(tabela *tab, arvoreAVL raiz, int chave) {
    if (raiz == NULL)
        return;
    
    if(raiz->valor->chave == chave)
        // imprimir_elemento(raiz, tab);
        
    
    if (chave > raiz->valor->chave)
        busca(tab, raiz->dir, chave);
    else
        busca(tab, raiz->esq, chave);
}