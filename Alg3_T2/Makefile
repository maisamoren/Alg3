CFLAGS = -Wall -g -std=c99

all: busca

busca: busca.o avl-tree.o
	gcc $(CFLAGS) busca.o avl-tree.o -o busca 

busca.o: busca.c avl-tree.h 
	gcc $(CFLAGS) -c busca.c 

avl-tree.o: avl-tree.c avl-tree.h
	gcc $(CFLAGS) -c avl-tree.c 

clean:
	rm -rf ./*.o
	 
purge: clean
	rm -rf busca

