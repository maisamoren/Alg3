#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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