// TRABALHO 1 - AVL - ALG 3 
// Maisa Carolina Moreno Girardi - GRR20204081
// Raphael Augusto Surmacz - GRR2021____

#include <stdio.h>
#include <stlib.h>

// ___________________________________________________________________________________
no *cria_avl(int chave){
    no *n = malloc(sizeof(no));

    if (n != NULL){
        n->depth=0;
        n->chave=chave;
        n->esq=NULL;
        n->dir=NULL;
        n->pai=NULL;
        return n;
    }
    return NULL;
}
// ___________________________________________________________________________________
struct TNo {
    char valor;
    int altura;
    tNo *esq, *dir;
}
// ___________________________________________________________________________________
void inicio(){
    printf ("       BEM VINDO!");
    printf ("           Esse programa foi feito para impletar uma arvore AVL.");
    printf ("           Abaixo voce tera o menu inicial:\n");
    printf (" -----------| OPCOES |-----------");
    printf (" |                              |");
    printf (" |  i - inserir um valor na AVL |");
    printf (" |  r - remover um valor na AVL |");
    printf (" |  t - travessia em ordem      |");
    printf (" |  p - imprimir a arvore AVL   |");
    printf (" |  q - sair do programa        |");
    printf (" |                              |");
    printf (" --------------------------------");
}
// ___________________________________________________________________________________
void fim(){
    printf ("\n");
    printf ("   OBRIGADA POR USAR O PROGRAMA!");
    printf ("       Tchau! =) ");
}
// ___________________________________________________________________________________
// void em_ordem(node *n, int h){
//     if (n == NULL) return;

//     em_ordem(n->esq, h+1);
//     printf("%d, %d \n", n->chave, h);
//     em_ordem(n->dir, h+1);
// }
// ___________________________________________________________________________________
// void imprime (node *n, int depth){
//     int i;
//     if(n){
//         imprime(n->R_son, depth+1);
//         printf("\n\n");
//         for(i=0; i<depth; i++)
//             printf("\t");
//         printf("%d",n->key);
//         imprime(n->L_son, depth+1);
//     }
// }
// ___________________________________________________________________________________
tNo *min (Tno *no){
    if (n->esq == NULL) return no;
    else
        return min(no->esq);
}
// ___________________________________________________________________________________
int main (){
    char opc, int chave;

    inicio();
    scanf("%c %d", &op, &chave);

    __ = cria_avl (chave);

    while (op != 's'){
        // comparar chars
        se op == i
            inserir
            balancear 
        se op == r
            busca bst pelo no
            substitui no por seu antecessor ou sucessor em ordem
        se op == t
            // em_ordem(n, h);
        se op == p 
            // imprime(n, depth);
        scanf ("%c, &op");
    }
    fim();
}