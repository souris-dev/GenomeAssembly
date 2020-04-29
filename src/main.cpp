// main.cpp
// Application entry point
#include "../include/DeBruijnGraph.h"
#include "../include/KMerifier.h" // this line is not required, but for clarity

int main()
{

    vector<int, string> Reads;
    unordered_map<int, string> kmers;
    unordered_map<int, string> k_1_mers;
    unordered_set<string> k_1_mers_nodup;

    kmers=getKMers();
    k_1_mers=getKMinusOneMers();
    k_1_mers_nodup=getUniqueKMinusOneMers();

    cout << "\nEnter k: ";
    int k;
    cin >> k;

    cout << "\nEnter number of reads: ";
    int count;
    cin >> count;

    vector<string>Reads;

     for (int i = 0; i < count; i++)
    {
        string read;
        cin >> read;
        Reads.pushback(read)

    }

    KMerifier kmf= KMerifier(k,Reads);
    DeBruijnGraph dbg = DeBruijnGraph(kmf);

    string orign = dbg.DoEulerianWalk();

    cout<<"Original String is : " << orign;

    return 0;
}
