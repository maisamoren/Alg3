// TAD FILA APONTADOR - C

#include <stdio.h>
#include <stdlib.h>
#include "tadFilaApontador.h"

// cria uma nova fila
Fila* criaFila () {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->front = f->rear = NULL;
    return f;
}

// enfilera um nó
void enqueue (Fila* f, Nodo* no) {
    NodoFila* nf = (NodoFila*)malloc(sizeof(NodoFila));
    nf->valor = no;
    nf->prox = NULL;
    if (f->rear == NULL) {
        f->front = f->rear = nf;
        return;
    }
    f->rear->prox = nf;
    f->rear = nf;
}

// desenfileira um nó
Nodo* dequeue (Fila* f) {
    if (f->front == NULL)
        return NULL;
    NodoFila* temp = f->front;
    f->front = f->front->prox;
    if (f->front == NULL)
        f->rear = NULL;
    Nodo* no = temp->valor;
    free(temp);
    return no;
}