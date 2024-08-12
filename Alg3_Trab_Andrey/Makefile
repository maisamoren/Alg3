CFLAGS = -Wall -g -std=c99
CC = gcc

all: main.o dicionario.o trie.o
	$(CC) -o dicionario main.o dicionario.o trie.o

dicionario.o: dicionario.c
	$(CC) -c $(CFLAGS) dicionario.c

trie.o: trie.c
	$(CC) -c $(CFLAGS) trie.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c
clean:
	rm -rf ./*.o
	 
purge: clean
	rm -rf dicionario
