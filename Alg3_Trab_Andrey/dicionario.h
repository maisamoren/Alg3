#ifndef __DICIONARIO__
#define __DICIONARIO__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "trie.h"

char caracterAtual (nodeTrie *nodo);

void inverterVetor (char vetor[]);

void imprimePalavraAchada (nodeTrie *nodo, FILE *outputFile, int x);

int verificaIgualdadeLetra (char key1, char key2);

int palavrasSemelhantes (nodeTrie *nodo, char *key, int letraAtual, int totalLetras, int errosMax, int errosAtual, FILE *outputFile, nodeTrie *vetor[], int *x);

void loadWords (nodeTrie *root, const char *filename);

void consultar (nodeTrie *root, const char *filename);

#endif
