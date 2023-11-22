#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Estrutura do nó da árvore digital
typedef struct TrieNode {
    struct TrieNode *filhos[26]; // Para letras do alfabeto 
    char *lista; // Lista de arquivos onde a palavra ocorre
} TrieNode;

// Função para inicializar um novo nó da árvore
TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node) {
        for (int i = 0; i < 26; i++) {
            node->filhos[i] = NULL;
        }
        node->lista = NULL;
    }
    return node;
}

// Função para inserir uma palavra na árvore
void insere(TrieNode *root, const char *word, const char *file) {
    TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        char c = tolower(word[i]);
        if (!isalpha(c)) {
            continue; // Ignora caracteres não alfabéticos
        }
        int index = c - 'a';
        if (!current->filhos[index]) {
            current->filhos[index] = createNode();
        }
        current = current->filhos[index];
    }

    // Adiciona o arquivo à lista associada à palavra
    if (!current->lista) {
        current->lista = strdup(file);
    } else {
        char *temp = (char *)malloc(strlen(current->lista) + strlen(file) + 2);
        sprintf(temp, "%s %s", current->lista, file);
        free(current->lista);
        current->lista = temp;
    }
}

// Função para procurar palavras com um determinado prefixo na árvore
void procura(TrieNode *root, const char *prefix) {
    TrieNode *current = root;
    for (int i = 0; i < strlen(prefix); i++) {
        char c = tolower(prefix[i]);
        int index = c - 'a';
        if (!current->filhos[index]) {
            return; // Prefixo não encontrado
        }
        current = current->filhos[index];
    }

    // Imprime a lista de arquivos associados à palavra com o prefixo
    if (current->lista) {
        printf("%s %s\n", prefix, current->lista);
    }
}

// Função para liberar a memória alocada para a árvore
void freeTrie(TrieNode *node) {
    if (node) {
        for (int i = 0; i < 26; i++) {
            freeTrie(node->filhos[i]);
        }
        free(node->lista);
        free(node);
    }
}

int main(int argc, char *argv[]) {

    // printf ("entrou aqui\n");

    FILE *baseFile = fopen("ENEIDA.ini", "r"); 

    // printf ("entrou aqui\n");

    if (!baseFile) {
        fprintf(stderr, "Erro ao abrir o arquivo da base\n");
        return 1;
    }

    TrieNode *root = createNode(); 

    char word[MAX_WORD_LENGTH];

    while (fscanf(baseFile, "%s", word) == 1) {
        char file[MAX_WORD_LENGTH];
        // printf ("entrou aqui");
        fscanf(baseFile, "%s", file);
        insere(root, word, file);
    }

    FILE *textFile = fopen("saida.txt", "r");

    if (textFile) {
        while (fscanf(textFile, "%s", word) == 1) {
            insere(root, word, argv[2]);
        }
        fclose(textFile);
    }

    freopen(argv[1], "w", baseFile);
    fclose(baseFile);

    procura(root, "pre");

    freeTrie(root);

    return 0;
}
