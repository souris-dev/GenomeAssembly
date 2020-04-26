# Genome Assembly Using De-Bruijn Graphs

## Initial Implementation: The Overall Algorithm

1. Input the value of 'k'. Then, input the number of reads that the user shall provide to the program.
2. For each of the reads, generate k-mers. 
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

Whichever string occurs 2 times (or more) out of the three, show that string. If all the 3 strings are different, show them all.


## Building the De Bruijn Graph

A De-Bruijn graph is a **directed multi-graph** (can have more than one edge between 2 nodes) that is always Eulerian (always has an Eulerian path).
We shall use an **Adjacency List** representation for the De-Bruijn graph. 

First of all, we'll be needing a `class Node` for this.

A class DeBruijnGraph would be handy for this.

Details of implementation coming up soon.
