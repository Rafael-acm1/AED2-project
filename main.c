#include "projeto.h"
#include "stdio.h"
#include "stdlib.h"
#include "bst.h"
#include "avl.h"
#include "rb.h"

int main(void) {
    tabela tb;
    int ret, opcao, chave;
    ret = inicializarTabela(&tb);

    while(1) {
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 1: // ADICIONAR JOGADOR
                adicionarJogador(&tb, lerDados());
                break;
            case 2: // Imprimir elementos
                in_orderBST(tb.indice_bst);
                in_orderAVL(tb.indice_avl);
                in_orderRB(tb.indice_rb);
                break;
            case 3: // BUSCAR ELEMENTO
                scanf("%d", &chave);
                buscaBST(chave, tb.indice_bst);
                break;
            case 4: // REMOVER ELEMENTO
                scanf("%d", &chave);
                removerIndice(&tb, chave);
                break;
            case 99: // SAIR
                finalizar(&tb);
                exit(99);
                break;
        
        default:
            break;
        }
    }

    return 1;
}