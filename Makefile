CFLAGS = -O
CC = g++

GenomeAssembler: main.o DeBruijnGraph.o KMerifier.o
		$(CC) $(CFLAGS) -o GenomeAssembler main.o DeBruijnGraph.o KMerifier.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

DeBruijnGraph.o: DeBruijnGraph.cpp
	$(CC) $(CFLAGS) -c DeBruijnGraph.cpp

KMerifier.o: KMerifier.cpp
	$(CC) $(CFLAGS) -c KMerifier.cpp

clean:
	rm -f core *.o
