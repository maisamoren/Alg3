#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 26

typedef struct nodeTrie {
    int wordEnd;
    struct nodeTrie *childNode[MAX];
} nodeTrie;

nodeTrie *createNode () {
    nodeTrie *new = (nodeTrie*)malloc(sizeof(nodeTrie));
    new->wordEnd = 0;
    for (int i = 0; i < MAX; i++){
        new->childNode[i] = NULL;
    }
    return new;
}

nodeTrie *searchTrie (nodeTrie *root, char *key) {
    nodeTrie *aux = root;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = key[i];

        // verifica se o nó existe para o char atual na árvore
        if (aux->childNode[c-'a'] == NULL) {
            return false; // palavra n existe na trie
        }

        // move o ponteiro aux para o nó já existente para o chat atual
        aux = aux->childNode[c-'a'];
    }
    return (aux->wordEnd);
}

void inseertTrie (nodeTrie *root, char *key) {
    nodeTrie *current = root;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = key[i];
        if (current->childNode[c-'a'] == NULL) {
            nodeTrie *new = createNode();
            current->childNode[c-'a'] = new;
        }
        current = current->childNode[c-'a'];
    }
    current->wordEnd = 1;
}

bool empty (nodeTrie *root) {
    for (int i = 0; i < MAX; i++) {
        if (root->childNode[i] != NULL) {
            return false;
        }
    }
    return true;
}

nodeTrie *deleteTrie (nodeTrie *root, char *key, int depth) {
    if (!root) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->wordEnd) {
            root->wordEnd = 0;
        }
        if (empty(root)) {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = key[depth] - 'a';
    root->childNode[index] = deleteTrie(root->childNode[index], key, depth+1);

    if (empty(root) && root->wordEnd == 0) {
        free(root);
        root = NULL;
    }

    return root;
}