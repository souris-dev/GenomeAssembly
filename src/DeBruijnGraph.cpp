// DeBruijnGraph.cpp
// Contains the implementation of the DeBruijnGraph class

#include "../include/DeBruijnGraph.h"
#include <stack>
#include <algorithm>

// Implementation of the DeBruijnGraph class

void DeBruijnGraph::connectLastAndFirst()
{
    // connects the last node with the first node
}

void DeBruijnGraph::countEdges()
{
    // counts the number of edges each node has EMERGING from it (populates edge_counts)
}

DeBruijnGraph::DeBruijnGraph(KMerifier kmf) // constructor
{
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

    // Things to do here:
    // 1. Take the appropriate k-1-mers fromm kmf
    // 2. Add them as nodes to the graph using addNode
    // 3. Add appropriate edges between them using addEdge
    // 4. Add these nodes in their order of addition into 'nodes'
    // Like the first added node goes into: nodes[0], the second one nodes[1]
    // and so on.
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
    // implementation of the Heirholzer's algorithm. 
    // This function returns the original string.
    string original = "";

    connectLastAndFirst(); // needed in order for Hierholzer's Algo to work

    unordered_map <Node, vector<Node>> adjListTemp = this->adjList;

    countEdges();
    unordered_map <Node, int> edgeCountsTemp = this->edgeCounts;

    if (adjListTemp.size() == 0)
    {
        original = "";
        return original;
    }

    stack<Node> currPath; // for backtracking purposes
    
    // to store the final circuit:
    vector<Node> circuit;

    // The following stores the Eulerian circuit in 'circuit' in the reverse order

    currPath.push(nodes[0]);
    Node currNode = nodes[0]; // we shall start from the first node

    while (!currPath.empty())
    {
        // check if current node has edges we can traverse
        if (edgeCountsTemp[currNode] != 0)
        {
            currPath.push(currNode);

            Node nextNode = adjListTemp[currNode].back();

            edgeCountsTemp[currNode]--;
            
            adjListTemp[currNode].pop_back();

            // get to the next node
            currNode = nextNode;
        }

        // otherwise, if this node has no more remaining edges,
        // add to final circuit and backtrack
        else
        {
            circuit.push_back(currNode);

            // this lets us backtrack
            currNode = currPath.top();
            currPath.pop();
        }
    }

    // The reversed circuit is stored in 'circuit'
    // Now we need to reverse it to get the actual circuit
    
    reverse(circuit.begin(), circuit.end());

    original = circuit[0];

    for (int i = 0; i < (circuit.size() - 1); i++)
    // we need to ignore the last node of the circuit, 
    // so i goes from 0 to circuit.size() - 2
    {
        // append the last character
        original += circuit[i].substr((kmf.getK() - 1) - 1, 1);
    }

    return original;
}