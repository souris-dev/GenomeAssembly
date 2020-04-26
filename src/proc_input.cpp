#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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
}