// MAIN

#include "tadArvBinInt.h"
#include "tadFilaApontador.h"
#include <stdio.h>
#include <stdlib.h>

// imprime regras para arvore
void elementos() {
    printf("\nEsse programa usa árvores binárias, para iniciar o programa, é preciso digitar o número de nós que sua árvore terá e os valores de cada nó.");
}

// imprime o menu das funções
void entrada() {
    printf("\nPara realizar as operações na árvore binária selecionada, escolha uma opção entre as abaixo: \n\n");
    printf("a. Somatória dos valores de todas as chaves da árvore;\n");
    printf("b. Impressão do menor valor entre as chaves da árvore;\n");
    printf("c. Alteração na árvore para que o valor de um nó pai seja igual que o valor de seu maior filho;\n");
    printf("d. Duplicação da quantidade de nós da árvore - segue a seguinte regra: Se o valor do nó n for par (k), cria-se um novo pai de n, que tem valor k+1 e o nó n se torna o filho esquerdo. Se o valor por ímpar (j), cria-se o novo pai com valor k-1 e o nó n se torna o filho da direita;\n");
    printf("e. Alteração nos valores da árvore para que o maior valor fique na raiz, trocando os valores de nós;\n");
    printf("f. Alteração na árvore para que cada nó tenha o maior valor dos seus filhos, mantendo todas as chaves na árvore;\n");
    printf("g. Impressão da árvore binária;\n");
    printf("x. Sair do programa.\n");
    printf("\nDigite uma das opções: \n");
}

int main() {

    printf("\nBem vindo!\n");

    elementos();
    int numNos;
    printf("\n\nDigite o número de nós da árvore: ");
    scanf("%d", &numNos);

    int chaves[numNos];
    printf("Digite as chaves dos nós da árvore - para finalizar a leitura, digite 0:\n");
    for (int i = 0; i < numNos; i++) {
        scanf("%d ", &chaves[i]);
    }

    Nodo *raiz = criaArv(chaves, numNos);

    char opcao = 'y';
    entrada();

    while (opcao != 'x') {

        if (opcao == 'a') {
            int soma;
            soma = somaChave(raiz);
            printf("A soma de todas as chaves da árvore é: %d", soma);
            printf("\n\n");
        }

        if (opcao == 'b') {
            int min;
            min = valorMinimo(raiz);
            printf("O valor mínimo das chaves que estão na árvore é: %d", min);
            printf("\n\n");
        }

        if (opcao == 'c') {
            paiMaior(raiz);
            printf("A árvore foi alterada; agora a raiz contém o maior valor. Para visualizar a árvore, selecione a opção 'g'.");
            printf("\n\n");
        }

        if (opcao == 'd') {
            raiz = dobraArvore(raiz);
            printf("A árvore foi alterada; agora com o dobro de nós. Para visualizar a árvore, selecione a opção 'g'.");
            printf("\n\n");
        }

        if (opcao == 'e') {
            maiorNaRaiz(raiz);
            printf("A árvore foi alterada; o maior valor está na raiz e ocorrerão as trocas. Para visualizar a árvore, selecione a opção 'g'.");
            printf("\n\n");
        }

        if (opcao == 'f') {
            ordenaPeloMaior(raiz);
            printf("A árvore foi alterada; cada nó tem o maior valor entre seus filhos. Para visualizar a árvore, selecione a opção 'g'.");
            printf("\n\n");
        }

        if (opcao == 'g') {
            printf("A impressão da árvore binária segue a ordem - esquerda, raiz, direita: ");
            emOrdem(raiz);
            printf("\n\n");
        }

        scanf("%c", &opcao);
    }

    printf("\nObrigado por usar esse programa! Até mais.");

    return 0;
}
