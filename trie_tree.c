#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 26 

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
            return false; // palavra n existe na trie
        }

        // move o ponteiro aux para o nó já existente para o chat atual
        aux = aux->childNode[c-'a'];
    }
    return (aux->wordEnd);
}

// Insere uma palavra na trie
void insertTrie (nodeTrie *root, char *key) {

    nodeTrie *current = root;
    
    for (int i = 0; key[i] != '\0'; i++) {
        char c = key[i];
        if (current->childNode[c-'a'] == NULL) {
            nodeTrie *new = createNode();
            new->root = current;
            current->childNode[c-'a'] = new;
        }
        current = current->childNode[c-'a'];
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

// Retorna a diferenca de tamanho das palavras
int diferencaTamanhoPalavras (nodeTrie *nodo, char *key, int totalLetras) {
    
    int tamanhoNodo;
    nodeTrie *auxiliar;

    tamanhoNodo = 1;
    auxiliar = nodo;

    // Calcula o tamanho da palavra encontrada na trie
    while (auxiliar->root != NULL) {
        tamanhoNodo++;
        auxiliar = auxiliar->root;
    }

    // tamanhoKey = strlen(key);
    // retorna a subtracao de ambos valores encontrados
    return (tamanhoNodo - totalLetras);
}

// Descobre o caracter do nodo atual
char caracterAtual (nodeTrie *nodo) {

    nodeTrie *aux = nodo->root;

    for (int i = 0; i < MAX; i++){
        if (aux->childNode[i] == nodo)
            return i + 'a';
    }
    
       
}

// Imprime palavras encontradas
void imprimePalavraAchada (nodeTrie *nodo, int errosAtual) {
    
    int tamanhoNodo, preencheNodo;
    nodeTrie *auxiliar;
    char *vetorAuxiliar;

    tamanhoNodo = 1;
    auxiliar = nodo;
    
    // Calcula o tamanho da palavra encontrada na trie
    while (auxiliar->root != NULL) {
        tamanhoNodo++;
        auxiliar = auxiliar->root;
    }

    // Aloca memória para o vetor auxiliar com tamanho encontrado anteriormente
    vetorAuxiliar = malloc (sizeof (vetorAuxiliar * char));

    auxiliar = nodo;
    preencheNodo = tamanhoNodo - 1;

    // Preenche o vetor auxiliar com as letras da palavra encontrada
    while (preencheNodo <= 0) {
        vetorAuxiliar[preencheNodo] = caracterAtual(auxiliar);
        preencheNodo--;
        auxiliar = auxiliar->root;
    }

    // Imprime a palavra encontrada
    for (int i = 0; i < tamanhoNodo; i++){
        printf ("%c", vetorAuxiliar[i]);
    }

    // Imprime os erros totais 
    printf (", %d\n", errosAtual);

    // Desaloca vetor utilizado
    free (vetorAuxiliar);

    return;
}

// Verifica se as letras sao iguais
int verificaIgualdadeLetra (char key1, char key2){
    if (key1 == key2)
        return 1;
    return 0;
}

int palavrasSemelhantes (nodeTrie *nodo, char *key, int letraAtual, int totalLetras, int errosMax, int errosAtual){

    // Contador para saber quantas palavras semelhantes foram encontradas
    int contagem = 0;

    // If de seguranca para garantir que nao entre em locais da memoria indevidos (seja um nodo nulo ou um fim de vetor que nao existe)
    if ((nodo == NULL) || (letraAtual > totalLetras)) {
        return 0;
    }

    // Verifica se a letra atual da palavra eh igual a letra da arvore
    if (verificaIgualdadeLetra(key[letraAtual], caracterAtual(nodo)) != 1)
           errosAtual++;

    // Caso o numero de erros atuais seja maior que o maximo permitido, retorna impedindo busca desnecessarias
    if (errosAtual <= errosMax){

        // Caso seja o fim de alguma palavra, verifica se enquadra dentro do erro permitido
        if (nodo->wordEnd == 1){
            int errosAgora = errosAtual + diferencaTamanhoPalavras(nodo, key, totalLetras);
            if (errosAgora <= errosMax){
                contagem++;
                imprimePalavraAchada(nodo, errosAgora);
            }
        }

        // Chamadas de recursividade para achar palavras semelhantes buscando por todas possibilidades
        else{
            for (int i = 0; i < MAX; i++) {
                if (nodo->childNode[i] != NULL) {
                    // Chamada para proxima letra da trie apenas
                    contagem = contagem + palavrasSemelhantes(nodo->childNode[i], key, letraAtual, totalLetras, errosMax, errosAtual);
                    // Chamada para proxima letra da trie e do vetor
                    contagem = contagem + palavrasSemelhantes(nodo->childNode[i], key, letraAtual + 1, totalLetras, errosMax, errosAtual);
                }
            }
            // Chamada para proxima letra do vetor apenas
            contagem = contagem + palavrasSemelhantes(nodo, key, letraAtual + 1, totalLetras, errosMax, errosAtual);
        }
    }

    return contagem;
}

int main () {

    // printf("\n\n BEM VINDO\n\n");

    //nodeTrie *Tree; 
    //Tree = createNode();

    printf("%c\n", 3 + 'a');
    
    return 0;
}
