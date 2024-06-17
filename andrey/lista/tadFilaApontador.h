// TAD FILA APONTADOR - H

/*---------------------------------------------------------
Interface: TAD Fila
-----------------------------------------------------------*/

#ifndef __TADFILAAPONTADOR__
#define __TADFILAAPONTADOR__

#include <stdio.h>
#include <stdlib.h>
#include "tadArvBinInt.h"

typedef struct NodoFila {
    Nodo *valor;
    struct NodoFila *prox;
} NodoFila;

typedef struct Fila {
    NodoFila *front;
    NodoFila *rear;
} Fila;

Fila* criaFila ();

void enqueue (Fila* f, Nodo* no);

Nodo* dequeue (Fila* f);

#endif