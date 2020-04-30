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

    // input the reads
    for (int i = 0; i < count; i++)
    {
        string read;
        cin >> read;
        Reads.push_back(read);
    }

    
    cout << "The reads are: \n";
    for (int i = 0; i < Reads.size(); i++)
    {
        cout << Reads[i] << endl;
    }
    
    cout << "Initializing KMerifier...\n";
    KMerifier kmf = KMerifier(k, Reads);

    cout << "\nKMers of the reads, where k = " << kmf.getK() << endl;
    kmf.dispKMers();

    cout << "\nK-1 mers of the reads: \n";
    kmf.dispKOneMers();

    // The DeBruijnGraph takes a KMerifier object in its constructor
    DeBruijnGraph dbg = DeBruijnGraph(kmf);
    dbg.printAdjList();

    // Get the original string by performing an Eulerian walk of the graph
    string orign = dbg.DoEulerianWalk();

    cout << "Original String is : " << orign;

    return 0;
}
