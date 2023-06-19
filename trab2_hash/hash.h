//.H

#define TAM 11

// struct de no' so' com a chave
struct no{
    int k;
};

// struct das duas tabelas hash
struct cuckoo{
    struct no tabela1[TAM];
    struct no tabela2[TAM];
}

// funcoes do calculo das tabelas
unsigned int t1(int k);

unsigned int t2(int k);

int busca(struct cuckoo *hash, int k);

void insere(struct cuckoo *hash, int k);

void exclui(struct cuckoo *hash, int k);

void inicia(struct cuckoo *hash);

void imprime(struct cuckoo *hash);