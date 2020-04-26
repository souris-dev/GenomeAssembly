# Experimental: Makefile is not yet tested
CFLAGS = --std=c++14 -O 
CC = g++

GenomeAssembler: main.o DeBruijnGraph.o KMerifier.o
		$(CC) $(CFLAGS) -o build/GenomeAssembler build/main.o build/DeBruijnGraph.o build/KMerifier.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o build/main.o

DeBruijnGraph.o: DeBruijnGraph.cpp
	$(CC) $(CFLAGS) -c DeBruijnGraph.cpp -o build/DeBruijnGraph.o

KMerifier.o: KMerifier.cpp
	$(CC) $(CFLAGS) -c KMerifier.cpp -o build/KMerifier.o

clean:
	rm -f core ./build/*.o
