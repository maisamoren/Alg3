#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 26 
#define MAX_WORD 100
#define MAX_LISTA 20

typedef struct nodeTrie {
    int wordEnd;
    struct nodeTrie *root;
    struct nodeTrie *childNode[MAX];
} nodeTrie;

// Aloca o nodo da trie
nodeTrie *createNode () {

    nodeTrie *new = (nodeTrie*)malloc(sizeof(nodeTrie));
    new->wordEnd = 0;
    new->root = NULL;

    for (int i = 0; i < MAX; i++){
        new->childNode[i] = NULL;
    }
    return new;
}

// Busca o nodo da trie
int searchTrie (nodeTrie *root, char *key) {

    nodeTrie *aux = root;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = key[i];

        // verifica se o nó existe para o char atual na árvore
        if (aux->childNode[c-'a'] == NULL) {
            return 0; // palavra n existe na trie
        }

        // move o ponteiro aux para o nó já existente para o chat atual
        aux = aux->childNode[c-'a'];
    }
    return (aux->wordEnd);
}

// Insere uma palavra na trie
void insertTrie (nodeTrie *root, char *key) {

    nodeTrie *current = root;

    for (int i = 0; i < strlen(key); i++){
        // Verifica se nao ha caracteres especiais, se houver ela nao eh inserida na trie
        if ((key[i] <= 64) || (key[i] >= 91 && key[i] <= 96) || (key[i] >= 123))
            return; 
    }

    for (int i = 0; i < strlen(key); i++) {
        char c = key[i];
        int x;
        // Converte letras maiúsculas e minusculas para o indice certo

        if ((c-'a' < MAX) && (c - 'a' >= 0))
        {
            if (current->childNode[c-'a'] == NULL){
                nodeTrie *new = createNode();
                new->root = current;
                current->childNode[c-'a'] = new;
                x = c - 'a';
                current = current->childNode[x];
            }
            else current = current->childNode[c-'a'];
        } 
        else {
            if (current->childNode[c-'A'] == NULL){
                nodeTrie *new = createNode();
                new->root = current;
                current->childNode[c-'A'] = new;
                x = c - 'A';
                current = current->childNode[x];
            }
            else current = current->childNode[c-'A'];
        }
    }
    current->wordEnd = 1;
}

// Verifica se o nodo esta vazio
bool empty (nodeTrie *root) {

    for (int i = 0; i < MAX; i++) {
        if (root->childNode[i] != NULL) {
            return false;
        }
    }

    return true;
}

nodeTrie *deleteTrieNode (nodeTrie *root, char *key, int depth) {

    // Verifica se a raiz é nula, caso sim retorna
    if (!root) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->wordEnd == 1) {
            root->wordEnd = 0;
        }
        if (empty(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = key[depth] - 'a';
    root->childNode[index] = deleteTrieNode(root->childNode[index], key, depth+1);

    if (empty(root) && root->wordEnd == 0) {
        free(root);
        root = NULL;
    }

    return root;
}

// Deleta a trie inteira no fim do programa
void deleteTrieTree (nodeTrie *root) {

    // Verifica se a raiz é nula, caso sim retorna
    if (!root) {
        return;
    }

    // Percorre primeiro todas as folhas da trie pra deletar de baixo para cima
    for (int i = 0; i < MAX; i++) {
        if (root->childNode[i] != NULL) {
            deleteTrieTree(root->childNode[i]);
        }
    }

    // Desaloca o nodo atual
    free(root);

    return;
}


// Descobre o caracter do nodo atual
char caracterAtual (nodeTrie *nodo) {
//
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


//
void inverterVetor (char vetor[])
{
    int x = strlen(vetor) - 1;

    char auxiliar;

    for (int i = 0; i < (x/2); i++)
    {
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
int verificaIgualdadeLetra (char key1, char key2){
    if ((key1 == key2) || (key1 - 32 == key2))
        return 1;
    return 0;
}

int palavrasSemelhantes (nodeTrie *nodo, char *key, int letraAtual, int totalLetras, int errosMax, int errosAtual, FILE *outputFile, int contagem) {

    // If de seguranca para garantir que nao entre em locais da memoria indevidos (seja um nodo nulo ou um fim de vetor que nao existe)
    if (nodo == NULL) {
        return 0;
    }

    // Verifica se a letra atual da palavra eh igual a letra da arvore
    if (verificaIgualdadeLetra(caracterAtual(nodo), key[letraAtual]) != 1)
           errosAtual = errosAtual + 1;

    // Caso o numero de erros atuais seja maior que o maximo permitido, retorna impedindo busca desnecessarias
    if (errosAtual <= errosMax){

        // Caso seja o fim de alguma palavra, verifica se enquadra dentro do erro permitido
        if (nodo->wordEnd == 1){
            int errosAgora = errosAtual + (totalLetras - letraAtual - 1);
            if (errosAgora <= errosMax){
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
                    }
                }
                // Chamada para proxima letra do vetor apenas
                contagem = contagem + palavrasSemelhantes(nodo, key, letraAtual + 1, totalLetras, errosMax, errosAtual, outputFile, contagem);
            }

    }

    return contagem;
}

void loadWords (nodeTrie *root, const char *filename) {

    FILE *file = fopen(filename, "r");

    // Verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        perror("erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD]; // Buffer para armazenar cada palavra lida

    while (fscanf(file, "%99s", word) != EOF) {
        insertTrie(root, word); // Insere a palavra lida na TRIE
    }

    fclose(file);
}

void process (nodeTrie *root, const char *filename) {

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    // Abre o arquivo de saída para escrita
    FILE *outputFile = fopen("saida.txt", "w");
    if (outputFile == NULL) {
        perror("Unable to open output file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *word = calloc(MAX_WORD, sizeof(char)); // Buffer para armazenar cada palavra da consulta
    int errosMax;

    // Lê as consultas do arquivo uma por uma
    while (fscanf(file, "%99s %d", word, &errosMax) != EOF) {

        for (int i = 0; i < strlen(word); i++){
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

int main () {

    nodeTrie *tree; 
    tree = createNode();

    loadWords(tree, "entrada.txt");
    process(tree, "consultas.txt");

    deleteTrieTree (tree);


    return 0;
}
