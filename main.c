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

    printf("Jogadores do SAO PAULO FC\n\n");

    while(1) {
        
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 1: // ADICIONAR JOGADOR
                printf("Qual jogador do Maior clube do Brasil voce quer adicionar?\n");
                adicionarJogador(&tab, lerDados());
                break;
            case 2: // Imprimir elementos
                printf("\nBST :\n");
                in_orderBST(tab.indice_bst, &tab);
                printf("\nAVL :\n");
                in_orderAVL(tab.indice_avl, &tab);
                printf("\nRB :\n");
                in_orderRB(tab.indice_rb, &tab);
                break;
            case 3: // BUSCAR ELEMENTO
                printf("Digite o numero da camisa do jogador que voce busca\n");
                scanf("%d", &chave);
                buscaBST(chave, tab.indice_bst, &tab);
                break;
            case 4: // REMOVER ELEMENTO
                printf("Digite o numero da camisa do jogador que voce quer remover\n");
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