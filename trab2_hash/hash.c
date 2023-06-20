// .C

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define TAM 11

unsigned int t1 (int k){
    return k % TAM;
}

unsigned int t2 (int k){
    return (int)TAM * ((float)k * 0.9 - (int)(k * 0.9));
}

int busca (struct cuckoo *hash, int k){
    unsigned int h1 = t1(k);
    unsigned int h2 = t2(k);

    if (hash->tabela1[h1].k == k){
        return hash->tabela1[h1].k;
    }
    else if (hash->tabela2[h2].k == k){
        return hash->tabela2[h2].k;
    } else {
        return 0;
    }
}

void insere(struct cuckoo *hash, int k){
    unsigned int h1 = t1(k);
    unsigned int h2 = t2(hash->tabela1[h1].k);

    if (hash->tabela1[h1].k == -1){
        hash->tabela1[h1].k = k;
    } else {
        if (!busca(hash, k)){
            if (hash->tabela2[h2].k == -1){
                hash->tabela2[h2].k = hash->tabela1[h1].k;
                hash->tabela1[h1].k = k;
            } 
            /* nesse caso n tem else e sera explicado no relatorio (arquivo .txt LEIAME) */
        }
    }
}

void exclui(struct cuckoo *hash, int k){
    unsigned int h1 = t1(k);
    unsigned int h2 = t2(k);

    if (hash->tabela1[h1].k == k){
        hash->tabela1[h1].k = -1;
    }
    else if (hash->tabela2[h2].k == k){
        hash->tabela2[h2].k = -1;
    } else {
        printf("Chave nao encontrada\n");
    }
}

void inicia(struct cuckoo *hash){
    for (int i=0; i<TAM; i++){
        hash->tabela1[i].k = -1;
        hash->tabela2[i].k = -1;
    }
}

void imprime(struct cuckoo *hash){
    for (int i=0; i<TAM; i++){
        if (hash->tabela1[i].k != -1){
            printf("%d,T1,%d\n", hash->tabela1[i].k, i);
        }
        if (hash->tabela2[i].k != -1){
            printf("%d,T2,%d\n", hash->tabela2[i].k, i);
        }
    }
}