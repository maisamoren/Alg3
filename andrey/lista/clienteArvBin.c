// MAIN

#include <stdio.h>
#include <stdlib.h>
#include "tadArvBinInt.h"
#include "tadFilaApontador.h"

// imprime regras para arvore
void elementos (){
    printf("\nEsse programa usa árvores binárias, para iniciar o programa, é preciso digitar o número de nós que sua árvore terá e os valores de cada nó.");
}

// imprime o menu das funções
void entrada () {
    printf("\nPara realizar as operações em uma árvore binária, escolha uma opção entre as abaixo: \n\n");
    printf("a. Somatória dos valores de todas as chaves de uma árvore binária;\n");
    printf("b. Calcula o valor mínimo das chaves de uma árvore binária;\n");
    printf("c. Alteração da árvoe binária para que o valor de um nó pai seja igual que o valor de seu maior filho;\n");
    printf("d. Multiplicamos a quantidade de nós da árvore binária;\n");
    printf("e. Alteração nos valores de uma árvore binária, de maneira que o maior valor fique na raiz;\n");
    printf("f. Alteração em uma árvore binária de maneira que cada nó tenha o maior valor dos seus filhos, mantendo todas as chaves na árvore;\n");
    printf("g. Para imprimir a árvore binária;\n");
    printf("z. Para sair do programa.\n");
    printf("\nDigite uma das opções: \n");
}

int main () {

    printf("\nBem vindo!\n");

    elementos();
    int numNos;
    printf("\n\nDigite o número de nós da árvore:");
    scanf("%d", &numNos);
    int chaves[numNos-1];
    printf("Digite as chaves dos nós da árvore:\n");
    int i = 0;
    while (i <= numNos-1) {
        scanf("%d ", &chaves[i]);
        i++;
    }

    Nodo *raiz = criaArv(chaves, numNos);

    char opcao = 'y';
    entrada();

    while (opcao != 'z') {

        if (opcao == 'a'){
            int soma;
            soma = somaChave(raiz);
            printf("A soma de todas as chaves da árvore é: %d", soma);
            printf("\n\n");
        }

        if (opcao == 'b'){
            int min;
            min = valorMinimo(raiz);
            printf("\n\nO valor mínimo das chaves que estão na árvore é: %d", min);
        }

        if (opcao == 'c'){
            paiMaior(raiz);
            printf("\n\nO valor foi alterado. Para vizualizar, escolha a opção de imprimir a árvore.");
        }

        if (opcao == 'd'){
            Nodo *novaRaiz;
            novaRaiz = dobraArvore(raiz); 
            printf("\n\nA árvore agora está alterada, com o dobro de nós. A impressão da árvore segue a ordem - esquerda, raiz, direita:");
            emOrdem(novaRaiz); 
        }

        if (opcao == 'e'){
            maiorNaRaiz(); 
        }

        if (opcao == 'f'){
            //
        }

        if (opcao == 'g'){
            printf("A impressão da árvore binária segue a ordem - esquerda, raiz, direita:");
            emOrdem(raiz);
            printf("\n\n");
        }

        scanf("%c", &opcao);
    }

    printf("\nObrigado por usar esse programa! Até mais.");

    // entrada();
    // scanf("%d", &opcao);

    // Nodo *raiz = criaArv(chaves, numNos);

    // switch (opcao){
    //     case 1:
    //         int soma;
    //         soma = somaChave(raiz);
    //         printf("\n\nA soma de todas as chaves da árvore é: %d", soma);
    //     break;

    //     case 2:
    //         int min;
    //         min = valorMinimo(raiz);
    //         printf("\n\nO valor mínimo das chaves que estão na árvore é: %d", min);
    //     brek;

    //     case 3:
    //         paiMaior(raiz);
    //         printf("\n\nO valor foi alterado. Para vizualizar, escolha a opção de imprimir a árvore.");
    //     break;

    //     case 4:
    //         Nodo *novaRaiz;
    //         novaRaiz = dobraArvore(raiz);
    //         printf("\n\nA árvore agora está alterada, com o dobro de nós. Para vizualizar a nova árvore, digite 1; Caso não queira, digite 0.");
            
    //         int op;
    //         scanf("%d", &op);
            
    //         switch (op){
    //             case 1: 
    //                 printf("\n\nA impressão da árvore binária segue a ordem - esquerda, raiz, direita:\n");
    //                 emOrdem(novaRaiz);
    //             break;

    //             case 0:
    //             break;
    //         }
    //     break;

    //     case 5:
    //         // maiorNaRaiz ()
    //     break;

    //     case 6:
    //         //
    //     break;

    //     case 7:
    //         printf("\n\nA impressão da árvore binária segue a ordem - esquerda, raiz, direita:\n");
    //         emOrdem(raiz);
    //     break;

    //     case 0:
    //         printf("\nObrigado por usar esse programa! Até mais.");
    //     break;
    // }

    return 0;    
}
