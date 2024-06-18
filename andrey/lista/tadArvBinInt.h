// TAD ARVORE BINARIA - H

/*---------------------------------------------------------
Interface: TAD Arvore
-----------------------------------------------------------*/

#ifndef __TADARVBININT__
#define __TADARVBININT__

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int item;
    struct Nodo *esq, *dir;
} Nodo;

Nodo *novoNo(int item);

Nodo *criaArv(int chaves[], int n);

void emOrdem(Nodo *n);

int somaChave(Nodo *raiz);

int valorMinimo(Nodo *raiz);

void paiMaior(Nodo *raiz);

Nodo *dobraArvore(Nodo *raiz);

void maxHeapify(Nodo *raiz);

void maiorNaRaiz(Nodo *raiz);

void heapifyInvertido(Nodo *raiz);

void ordenaPeloMaior(Nodo *raiz);

#endif
