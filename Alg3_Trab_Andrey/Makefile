CFLAGS = -Wall -g -std=c99

all: dicionario

dicionario: trie.o dicionario.o
	gcc $(CFLAGS) trie.o dicionario.o -o dicionario -ltinfo

trie.o : trie.c trie.h
	gcc $(CFLAGS) -c trie.c -ltinfo

dicionario.o : dicionario.c dicionario.h
	gcc $(CFLAGS) -c dicionario.c -ltinfo

clean:
	rm -rf ./*.o
	 
purge: clean
	rm -rf dicionario