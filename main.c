#include "projeto.h"
#include "stdio.h"
#include "stdlib.h"
#include "bst.h"
#include "avl.h"
#include "rb.h"

int main(void) {
    tabela tab;
    int ret, opcao, chave;
    ret = inicializarTabela(&tab);

    while(1) {
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 1: // ADICIONAR JOGADOR
                adicionarJogador(&tab, lerDados());
                break;
            case 2: // Imprimir elementos
                in_orderBST(tab.indice_bst, &tab);
                in_orderAVL(tab.indice_avl, &tab);
                in_orderRB(tab.indice_rb, &tab);
                break;
            case 3: // BUSCAR ELEMENTO
                scanf("%d", &chave);
                buscaBST(chave, tab.indice_bst, &tab);
                break;
            case 4: // REMOVER ELEMENTO
                scanf("%d", &chave);
                removerIndice(&tab, chave);
                break;
            case 99: // SAIR
                finalizar(&tab);
                exit(99);
                break;
        
        default:
            break;
        }
    }

    return 1;
}