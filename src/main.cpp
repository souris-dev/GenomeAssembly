// main.cpp
// Application entry point
#include "../include/DeBruijnGraph.h"
#include "../include/KMerifier.h" // this line is not required, but for clarity

int main()
{

    vector<int, string> Reads;
   
    cout << "\nEnter k: ";
    int k;
    cin >> k;
   
    cout << "\nEnter number of reads: ";
    int count;
    cin >> count;


     for (int i = 0; i < count; i++)
    {
        string read;
        cin >> read;
        Reads.push_back(read);

    }
    
    
    KMerifier kmf= KMerifier(k,Reads);
    DeBruijnGraph dbg = DeBruijnGraph(kmf);

    string orign = dbg.DoEulerianWalk();

    cout<<"Original String is : " << orign;

    return 0;
}
