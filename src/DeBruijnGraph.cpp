// DeBruijnGraph.cpp
// Contains the implementation of the DeBruijnGraph class

#include "../include/DeBruijnGraph.h"
#include <stack>

// Implementation of the DeBruijnGraph class

void DeBruijnGraph::connectLastAndFirst()
{
    // connects the last node with the first node
}

void DeBruijnGraph::countEdges()
{
    // counts the number of edges each node has EMERGING from it (populates edge_counts)
}

DeBruijnGraph::DeBruijnGraph() // constructor
{
    // do nothing for now, really
}

DeBruijnGraph::DeBruijnGraph(KMerifier kmf) // constructor
{
    // create the object and initialize nodes
    initNodesFromKMerifier(kmf);
}

void DeBruijnGraph::addEdge(Node nodeFrom, Node nodeTo)
{
    // add an edge from nodeFrom to nodeTo
}

void DeBruijnGraph::addNode(Node node)
{
    // add the node 'node' to the graph
}

void DeBruijnGraph::initNodesFromKMerifier(KMerifier kmf)
{
    // initialize adjList from the KMerifier object kmf
}

bool DeBruijnGraph::contains(Node node)
{
    // returns true if the string node is there in the graph
}

void DeBruijnGraph::printAdjList()
{
    // for debugging purposes
}

string DeBruijnGraph::DoEulerianWalk()
{
    // implementation of the Heirholzer's algorithm. This function returns the original string.
}