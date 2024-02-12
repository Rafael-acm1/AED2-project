#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvoreRB no_null;

void inicializarRB(arvoreRB *raiz) {
	*raiz = NULL;
	no_null = (arvoreRB) malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
    no_null->pai = NULL;
}

arvoreRB tio(arvoreRB elemento) {
	return irmao(elemento->pai);
}

arvoreRB avo(arvoreRB elemento){
	return elemento->pai->pai;
}
void rotacao_dupla_direita(arvoreRB *raiz, arvoreRB pivo) {
    rotacao_simples_esquerda(raiz, pivo->esq);
    rotacao_simples_direita(raiz, pivo);
}
void rotacao_dupla_esquerda(arvoreRB *raiz, arvoreRB pivo){
    rotacao_simples_direita(raiz, pivo->dir);
    rotacao_simples_esquerda(raiz, pivo);
}
void adicionarRB (int valor, arvoreRB *raiz) {
	arvoreRB posicao, pai, novo;
	posicao = *raiz;
	pai = NULL;

	 while(posicao != NULL) {
			pai = posicao;
			if(valor > posicao->dado) 
					posicao = posicao->dir;
			else 
					posicao = posicao->esq;
	}


  
	novo = (arvoreRB) malloc(sizeof(struct no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;


	if(eh_raiz(novo))	
			*raiz = novo;
	else {
      
		if(valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}


	ajustar(raiz, novo);
}


void ajustar(arvoreRB *raiz, arvoreRB elemento){
    
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {

			if(cor(tio(elemento)) == VERMELHO) {
				recolorir(avo(elemento));
								
				elemento = elemento->pai->pai;
				continue;
			} 

			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
					rotacao_simples_direita(raiz, elemento->pai->pai);
					recolorir(elemento->pai);
					

					elemento = elemento->pai;
					continue;
			}
		
			if(!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
					rotacao_simples_esquerda(raiz, elemento->pai->pai);
					recolorir(elemento->pai);

					elemento = elemento->pai;
					continue;
			}

			if(!eh_filho_esquerdo(elemento)&&
			    eh_filho_esquerdo(elemento->pai)&&
			   (tio(elemento) == NULL ||
				tio(elemento)->cor == PRETO)) {

					rotacao_dupla_direita(raiz, elemento->pai->pai);
					recolorir(elemento);

					continue;
			}
			
			if(eh_filho_esquerdo(elemento)&&
			  !eh_filho_esquerdo(elemento->pai)&&
			  (tio(elemento) == NULL ||
			   tio(elemento)->cor == PRETO)) {

					rotacao_dupla_esquerda(raiz, elemento->pai->pai);
					recolorir(elemento);

					continue;
			}

	}
	(*raiz)->cor = PRETO;
}

/* Realiza a rotação simples direita
Antes da rotação: 
cor(p) = Preto
cor(u) = cor(v) = Vermelho

       p             u
      / \           / \
     u  t2   =>    v   p
    / \               / \
   v  t1             t1 t2

Após a rotação: 
cor(u) = Preto
cor(v) = cor(p) = Vermelho
*/
void rotacao_simples_direita(arvoreRB *raiz, arvoreRB pivo){
			arvoreRB u, t1;
			u = pivo->esq;
            t1 = u->dir;

            /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito*/
			int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
			//Atualização dos ponteiros
			pivo->esq = t1;
            if(t1 != NULL)
				t1->pai = pivo;

			u->dir = pivo;

			u->pai = pivo->pai;
			pivo->pai = u;

            //Se não existir árvore acima de u, u passa a ser a raiz da árvore
			if(eh_raiz(u))
				*raiz = u;
			else {
              //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
					if(posicao_pivo_esq)
							u->pai->esq = u;
					else
							u->pai->dir = u;
			}
}

void rotacao_simples_esquerda(arvoreRB *raiz, arvoreRB pivo) {
	arvoreRB u, t1;
	u = pivo->dir;
	t1= u->esq;
	/*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber 
	se o pivo p era um filho esquerdo ou direito*/
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	
	//Atualização dos ponteiros
	pivo->dir = t1;
	if(t1 != NULL)
		t1->pai = pivo;

	u->esq = pivo;
	u->pai = pivo->pai;
	pivo->pai = u;

	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if(eh_raiz(u))
		*raiz = u;
	else {
        /*Caso contrário (se existir) é preciso ligar o restante da árvore
		a esta sub-árvore, resultante da rotação*/
		if(posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}


void recolorir(arvoreRB pivo){
	
	if(pivo->esq != NULL)
		pivo->esq->cor = pivo->cor;
	if(pivo->dir != NULL)
		pivo->dir->cor = pivo->cor;
	//se o pivô for preto, vai receber a cor vermelha e vice-versa
	pivo->cor = (pivo->cor == PRETO)? VERMELHO : PRETO;
}

/*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
enum cor cor(arvoreRB elemento) {
	enum cor c;
	if(elemento==NULL)
		return PRETO;
	else
		return elemento->cor;
	return c;
}
/*Verifica se um nó é a raiz da árvore*/
int eh_raiz(arvoreRB elemento) {
	return (elemento->pai == NULL);
}
/*Verifica se um nó é filho esquerdo*/
int eh_filho_esquerdo(arvoreRB elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}



arvoreRB irmao(arvoreRB elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

void imprimir(arvoreRB raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

int alturaRB(arvoreRB raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(alturaRB(raiz->dir), alturaRB(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvoreRB raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado->chave;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvoreRB raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado->chave;
	else
			return maior_elemento(raiz->esq);
}

void pre_orderRB(arvoreRB raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_orderRB(raiz->esq);
		pre_orderRB(raiz->dir);
	}
}

void pos_order(arvoreRB raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_orderRB(arvoreRB raiz) {
	if(raiz != NULL) {
		in_orderRB(raiz->esq);
		imprimir_elemento(raiz);
		in_orderRB(raiz->dir);
	}
}

void imprimir_elemento(arvoreRB raiz) {
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}

void remover (int valor, arvoreRB *raiz) {
	arvoreRB posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado->chave) {
            if(posicao->esq != NULL && posicao->dir != NULL) { 
    			posicao->dado->chave = maior_elemento(posicao->esq);   
	    		remover(posicao->dado->chave, &(posicao->esq));
                break;
            }

			
			if(posicao->esq == NULL && posicao->dir != NULL) {
				posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;

				if(eh_raiz(posicao)) {
					*raiz = posicao->dir;
				} else {
					if(eh_filho_esquerdo(posicao)) {
    					posicao->pai->esq = posicao->dir;
					} else {
						posicao->pai->dir = posicao->dir;
    				}      
				}
                free(posicao);   
				break;
			}

			if(posicao->dir == NULL && posicao->esq != NULL) {
				posicao->esq->cor = PRETO;
				posicao->esq->pai = posicao->pai;

				if(eh_raiz(posicao)) {
					*raiz = posicao->esq;
				} else {
					if(eh_filho_esquerdo(posicao)) {
    					posicao->pai->esq = posicao->esq;
					} else {
						posicao->pai->dir = posicao->esq;
    				}      
				}
                free(posicao);   
				break;
			}

			
			if(posicao->esq == NULL && posicao->dir == NULL) {
									
				if(eh_raiz(posicao)) {
					*raiz = NULL;
                    free(posicao);
					break;
				}

				
				if(posicao->cor == VERMELHO) {
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
                    free(posicao);
					break;
				} else {
					
					no_null->cor = DUPLO_PRETO;
					no_null->pai = posicao->pai;
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = no_null;
					else
						posicao->pai->dir = no_null;
					free(posicao);
					reajustar(raiz, no_null);
					break;
				}
			}
		}	
		if(valor > posicao->dado->chave) 
				posicao = posicao->dir;
		else 
				posicao = posicao->esq;
	}
}

void reajustar(arvoreRB *raiz, arvoreRB elemento){

	//caso 1	
	if(eh_raiz(elemento)) {

		elemento->cor = PRETO;
        if(elemento == no_null) {
            *raiz = NULL;
		}
		return;
	}

	//caso 2
	if(  cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == VERMELHO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
                //Verifica se é o caso 2 esquerdo ou direito
				if(eh_filho_esquerdo(elemento))
						rotacao_simples_esquerda(raiz, elemento->pai);
				else
						rotacao_simples_direita(raiz, elemento->pai);	
				
                elemento->pai->pai->cor = PRETO;
				elemento->pai->cor = VERMELHO;
				
                //Atenção à chamada recursiva do reajustar.
                //O caso 2 não remove o duplo-preto
                reajustar(raiz, elemento);
				return;
	}

	//caso 3
	if(cor(elemento->pai) == PRETO &&
	   cor(irmao(elemento)) == PRETO &&
	   cor(irmao(elemento)->dir) == PRETO &&
	   cor(irmao(elemento)->esq) == PRETO ) {

			//Verificar e remover o no_null
			elemento->pai->cor = DUPLO_PRETO;
			irmao(elemento)->cor = VERMELHO;
			
			arvoreRB pai = elemento->pai;
			retira_duplo_preto(raiz, elemento);
			
			//Chamada recursiva para eliminar o duplo preto do elemento P
			//reajustar(raiz, elemento->pai);
			reajustar(raiz, pai);
			return ;
	}	

	//caso 4
	if(cor(elemento->pai) == VERMELHO &&
	   cor(irmao(elemento)) == PRETO &&
	   cor(irmao(elemento)->dir) == PRETO &&
	   cor(irmao(elemento)->esq) == PRETO ) {	

			//Verificar e remover o no_null
			elemento->pai->cor = PRETO;
			irmao(elemento)->cor = VERMELHO;

			retira_duplo_preto(raiz, elemento);
			
			return;
	}

    //Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
	//caso 5a
	if(eh_filho_esquerdo(elemento) &&
	   cor(irmao(elemento)) == PRETO &&
	   cor(irmao(elemento)->dir) == PRETO &&
	   cor(irmao(elemento)->esq) ==VERMELHO) {	

			rotacao_simples_direita(raiz, irmao(elemento));
			recolorir(irmao(elemento));
			if(irmao(elemento)->esq != NULL)
				irmao(elemento)->esq->cor = PRETO;

			reajustar(raiz, elemento);
			return;
	}

	//caso 5b
	if(!eh_filho_esquerdo(elemento) &&
	    cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->dir) == VERMELHO &&
	    cor(irmao(elemento)->esq) == PRETO) {	

			rotacao_simples_esquerda(raiz, irmao(elemento));
			recolorir(irmao(elemento));
			if(irmao(elemento)->dir != NULL)
				irmao(elemento)->dir->cor = PRETO; 

			reajustar(raiz, elemento);
			return;
	}

	//caso 6a
	if(eh_filho_esquerdo(elemento) &&
	   cor(irmao(elemento)) == PRETO &&
	   cor(irmao(elemento)->dir) == VERMELHO) {	

			irmao(elemento)->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			irmao(elemento)->dir->cor = PRETO;

			rotacao_simples_esquerda(raiz, elemento->pai);
			retira_duplo_preto(raiz, elemento);

			return;
	}

	//caso 6b
	if(!eh_filho_esquerdo(elemento) &&
	    cor(irmao(elemento)) == PRETO &&
	    cor(irmao(elemento)->esq) == VERMELHO) {	

			irmao(elemento)->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			irmao(elemento)->esq->cor = PRETO;

			rotacao_simples_direita(raiz, elemento->pai);
			retira_duplo_preto(raiz, elemento);

			return;
	}
}

void retira_duplo_preto(arvoreRB *raiz, arvoreRB elemento) {
			if(elemento == no_null)
				if(eh_filho_esquerdo(elemento))
						elemento->pai->esq = NULL;
				else
						elemento->pai->dir = NULL;
			else
				elemento->cor = PRETO;
}

