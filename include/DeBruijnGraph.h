// DeBruijnGraph.h
// Contains prototypes for the DeBruijnGraph class

// This file's contents should be included only once
// Hence the ifndef directives:

#ifndef DEBRUIJNGRAPH_H
#define DEBRUIJNGRAPH_H

#include "KMerifier.h"

#define Node string

// This is actually bad practice, but for simplicity
// and because we won't be using any other namespace for now


class DeBruijnGraph
{
private:
	unordered_map <Node, vector<Node>> adjList;
	unordered_map <Node, int> edgeCounts; // stores the number of edges each node has EMERGING from it
	
	void connectLastAndFirst(); // connects the last node with the first node
	void countEdges(); // counts the number of edges each node has EMERGING from it (populates edge_counts)

public:
	DeBruijnGraph(); // empty constructor
	DeBruijnGraph(KMerifier kmf); // constructor to directly initialize the graph with a KMerifier object

	void addEdge(Node nodeFrom, Node nodeTo);
	void addNode(Node node);

	bool contains(Node node); // returns true if the string node is there in the graph

	void initNodesFromKMerifier(KMerifier kmf); // initializes the nodes from an object of a KMerifier class type. 
	// Use the addEdge and addNode functions from inside this function.

	void printAdjList(); // for debugging purposes

	string DoEulerianWalk(); // implementation of the Heirholzer's algorithm. This function returns the original string.

	// ... other functions may be added, for example, for debugging.
};

#endif