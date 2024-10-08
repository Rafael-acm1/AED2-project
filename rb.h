#ifndef RB_H
#define RB_H
#include "projeto.h"



void inicializarRB(arvoreRB *raiz);
void inserirRB (tipo_dado *valor, arvoreRB *raiz);
void removerRB (int valor, arvoreRB *raiz);
void recolorir(arvoreRB pivo);
int alturaRB(arvoreRB raiz);
int maior(int a, int b);
tipo_dado *maior_elemento(arvoreRB raiz);
int menor_elemento(arvoreRB raiz);
// void in_orderRB(arvoreRB raiz);

void imprimir_elemento(arvoreRB raiz);
void imprimir(arvoreRB raiz);
void ajustar(arvoreRB *raiz, arvoreRB elemento);
void reajustar(arvoreRB *raiz, arvoreRB elemento);
void rotacao_simples_direitaRB(arvoreRB *raiz, arvoreRB pivo);
void rotacao_simples_esquerdaRB(arvoreRB *raiz, arvoreRB pivo);
void rotacao_dupla_direitaRB(arvoreRB *raiz, arvoreRB pivo);
void rotacao_dupla_esquerdaRB(arvoreRB *raiz, arvoreRB pivo);
enum cor cor(arvoreRB elemento);
int eh_raiz(arvoreRB elemento);
int eh_filho_esquerdo(arvoreRB elemento);
arvoreRB irmao(arvoreRB elemento);
arvoreRB tio(arvoreRB elemento);
void retira_duplo_preto(arvoreRB *raiz, arvoreRB elemento);


#endif