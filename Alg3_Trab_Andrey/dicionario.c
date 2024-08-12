#ifndef __DICIONARIO__
#define __DICIONARIO__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "dicionario.h"

// Descobre o caracter do nodo atual
char caracterAtual (nodeTrie *nodo) {

    nodeTrie *aux = nodo->root;
    char volta = 'a';

    if (nodo->root == NULL)
        return '?';

    for (int i = 0; i < MAX; i++){
        if (aux->childNode[i] == nodo){
            return i + volta;}
    }

    return '?';
}

void inverterVetor (char vetor[]) {
    int x = strlen(vetor) - 1;

    char auxiliar;

    for (int i = 0; i < (x/2); i++) {
        auxiliar = vetor[i];
        vetor[i] = vetor[x-i-1];
        vetor[x-i-1] = auxiliar;
    }
}

// Imprime palavras encontradas
void imprimePalavraAchada (nodeTrie *nodo, FILE *outputFile, int contagem) {

    int tamanhoNodo, preencheNodo;
    nodeTrie *auxiliar;
    char *vetorAuxiliar;

    tamanhoNodo = 0;
    auxiliar = nodo;

    if (contagem >= MAX_LISTA) {
        return;
    }

    // Calcula o tamanho da palavra encontrada na trie
    while (auxiliar->root != NULL) {
        tamanhoNodo++;
        auxiliar = auxiliar->root;
    }

    // Aloca memória para o vetor auxiliar com tamanho encontrado anteriormente
    vetorAuxiliar = calloc (tamanhoNodo, sizeof(char));

    auxiliar = nodo;

    // Preenche o vetor auxiliar com as letras da palavra encontrada
    for (int i= 0; i <= tamanhoNodo; i++) {
        vetorAuxiliar[i] = caracterAtual(auxiliar);
        auxiliar = auxiliar->root;
    }

    inverterVetor (vetorAuxiliar);

    // Imprime a palavra encontrada
    for (int i = 0; i < tamanhoNodo; i++){
        fprintf(outputFile, "%c", vetorAuxiliar[i]);
    }

    fprintf(outputFile, ",");

    // Desaloca vetor utilizado
    free (vetorAuxiliar);

    return;
}

// Verifica se as letras sao iguais
int verificaIgualdadeLetra (char key1, char key2) {

    if ((key1 == key2) || (key1 - 32 == key2)){
        return 1;
    }
    return 0;
}

int palavrasSemelhantes (nodeTrie *nodo, char *key, int letraAtual, int totalLetras, int errosMax, int errosAtual, FILE *outputFile, int contagem) {

    // If de seguranca para garantir que nao entre em locais da memoria indevidos (seja um nodo nulo )
    if (nodo == NULL) {
        return 0;
    }

    // Verifica se a letra atual da palavra eh igual a letra da arvore
    if (verificaIgualdadeLetra(caracterAtual(nodo), key[letraAtual]) != 1)
        errosAtual = errosAtual + 1;

    // Caso o numero de erros atuais seja maior que o maximo permitido, retorna impedindo busca desnecessarias
    if (errosAtual <= errosMax) {

        // Caso seja o fim de alguma palavra, verifica se enquadra dentro do erro permitido
        if (nodo->wordEnd == 1) {
            int errosAgora = errosAtual + (totalLetras - letraAtual - 1);
            if (errosAgora <= errosMax) {
                imprimePalavraAchada(nodo, outputFile, contagem);
                contagem++;
            }
        }

        for (int i = 0; i < MAX; i++) {            
            contagem = contagem + palavrasSemelhantes(nodo->childNode[i], key, letraAtual + 1, totalLetras, errosMax, errosAtual, outputFile, contagem);
        }

        // Chamadas de recursividade para achar palavras semelhantes buscando por todas possibilidades
        // if para garantir que palavras não acabem se repetindo no processo
        if (verificaIgualdadeLetra(caracterAtual(nodo), key[letraAtual]) != 1){  
            for (int i = 0; i < MAX; i++) {
                if (nodo->childNode[i] != NULL) {
                    // Chamada para proxima letra da trie apenas
                    contagem = contagem + palavrasSemelhantes(nodo->childNode[i], key, letraAtual, totalLetras, errosMax, errosAtual, outputFile, contagem);
                } else {
                    // Chamada para proxima letra do vetor apenas
                    contagem = contagem + palavrasSemelhantes(nodo->childNode[i], key, letraAtual + 1, totalLetras, errosMax, errosAtual, outputFile, contagem);
                }
            }
            /* // Chamada para proxima letra do vetor apenas
            contagem = contagem + palavrasSemelhantes(nodo, key, letraAtual + 1, totalLetras, errosMax, errosAtual, outputFile, contagem); */
        }

    }

    return contagem;
}

void loadWords (nodeTrie *root, const char *filename) {

    FILE *file = fopen(filename, "r");

    // Verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        perror("Erro ao abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD]; // Armazena cada palavra lida

    while (fscanf(file, "%99s", word) != EOF) {
        insertTrie(root, word); // Insere a palavra lida na TRIE
    }

    fclose(file);
}

void consultar (nodeTrie *root, const char *filename) {

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    // Abre o arquivo de saída para escrita
    FILE *outputFile = fopen("saida.txt", "w");
    if (outputFile == NULL) {
        perror("Erro ao abrir o arquivo.");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *word = calloc(MAX_WORD, sizeof(char)); // Armazenar cada palavra da consulta
    int errosMax;

    // Lê as consultas do arquivo uma por uma
    while (fscanf(file, "%99s %d", word, &errosMax) != EOF) {

        for (int i = 0; i < strlen(word); i++) {
            fprintf (outputFile, "%c", word[i]);
        }

        fprintf (outputFile, ":");

        // Busca palavras na árvore que estejam a uma distância de edição especificada
        palavrasSemelhantes(root, word, 0, strlen(word), errosMax, 0, outputFile, 0);

        fprintf (outputFile, "\n");
    }

    // Fecha os arquivos após a leitura e escrita
    fclose(file);
    fclose(outputFile);
    free (word);
}
