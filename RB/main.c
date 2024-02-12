// #include <stdio.h>
// #include <stdlib.h>
// #include "rb.h"

// int main(int argc, char * argv[]) {
//     arvore a;
//     int opcao;
//     inicializar(&a);

//     while(1) {
//         printf("\nEscolha uma opcaoo:\n");
//         printf("1 - Altura da árvore\n");
//         printf("2 - Adicionar elemento\n");
//         printf("3 - Maior elemento\n");
//         printf("4 - Menor elemento\n");
//         printf("5 - Pre-order\n");
//         printf("6 - In-order\n");
//         printf("7 - Pos-order\n");
//         // printf("8 - Remover elemento\n");
//         printf("9 - Imprimir árvore\n");
//         printf("99 - Sair\n");

//         scanf("%d", &opcao);

//         switch(opcao) {
//             int valor;
//             case 1:
//                 printf("Altura: %d\n", altura(a));
//                 break;
//             case 2:
//                 printf("Digite o valor a ser inserdio: ");
//                 scanf("%d", &valor);
//                 adicionar(valor, &a);
//                 printf("Valor %d adicionado\n", valor);
//                 break;
//             case 3:
//                 printf("Maior elemento: %d\n", maior_elemento(a));
//                 break;
//             case 4:
//                 printf("Menor elemento: %d\n", menor_elemento(a));
//                 break;
//             case 5:
//                 printf("Pre-order: ");
//                 pre_order(a);
//                 printf("\n");
//                 break;
//             case 6:
//                 printf("In-order: ");
//                 in_order(a);
//                 printf("\n");
//                 break;
//             case 7:
//                 printf("Pos-order: ");
//                 pos_order(a);
//                 printf("\n");
//                 break;
//             // case 8:
//             //     scanf("%d", &valor);
//             //     remover(valor, &a);
//             //     printf("Valor %d removido\n", valor);
//             //     break;
//             case 9:
//                 printf("Árvore: ");
//                 imprimir(a);
//                 printf("\n");
//                 break;
//             case 99:
//                 exit(0);
//             default:
//                 printf("Opção inválida. Tente novamente.\n");
//                 break;
//         }
//     }
// }
