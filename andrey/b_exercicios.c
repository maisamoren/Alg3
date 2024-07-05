#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define tB 3

typedef struct nodeB {
    int totalKeys;
    char keys[2*tB - 1];
    struct nodeB *child[2*tB];
    bool leaf;
} nodeB;

nodeB *createNodeB () {
    nodeB *x = (nodeB*)malloc(sizeof(nodeB));
    if (x != NULL){
        x->leaf = true;
        x->totalKeys = 0;
    }
    return x;
}

void splitChild (nodeB *x, int i){
    nodeB *y = x->child[i];
    nodeB *z = createNodeB();
    z->leaf = y->leaf;
    z->totalKeys = tB - 1;

    for (int j = 0; j < tB - 1; j++){
        z->keys[j] = y->keys[j+tB];
        printf("for 1\n ");
    }

    if (!y->leaf){
        for (int j = 0; j < tB; j++){
            z->child[j] = y->child[j+tB];
            printf("for 2\n ");
        }
    }

    y->totalKeys = tB-1;
    
    for (int j = x->totalKeys+1; j >= i+1; j--){
        x->child[j+1] = x->child[j];
        printf("for 3\n ");
    }

    x->child[i+1] = z;
    
    for (int j = x->totalKeys; j >= i; j--){
        x->keys[j+1] = x->keys[j];
        printf("for 4\n ");
    }

    x->keys[i] = y->keys[tB-1];
    x->totalKeys++;
}

void insertNonFull (nodeB *x, char l){
    int i = x->totalKeys;
    if (x->leaf){
        while (i >= 1 && l < x->keys[i]){
            x->keys[i+1] = x->keys[i];
            i--;
        }

        x->keys[i+1] = l;
        x->totalKeys = x->totalKeys + 1;
    }
    else {
        while (i >= 1 && l < x->keys[i]){
            i--;
        }
        i++;

        if (x->child[i]->totalKeys == 2*tB-1){
            splitChild(x, i);
            if (l > x->keys[i]){
                i++;
            }
        }
        insertNonFull(x->child[i], l);
    }
}

void insert (nodeB *x, char l){
    nodeB *r = x;
    if (r->totalKeys == 2*tB-1){
        nodeB *s = createNodeB();
        x = s;
        s->leaf = false;
        s->child[0] = r;
        splitChild(s, 0);
        insertNonFull(s, l);
    }
    else {
        insertNonFull(r, l);
    }
}

// void imprime (nodeB *root){

// }

void delete (nodeB * root, char l){
    int i = 1;
    
    while (i < x->totalKeys && x->keys[i]){
        i++;
    }

    if (i < x->totalKeys && k == x->keys[i]){
        if (x->leaf){
            removeFromLeaf(x, l);
            return;
        }
        else{
            if (x->child[i]->totalKeys >= t){
                node *p
            }
        }
    }
}

int main (){

    nodeB *root = createNodeB();

    char letter;
    printf("Digite um char para ser inserido na árvore B: ");
    scanf("%c ", &letter);

    insert(root, letter);

    // imprime(root);

    char l;
    printf("Digite um char para ser deletado na árvore B: ");
    scanf("%c ", &l);
    delete(root, l);

    return 0;
}