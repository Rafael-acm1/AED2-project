#ifndef SGBD_H
#define SGBD_H
#include "stdio.h"

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct JogadorSP {
	char nome[50];
	char posição[20];
    char nacionalidade[30];
    int idade;
    int numerocamisa;
} jogadorSP;

typedef struct indice {
	int chave;
	int indice; 
} tipo_dado;

typedef struct no_bst {
	tipo_dado *valor;
	struct no_bst *esq, *dir;
} no_bst;

typedef struct no_avl {
    tipo_dado *valor;
    int fb;
    struct no_avl* esq, *dir;
} no_avl;

typedef struct no_rb {
	tipo_dado *dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
} no_rb;

typedef no_bst* arvoreBST;
typedef no_avl* arvoreAVL;
typedef no_rb* arvoreRB;

typedef struct tabela {
	FILE *arquivo_dados;
	arvoreBST indice_bst;
    arvoreAVL indice_avl;
    arvoreRB indice_rb; 
} tabela;


int inicializarTabela(tabela *tabela);
void adicionarJogador(tabela *tabela, jogadorSP *jogador);
jogadorSP* lerDados();
void finalizar(tabela *tab);
void in_orderAVL(arvoreAVL raiz);
void removerIndice(tabela *tab, int *valor);
void adicionarIndice(tabela *tab, tipo_dado *valor);
void in_orderBST(arvoreBST raiz);
arvoreBST inserirBST(int valor, arvoreBST raiz);

#endif