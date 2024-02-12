#ifndef SGBD_H
#define SGBD_H
#include "stdio.h"

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

// typedef struct livro {
// 	char titulo[81];
// 	char autor[51];
// 	char isbn[21];
// 	int codigo;

// } dado;

typedef struct JogadorSP {
	char nome[81];
	char posição[51];
    char nacionalidade[50];
    int idade;
    int numerocamisa;
	int CPF;
} info;

typedef struct indice {
	int chave;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_dado;

typedef struct no_bst {
	tipo_dado *valor;
	struct no_bst *esq, *dir;
} no_bst;

typedef struct no_avl {
    int valor;
    int fb;
    struct no_avl* esq, *dir;
} no_avl;

typedef struct no_rb {
	tipo_dado dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
} no_rb;


typedef struct tabela {
	FILE *arquivo_dados;
	arvoreBST indice_bst;
    arvoreAVL indice_avl;
    arvoreRB indice_rb; 
} tabela;

typedef no_bst* arvoreBST;
typedef no_avl* arvoreAVL;
typedef no_rb* arvoreRB;



#endif