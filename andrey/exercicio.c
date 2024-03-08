#include <stdio.h>
#include <stlib.h>

typedef struct node {
    char key;
    node *left, *right;
} node;

node *createNode(char key, node *left, node *right){
    node *n = malloc (sizeof(node));
    n->key = key;
    n->left = left;
    n->right = right;
    return n;
}

void inOrder(node *n){
    if (!n)
        return;
    inOrder(n->left);
    printf("%c ", n->key);
    inOrder(n->right);
}

void preOrder(node *n){
    if (!n)
        return;
    printf("%c ", n->key);
    preOrder(n->left);
    preOrder(n->right);
}

void postOrder(node *n){
    if (!n)
        return;
    postOrder(n->left);
    postOrder(n->right);
    printf("%c ", n->key);
}

void expression(node *n){
    if (!n)
        return;
    
    expression(n->left);

    if (n->key == '3'){
        
    }

}

int main () {
    node *root = createNode('/',createNode('-',createNode('*',createNode('5',NULL,
                 NULL),createNode('6',NULL,NULL)),createNode('+',createNode('5',NULL,
                 NULL),createNode('1',NULL,NULL))),createNode('*',createNode('3',NULL,
                 NULL),createNode('4',NULL,NULL)));

    inOrder(root);
    printf("\n");
    preOrder(root);
    printf("\n");
    postOrder(root);

    expression(root);
}