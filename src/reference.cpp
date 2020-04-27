#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define Node string

using namespace std;

int main()
{
    unordered_map<int, string> reads;   

    unordered_map<int, string> kmers;
    unordered_map<int, string> k_1_mers;
    unordered_set<string> k_1_mers_nodup;

    unordered_map<int, string> k_1_nodes;

    cout << "\nEnter K: ";
    int K;
    cin >> K;
    
    cout << "\nEnter number of reads: ";
    int count;
    cin >> count;

    int ind = 0;
    for (int i = 0; i < count; i++)
    {
        string read;
        cin >> read;

        // k-merify
        for (int j = 0; j < (read.length() - K + 1); j++)
        {
            kmers[ind] = read.substr(j, K);
            ind++;
        }
    }

    // DEBUG: Show kmers
   cout << "\n" << K << "-mers: " << endl;

   for (int i = 0; i < kmers.size(); i++)
   {
       cout << kmers[i] << endl;
   }

    
    for (int i = 0; i < kmers.size(); i++)
    {
        // for ith kmer, its left k-1-mer is at 2*i and right k-1-mer is at 2*i + 1 index
        // of k_1_mers
        string km = kmers[i];
        
        k_1_mers[i*2] = km.substr(0, K-1);
        k_1_mers[i*2 + 1] = km.substr(1, K-1);

        // add these both to the set of nodes

        k_1_mers_nodup.insert(k_1_mers[i*2]);
        k_1_mers_nodup.insert(k_1_mers[i*2 + 1]);
    }

    // DEBUG: Show k-1-mers
   cout << "\n" << K-1 << "-mers: " << endl;

   for (int i = 0; i < k_1_mers.size(); i++)
   {
       cout << k_1_mers[i] << endl;
   }

   cout << "\n" << K-1 << "-mers (unique): " << endl;

   for (unordered_set<string>::iterator it = k_1_mers_nodup.begin(); it != k_1_mers_nodup.end(); it++)
   {
       cout << *it << endl;
   }

    unordered_map <Node, vector<Node>> adjList;
    unordered_map <int, Node> nodes; // associates a number to each Node
	
    unordered_map <Node, int> edgeCounts;

    // Initialize the Graph

    int nodesInserted = 0;

    for (int i = 0; i < k_1_mers.size(); i++)
    {
        if (adjList.find(k_1_mers[i]) != adjList.end())
        // if adjList does not contain that k_1_mer
        {
            // add that k-1-mer to the graph
            vector<Node> internalList; // initialize an empty vector
            adjList[k_1_mers[i]] = internalList;

            nodesInserted++;
            nodes[nodesInserted] = k_1_mers[i];

            if (nodesInserted > 0)
            {
                Node prevNodeInserted = nodes[nodesInserted - 1];
                Node currNodeInserted = nodes[nodesInserted];
                
                // connect the previous node with the current node
                // by adding a directed edge between them
                adjList[prevNodeInserted].push_back(currNodeInserted);
            }
        }
    }


    Node lastNode = nodes[nodes.size() - 1];
    Node firstNode = nodes[0];

    adjList[lastNode].push_back(firstNode);

    for (int i = 0; i < nodes.size(); i++)
    {
        Node node = nodes[i];
        edgeCounts[node] = adjList[node].size();
    }
}