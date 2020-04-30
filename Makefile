# Experimental: Makefile is not yet tested
CFLAGS = --std=c++14 -O 
CC = g++

GenomeAssembler: main.o DeBruijnGraph.o KMerifier.o
		$(CC) $(CFLAGS) -o build/GA.exe build/main.o build/DeBruijnGraph.o build/KMerifier.o

main.o:
	$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o

DeBruijnGraph.o:
	$(CC) $(CFLAGS) -c src/DeBruijnGraph.cpp -o build/DeBruijnGraph.o

KMerifier.o:
	$(CC) $(CFLAGS) -c src/KMerifier.cpp -o build/KMerifier.o

clean:
	rm -f core ./build/*.o
