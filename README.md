# Genome Assembly Using De-Bruijn Graphs

## Initial Implementation: The Overall Algorithm

1. Input the value of 'k'. Then, input the number of reads that the user shall provide to the program.
2. For each of the reads, generate k-mers. Do note that all the reads may not be of the same length. 
3. For each of the k-mers, generate left and right (k-1)-mers.

4. Build the De Bruijn graph (more on this below) using the (k-1)-mers.

5. Connect the last node of the De Bruijn graph with the first node.

6. Perform an Eulerian walk on the De Bruijn graph.

   a. While we visit the nodes during the Eulerian walk, take the whole string of the first node, and append the last letter of the consecutive nodes to it.
   
   b. Ignore the last edge (as the last edge connects the last node with the first node, due to step 5).

   c. For example, a walk like:

	_(ATF) -> (TFB) -> (FBI) -> (BII) -> (IIT) -> (ATF)_ (remember the last node IIT is connected to the first node ATF, because of step 5)

	would yield the complete string as: ATFBIIT (disregard the last edge, hence don't append 'F' from ATF again; or do it and then remove it, whichever is easier.)

7. Et voila! You've the original string. Just change those arbitrary letters in the reads to bases and you get a genome (that's upto the user)!


## Next Implementation

In the next version, we shall do all the above steps first by taking the value of k as that given by the user, then change the value of k to **(initial value of k) + 1**, then repeat the whole process again. We do it the third time, this time by changing the value of k to **(initial value of k) - 1**. This will give us 3 strings.

Show the string that occurs 2 times (or more) out of the three. If all the 3 strings are different, show them all.

**The steps are described in detail below:**

## Class Design

### Taking Input

This is quite a simple task: ask the user for the value of `k`, and the number of reads. Then, take in the reads.
After that, create a `KMerifier` object with that value of k and the reads, and let the workflow continue.

### Processing the Input

Following good design, there shall be a `class KMerifier` that takes a value `k`, and a `vector<string>` in its constructor.
An object of this class will help to generate the k-mers **and** (k-1)-mers, from the given `vector<string>`.

This class will also help to generate a set of **unique (k-1)-mers**.

The design of the class will be something like this:

```cpp
class KMerifier
{
private:
	int k;
	int k_minus_1;
	vector<string> reads;

public:
	KMerifier(int Kay, vector<string> Reads); // constructor
	
	unordered_map<int, string> getKMers(); // returns KMers of the reads, in order
	unordered_map<int, string> getKMinusOneMers(); // returns (K-1)-Mers of the reads in order
	
	// using unordered_map above instead of a vector has some benefits here

	unordered_set<string> getUniqueKMinusOneMers(); // returns unique (k-1)-mers

	int getK(); // returns value of k
	void setK(int kay); // sets the value of k
};
```
For a general idea of how this needs to be done, have a look at `src/reference.cpp`.


### Building the De Bruijn Graph

A De-Bruijn graph is a **directed multi-graph** (can have more than one edge between 2 nodes) that is always Eulerian (always has an Eulerian path).
We shall use an **Adjacency List** representation for the De-Bruijn graph. 

Remember that here, the nodes of the DeBruijn graph are `string`s.

A class DeBruijnGraph would be handy for this.

**A `DeBruijnGraph` object's nodes should be initialized by either of these methods:**
**1. Creating a KMerifier object and then passing it to a function `initNodesFromKMerifier`, which takes that object as an argument.**
**2. Creating a KMerifier object and then passing it to the constructor of the class `DeBruijnGraph`, so that it gets initialized at the time of creation.**

The adjacency list will be an unordered_map (for easy access of elements using []).

It (the adjacency list) can be hence represented like this:
{"a" : {"a0", "a1", "a2", ...},
"b" : {"b0", "b1", "b2", ...}, ...}

so that saying `adjList["b"][0]` would mean `"b0"`. This needs to be done because the nodes are strings.

__(Note: Please see the `#define` directive in the beginning.)__

```cpp
#define Node string
// The above line replaces each instance of the word Node with string, like find and replace
// Node in the lines after this is just string.

class DeBruijnGraph
{
private:
	unordered_map <Node, vector<Node>> adjList;
	unordered_map <int, Node> nodes; // associates a number to each Node
	unordered_map <Node, int> edgeCounts; // stores the number of edges each node has EMERGING from it
	
	void connectLastAndFirst(); // connects the last node with the first node
	void countEdges(); // counts the number of edges each node has EMERGING from it (populates edge_counts)

public:
	DeBruijnGraph(); // empty constructor
	DeBruijnGraph(KMerifier kmf); // constructor to directly initialize the graph with a KMerifier object

	void addEdge(Node node1, Node node2);
	void addNode(Node node);

	bool contains(Node node); // returns true if the string node is there in the graph

	void initNodesFromKMerifier(KMerifier kmf); // initializes the nodes from an object of the KMerifier class type. 
	// Use the addEdge and addNode functions from inside this function.

	void printAdjList(); // for debugging purposes

	string DoEulerianWalk(); // implementation of the Heirholzer's algorithm. This function returns the original string.

	// ... other functions may be added, for example, for debugging.
};
```

The Eulerian walk of the `DeBruijnGraph` will be performed by calling the `DoEulerianWalk()` function. This function returns us the complete string.
The algorithm used to do this is: [Hierholzer's Algorithm](https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/) (a linear time algorithm).


## Main Workflow Design

1. Take in `k` and the reads, then create a `KMerifier` object.
2. Create a `DeBruijnGraph` object and initialize its nodes using the `KMerifier` class object (created in step 1).
3. Use `DoEulerianWalk()` of the `DeBruijnGraph` object to get the complete string.
4. **Next Implementation**: Do the above three steps for different values of `k` (instead of asking the user for `k` again, use *k(initial) + 1* and *k(initial) - 1* as `k` values, as mentioned before).
   Show the string that occurs 2 times (or more) out of the three. If all the 3 strings are different, show them all.

