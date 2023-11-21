#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Estrutura do nó da árvore digital
typedef struct TrieNode {
    struct TrieNode *children[26]; // Para letras do alfabeto inglês
    char *fileList; // Lista de arquivos onde a palavra ocorre
} TrieNode;

// Função para inicializar um novo nó da árvore
TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node) {
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        node->fileList = NULL;
    }
    return node;
}

// Função para inserir uma palavra na árvore
void insertWord(TrieNode *root, const char *word, const char *file) {
    TrieNode *current = root;
    for (int i = 0; i < strlen(word); i++) {
        char c = tolower(word[i]);
        if (!isalpha(c)) {
            continue; // Ignora caracteres não alfabéticos
        }
        int index = c - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    // Adiciona o arquivo à lista associada à palavra
    if (!current->fileList) {
        current->fileList = strdup(file);
    } else {
        char *temp = (char *)malloc(strlen(current->fileList) + strlen(file) + 2);
        sprintf(temp, "%s %s", current->fileList, file);
        free(current->fileList);
        current->fileList = temp;
    }
}

// Função para procurar palavras com um determinado prefixo na árvore
void searchPrefix(TrieNode *root, const char *prefix) {
    TrieNode *current = root;
    for (int i = 0; i < strlen(prefix); i++) {
        char c = tolower(prefix[i]);
        int index = c - 'a';
        if (!current->children[index]) {
            return; // Prefixo não encontrado
        }
        current = current->children[index];
    }

    // Imprime a lista de arquivos associados à palavra com o prefixo
    if (current->fileList) {
        printf("%s %s\n", prefix, current->fileList);
    }
}

// Função para liberar a memória alocada para a árvore
void freeTrie(TrieNode *node) {
    if (node) {
        for (int i = 0; i < 26; i++) {
            freeTrie(node->children[i]);
        }
        free(node->fileList);
        free(node);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_base> <arquivo_texto>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *baseFile = fopen(argv[1], "a+"); // Abre o arquivo da base em modo de leitura e escrita
    if (!baseFile) {
        fprintf(stderr, "Erro ao abrir o arquivo da base\n");
        return EXIT_FAILURE;
    }

    TrieNode *root = createNode(); // Cria a raiz da árvore

    // Leitura do arquivo da base e construção da árvore
    char word[MAX_WORD_LENGTH];
    while (fscanf(baseFile, "%s", word) == 1) {
        char file[MAX_WORD_LENGTH];
        fscanf(baseFile, "%s", file);
        insertWord(root, word, file);
    }

    // Leitura do arquivo de texto e inserção na base
    FILE *textFile = fopen(argv[2], "r");
    if (textFile) {
        while (fscanf(textFile, "%s", word) == 1) {
            insertWord(root, word, argv[2]);
        }
        fclose(textFile);
    }

    // Escrita da árvore modificada de volta para o arquivo da base
    freopen(argv[1], "w", baseFile);
    fclose(baseFile);

    // Busca por palavras com um determinado prefixo
    searchPrefix(root, "pre"); // Substitua "pre" pelo prefixo desejado

    // Libera a memória alocada para a árvore
    freeTrie(root);

    return EXIT_SUCCESS;
}
