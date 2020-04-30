// DeBruijnGraph.cpp
// Contains the implementation of the DeBruijnGraph class

#include "../include/DeBruijnGraph.h"
#include <stack>
#include <algorithm>

// Implementation of the DeBruijnGraph class

void DeBruijnGraph::connectLastAndFirst()
{
    // connects the last node with the first node
    Node lastNode = nodes[nodes.size() - 1];
    Node firstNode = nodes[0];

    addEdge(lastNode, firstNode);
}


void DeBruijnGraph::countEdges()
{
    // counts the number of edges each node has EMERGING from it (populates edge_counts)
    for (int i = 0; i < nodes.size(); i++)
    {
        Node node = nodes[i];
        edgeCounts[node] = adjList[node].size();
    }
}


DeBruijnGraph::DeBruijnGraph(KMerifier kmf) // constructor
{
    initNodesFromKMerifier(kmf);
}


void DeBruijnGraph::addEdge(Node nodeFrom, Node nodeTo)
{
    // add an edge from nodeFrom to nodeTo
    adjList[nodeFrom].push_back(nodeTo);
}


void DeBruijnGraph::addNode(Node node)
{
    // add the node 'node' to the graph

    vector<Node> internalList; // initialize an empty vector
    adjList[node] = internalList;
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

    int nodesInserted = 0;
    unordered_map<int, string> k_1_mers = kmf.getKMinusOneMers();

    for (int i = 0; i < k_1_mers.size(); i++)
    {
        if (!contains(k_1_mers[i]))
        // if adjList does not contain that k_1_mer
        {
            // add that k-1-mer to the graph
            addNode(k_1_mers[i]);

            nodes[nodesInserted] = k_1_mers[i];
            nodesInserted++;

            if (nodesInserted > 1)
            {
                Node prevNodeInserted = nodes[(nodesInserted - 1) - 1]; 
                // nodesInserted is one-based, so have to subtract one
                Node currNodeInserted = nodes[nodesInserted - 1];

                // connect the previous node with the current node
                // by adding a directed edge between them
                addEdge(prevNodeInserted, currNodeInserted);
            }
        }
    }
}


bool DeBruijnGraph::contains(Node node)
{
    // returns true if the string node is there in the graph
    if (adjList.find(node) != adjList.end())
        return true;
    else
        return false;
}


void DeBruijnGraph::printAdjList()
{
    // for debugging purposes
    
    for (int i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i] << ": ";
        for (int j = 0; j < adjList[nodes[i]].size(); j++)
        {
            cout << adjList[nodes[i]][j] << " ";
        }
        cout << endl;
    }
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

    // --- Restoration of the original string ---

    original = circuit[0];

    // first node is already added to original,
    // and we need to ignore the last node of the circuit,
    // so i goes from i = 0 to i = circuit.size() - 2

    int k = kmf.getK();

    for (int i = 1; i < (circuit.size() - 1); i++)
    {
        // if there is an overlap between the previous and this node
        // so that left k-2-mer of this node is same as right k-2-mer of previous node,
        // for eg: AGG and GGB have GG in common
        // then append the last character only, of the current node

        // the nodes should atleast have 2 characters to check for overlaps though
    
        // apparently substr was not working properly so had to use this jugaad
        string right_prev = string(circuit[i - 1].begin() + 1, circuit[i - 1].end());
        string left_curr = string(circuit[i].begin(), circuit[i].end() - 1);

        if ((k - 1 > 1) && (right_prev == left_curr))
        {
            string curr = circuit[i];
            original += curr[curr.size() - 1]; // add the last characteter only
        }

        // otherwise, append this node as it is
        else
        {
            original += circuit[i];    
        }
        
    }

    return original;
}
