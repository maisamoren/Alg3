//myht.c

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(){
    char op;
    int k;
    struct cuckoo hash;
    
    inicia(&hash);

    while (scanf("%c %d", &op, &k) != EOF){
        if (op == 'i'){
            insere(&hash, k);
        } 
        else if (op == 'r'){
            exclui(&hash, k);
        }
    }
    imprime(&hash);

    return 0;
}