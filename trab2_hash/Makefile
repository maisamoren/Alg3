CFLAGS = -Wall -g -std=c99

all: myht

myht: myht.o hash.o
	gcc $(CFLAGS) myht.o hash.o -o myht 

myht.o: myht.c hash.h 
	gcc $(CFLAGS) -c myht.c 

hash.o: hash.c hash.h
	gcc $(CFLAGS) -c hash.c 

clean:
	rm -rf ./*.o
	 
purge: clean
	rm -rf myht

