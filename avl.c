#include "avl.h"
#include <stdio.h>
#include <stdlib.h>



void inicializarAVL(arvoreAVL *raiz) {
	*raiz = NULL;
}


arvoreAVL rotacao_simples_esquerda(arvoreAVL pivo) {
    //inicialização
    arvoreAVL u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;


    //Atualização dos ponteiros
    u->esq = pivo;
    pivo->dir = t2;

    return u;

}

arvoreAVL rotacao_simples_direita(arvoreAVL pivo){
    arvoreAVL u, t1, t2, t3;
    u = pivo->esq;
    t3 = pivo->dir;
    t1 = u->esq;
    t2 = u->dir;

    //Atualizando os ponteiros
    u->dir = pivo;
    pivo->esq = t2;

    return u;
}

arvoreAVL rotacao_dupla_direita(arvoreAVL pivo) {
    pivo->esq = rotacao_simples_esquerda(pivo->esq);
    return rotacao_simples_direita(pivo);
}

arvoreAVL rotacao_dupla_esquerda(arvoreAVL pivo) {
    pivo->dir = rotacao_simples_direita(pivo->dir);
    return rotacao_simples_esquerda(pivo);
}

arvoreAVL rotacao(arvoreAVL pivo) {
    if (pivo->fb > 0) {
        // Rotação esquerda
        if (pivo->dir->fb >= 0) {
            if (pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
                // rotação simples esquerda
                return rotacao_simples_esquerda(pivo);
            }
        } else {
            pivo->fb = 0;
            pivo->dir->fb = 0;
            // rotação dupla esquerda
            return rotacao_dupla_esquerda(pivo);
        }
    } else {
        // Rotação direita
        if (pivo->esq->fb <= 0) {
            if (pivo->esq->fb == 0) {
                pivo->fb = 1;
                pivo->esq->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
                // rotação simples direita
                return rotacao_simples_direita(pivo);
            }
        } else {
            pivo->fb = 0;
            pivo->esq->fb = 0;
            // rotação dupla direita
            return rotacao_dupla_direita(pivo);
        }
    }

    return pivo;  
}


arvoreAVL inserirAVL(arvoreAVL raiz, tipo_dado *valor, int *cresceu){
    //caso base
    if(raiz == NULL) {
        arvoreAVL nova = (arvoreAVL) malloc(sizeof(struct no_avl));
        nova->valor = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;

        //3. Retornar o ponteiro para a raiz (relativa) da nova árvore
        *cresceu = 1;
        return nova;
    }
    //caso indutivo
    else {
        if(valor->chave > raiz->valor->chave) {
            raiz->dir = inserirAVL(raiz->dir, valor, cresceu);
            if(*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacao(raiz);
                        break;
                    case -1:
                         raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserirAVL(raiz->esq, valor, cresceu);
            if(*cresceu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case -1:
                        *cresceu = 0;
                        return rotacao(raiz);
                        break;
                }
        }
    }
    return raiz;
}
}






arvoreAVL buscaAVL(int valor, arvoreAVL raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->valor->chave == valor) {
        return raiz;
    } else {
        if (valor >= raiz->valor->chave) {
            return buscaAVL(valor, raiz->dir);
        } else {
            return buscaAVL(valor, raiz->esq);
        }
    }
}



void filhos(arvoreAVL filha) {
    if (filha != NULL) {
        filhos(filha->esq);
        printf("[%d]", filha->valor);
        filhos(filha->dir);
    }
}
arvoreAVL descendentes(int valor,arvoreAVL raiz){
    
    if (raiz->valor->chave == valor ){
        printf("Descendentes de [%d]: ", raiz->valor->chave);
        filhos(raiz);
        printf("\n");
    } else{
        if(valor >= raiz->valor->chave){
            return  descendentes(valor, raiz->dir);
        } else{
            return  descendentes(valor, raiz->esq);
        }
    }
}


int alturaAVL(arvoreAVL raiz){
    if (raiz == NULL) {
        return 0; 
    }
    int contadoresq = 0;
    if(raiz->valor->chave % 1 == 0){
        contadoresq++; 
        } 
    int contadordir = 0;
    if(raiz->valor->chave % 1 == 0){
        contadordir++; 
        } 
    contadoresq += alturaAVL(raiz->esq);
    contadordir += alturaAVL(raiz->dir);

    if(contadordir > contadoresq){
        return contadordir;
    } else{
        return contadoresq;
    }
}

tipo_dado *maiorAVL(arvoreAVL no) {
    // Encontrar o elemento mais à direita da árvore
    while (no->dir != NULL) {
        no = no->dir;
    }
    return no->valor;
}

int fator_balanceamento(arvoreAVL N) {
    if (N == NULL)
        return 0;

    // Calcular a altura da subárvore esquerda e direita
    int altura_esq = alturaAVL(N->esq);
    int altura_dir = alturaAVL(N->dir);

    // Calcular e retornar o fator de balanceamento
    return altura_esq - altura_dir;
}


arvoreAVL removerAVL(arvoreAVL raiz, int  valor) {
    
    // printf("%d\n", raiz->valor->chave);

    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor->chave) {
        // printf("entrou na raiz esquerda\n");
        raiz->esq = removerAVL(raiz->esq, valor);
    } else if (valor > raiz->valor->chave) {
        // printf("entrou na raiz direita\n");
        raiz->dir = removerAVL(raiz->dir, valor);
    } else {

        // caso 1: elemento não possui filhos (folha)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // caso 2a: elemento possui exatamente um filho(esq)
        if (raiz->esq != NULL && raiz->dir == NULL) {
            arvoreAVL retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

        // caso 2b: elemento possui exatamente um filho(dir)
        if (raiz->esq == NULL && raiz->dir != NULL) {
            arvoreAVL retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        // caso 3: dois filhos
        if (raiz->esq != NULL && raiz->dir != NULL) {
            // localizar o maior elemento da subárvore esquerda
            raiz->valor = maiorAVL(raiz->esq);
            // remover a duplicata na subárvore esq
            raiz->esq = removerAVL(raiz->esq, raiz->valor->chave);
        }
    }

    // Realizar rotações, se necessário
    // Rotação à direita
    if (raiz->fb > 1 && valor < raiz->esq->valor->chave) {
        return rotacao_simples_direita(raiz);
    }

    // Rotação à esquerda
    if (raiz->fb < -1 && valor > raiz->dir->valor->chave) {
        return rotacao_simples_esquerda(raiz);
    }

    // Rotação dupla à esquerda e depois à direita
    if (raiz->fb > 1 && valor > raiz->esq->valor->chave) {
        raiz->esq = rotacao_simples_esquerda(raiz->esq);
        return rotacao_simples_direita(raiz);
    }

    // Rotação dupla à direita e depois à esquerda
    if (raiz->fb < -1 && valor < raiz->dir->valor->chave) {
        raiz->dir = rotacao_simples_direita(raiz->dir);
        return rotacao_simples_esquerda(raiz);
    }

    // Atualizar a altura do nó atual
    raiz->fb = fator_balanceamento(raiz);

    return raiz;
}
