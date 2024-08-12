#ifndef __TRIE__
#define __TRIE__

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

nodeTrie *createNode ();

int searchTrie (nodeTrie *root, char *key);

void insertTrie (nodeTrie *root, char *key);

bool empty (nodeTrie *root);

nodeTrie *deleteTrieNode (nodeTrie *root, char *key, int depth);

void deleteTrieTree (nodeTrie *root);

#endif