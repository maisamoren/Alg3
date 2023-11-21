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
        insere(root, word, file);
    }

    // Leitura do arquivo de texto e inserção na base
    FILE *textFile = fopen(argv[2], "r");
    if (textFile) {
        while (fscanf(textFile, "%s", word) == 1) {
            insere(root, word, argv[2]);
        }
        fclose(textFile);
    }

    // Escrita da árvore modificada de volta para o arquivo da base
    freopen(argv[1], "w", baseFile);
    fclose(baseFile);

    // Busca por palavras com um determinado prefixo
    procura(root, "pre"); // Substitua "pre" pelo prefixo desejado

    // Libera a memória alocada para a árvore
    freeTrie(root);

    return 0;
}
