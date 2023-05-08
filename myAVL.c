#include "source/myAVL.h"


//createAVL is called only when there's no AVL available, so it returns a pointer to an new AVL;
node *createAVL(int key){

    node *n = malloc(sizeof(node));

    if (n != NULL){
        n->depth=0;
        n->key=key;
        n->L_son=NULL;
        n->R_son=NULL;
        n->father=NULL;
        return n;
    }
    return NULL;
}
//----------------------------------------------------------------
node *insert(node *n, int key){//inserts a new node in the AVL.

    if(n==NULL){
        return createAVL(key);
    }else{
        if(key < n->key){
            n->L_son = insert(n->L_son, key);
            n->L_son->father=n;
        }else if(key > n->key){
            n->R_son=insert(n->R_son, key);
            n->R_son->father=n;
        }else
            printf("erro\n");
    }
    n->depth = bigger(height(n->L_son), height(n->R_son))+1;
    n=balancer(n);
    return n;
}
//----------------------------------------------------------------
node *balancer(node *n){
    
    int bf = balanceFactor(n);

//left rotation
    if(bf < -1 && balanceFactor(n->R_son) <= 0){
        n=L_rotate(n);
    }
//right rotation
    if(bf > 1 && balanceFactor(n->L_son) >= 0){
        n=R_rotate(n);
    }
//left-right rotation
    if(bf > 1 && balanceFactor(n->L_son) < 0){
        n=LR_rotate(n);
    }
//right-left rotation
    if(bf < -1 && balanceFactor(n->R_son) > 0){
        n=RL_rotate(n);
    }

    return n;
}
//----------------------------------------------------------------
node *binarySearch(node *n, int key){
    if(n==NULL)
        return NULL;
    if(n->key==key)
        return n;
    if(key<n->key)
        return binarySearch(n->L_son, key);
    return binarySearch(n->R_son, key);
}
//----------------------------------------------------------------
void *fatherFix(node *n, node *new){
    if(n->father!=NULL){
        if(n->father->L_son==n)
            n->father->L_son = new;
        else
            n->father->R_son = new;
        if(new != NULL)
            new->father=n->father;
    }
}
//----------------------------------------------------------------
node *delete(node *n, node *target){

    node *aux, *Nroot = n;

    if(target->L_son==NULL){
        fatherFix(target, target->R_son);
        free(target);
    }else{
        if(target->R_son==NULL){
            fatherFix(target, target->L_son);
            free(target);
        }
        else{
            aux = successor(target);
            fatherFix(aux, aux->R_son);
            aux->L_son=target->L_son;
            aux->R_son=target->R_son;
            fatherFix(target, aux);
            if(target == n)
                Nroot = aux;
            free(target);
        }
    }
    Nroot->depth = bigger(height(Nroot->L_son), height(Nroot->R_son))+1;
    Nroot = balancer(Nroot);
    return Nroot; 
}
//----------------------------------------------------------------
node *L_rotate(node *n){

    node *aux = n->R_son;

    n->R_son = aux->L_son;
    aux->father = n->father;
    n->father=aux;

    if (aux->L_son != NULL)
        aux->L_son->father=n;
    aux->L_son = n;
    
    n->depth=bigger(height(n->L_son), height(n->R_son))+1;
    aux->depth=bigger(height(aux->L_son), height(aux->R_son))+1;

    return aux;
}
//----------------------------------------------------------------
node *R_rotate(node *n){

    node *aux = n->L_son;

    n->L_son = aux->R_son;
    aux->father = n->father;
    n->father=aux;

    if (aux->R_son != NULL)
        aux->R_son->father=n;
    aux->R_son = n;
    
    n->depth=bigger(height(n->R_son), height(n->L_son))+1;
    aux->depth=bigger(height(aux->R_son), height(aux->L_son))+1;

    return aux;
}
//----------------------------------------------------------------
node *RL_rotate(node *n){
    n->R_son = R_rotate(n->R_son);
    return L_rotate(n);
}
//----------------------------------------------------------------
node *LR_rotate(node *n){
    n->L_son = L_rotate(n->L_son);
    return R_rotate(n);
}
//----------------------------------------------------------------
int bigger(int x, int y){
    if (x>y)
        return x;
    return y;
}
//----------------------------------------------------------------
int height(node *n){

    if(n==NULL){
        return -1;
    }
    return n->depth;
}
//----------------------------------------------------------------
int balanceFactor(node *n){
    
    if(n){
        return (height(n->L_son)-height(n->R_son));
    }else
        return 0;
}
//----------------------------------------------------------------
node *minimum(node *n){

    if(n->L_son==NULL)
        return n;
    else
        return minimum(n->L_son);
}
//----------------------------------------------------------------
node *successor(node *n){
    if(n->L_son==NULL)
        return n;
    return successor(n->L_son);
}
//--------------------------------------------------------------
void in_order(node *n, int h){
    if (n != NULL)
    {
        in_order(n->L_son, h+1);
        printf("%d, %d \n", n->key, h);
        in_order(n->R_son, h+1);
    }
}
//----------------------------------------------------------------
void printAVL(node *n, int depth){

    int i;
    if(n){
        printAVL(n->R_son, depth+1);
        printf("\n\n");
        for(i=0; i<depth; i++)
            printf("\t");
        printf("%d",n->key);
        printAVL(n->L_son, depth+1);
    }
}
//----------------------------------------------------------------
void menu(){

    printf("###################################################\n");
    printf("#            MENU DE OPERACOES AVL TREE           #\n");
    printf("#           ESCOLHA UMA DAS OPCOES ABAXO:         #\n");
    printf("#                                                 #\n");
    printf("#               i - INSERIR UM VALOR              #\n");
    printf("#               r - REMOVER UM VALOR              #\n");
    printf("#               p -  IMPRIMIR A AVL               #\n");
    printf("#               t - TRAVESSIA EM ORDEM            #\n");
    printf("#               s -      SAIR                     #\n");
    printf("#                                                 #\n");
    printf("###################################################\n");

    return;
}