// TAD ARVORE BINARIA - C

#include <stdio.h>
#include <stdlib.h>
#include "tadArvBinInt.h"
#include "tadFilaApontador.h"

// cria um novo nó da árvore
Nodo *novoNo (int item) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if (!n){
        return NULL;
    }

    n->item = item;
    n->esq = NULL;
    n->dir = NULL;

    return n;
}

// cria árvore
Nodo *criaArv (int chaves[], int n) {
    if (n == 0) {
        return NULL;
    }

    Nodo *raiz = novoNo(chaves[0]);
    Fila *f = criaFila();
    enqueue(f, raiz);

    int i = 1;
    while (i < n){
        Nodo *temp = dequeue(f);

        if (i < n) {
            temp->esq = novoNo(chaves[i++]);
            enqueue(f, temp->esq);
        }

        if (i < n) {
            temp->dir = novoNo(chaves[i++]);
            enqueue(f, temp->dir);
        }
    }

    return raiz;
}

void emOrdem (Nodo *n) {
    if (!n){
        return;
    }

    emOrdem(n->esq);
    printf("%d ", n->item);
    emOrdem(n->dir);
}

// soma de todas as chaves da árvore
int somaChave (Nodo *raiz) {
    if (raiz == NULL){
        return 0;
    }

    return raiz->item + somaChave(raiz->esq) + 
           somaChave(raiz->dir);
}

// encontra o valor mínimo na árvore
int valorMinimo(Nodo* raiz) {
    if (raiz == NULL){
        return 0;
    }

    int min = raiz->item;

    if (raiz->esq != NULL) {
        int minEsq = valorMinimo(raiz->esq);
        if (minEsq < min){
            min = minEsq;
        }
    }

    if (raiz->dir != NULL) {
        int minDir = valorMinimo(raiz->dir);
        if (minDir < min){
            min = minDir;
        }
    }

    return min;
}

// altera a árvore para que a chave do nó pai seja 
// igual a chave do maior filho 
void paiMaior (Nodo *raiz) {
    if (raiz == NULL) {
        return;
    }

    paiMaior(raiz->esq);
    paiMaior(raiz->dir);

    if (raiz->esq != NULL || raiz->dir != NULL){
        int e = (raiz->esq != NULL) ? raiz->esq->item :
                raiz->item;
        int d = (raiz->dir != NULL) ? raiz->dir->item :
                raiz->item;
        raiz->item = (e > d) ? e : d;
    }
}

// dobra a quantidade de nós da árvore
Nodo *dobraArvore (Nodo *raiz) {
    if (raiz == NULL){
        return NULL;
    }

    Nodo *novoPai;

    if (raiz->item % 2 == 0){
        novoPai = novoNo(raiz->item + 1);
        novoPai->esq = raiz;
    } else {
        novoPai = novoNo(raiz->item - 1);
        novoPai->dir = raiz;
    }

    raiz->esq = dobraArvore(raiz->esq);
    raiz->dir = dobraArvore(raiz->dir);

    return novoPai;
}

// maiorNaRaiz () {

// }