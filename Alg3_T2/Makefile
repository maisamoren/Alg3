CFLAGS = -Wall -g -std=c99

all: mytrie

mytrie: trab2.o 
	gcc $(CFLAGS) trab2.o -o trab2 

trab2.o: trab2.c 
	gcc $(CFLAGS) -c trab2.c 

# trie.o: trie.c trie.h
# 	gcc $(CFLAGS) -c trie.c 

clean:
	rm -rf ./*.o
	 
purge: clean
	rm -rf mytrie

