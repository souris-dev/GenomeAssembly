// main.cpp
// Application entry point
#include "../include/DeBruijnGraph.h"

int main()
{
    vector<string> Reads;
   
    cout << "\nEnter k: ";
    int k;
    cin >> k;
   
    cout << "\nEnter number of reads: ";
    int count;
    cin >> count;

    cout << "\nPlease enter the reads: \n";
    
    // input the reads
    for (int i = 0; i < count; i++)
    {
        string read;
        cin >> read;
        Reads.push_back(read);
    }
    
    KMerifier kmf = KMerifier(k, Reads);

    // The DeBruijnGraph takes a KMerifier object in its constructor
    DeBruijnGraph dbg = DeBruijnGraph(kmf);

    // Get the original string by performing an Eulerian walk of the graph
    string orign = dbg.DoEulerianWalk();

    cout << "Original String is : " << orign;

    return 0;
}
