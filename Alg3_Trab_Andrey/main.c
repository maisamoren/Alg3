#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "trie.h"
#include "dicionario.h"

int main () {

    nodeTrie *tree; 
    tree = createNode();

    loadWords(tree, "entrada.txt");
    process(tree, "consultas.txt");

    deleteTrieTree (tree);


    return 0;
}
