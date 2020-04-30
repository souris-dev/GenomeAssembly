#include "../include/KMerifier.h"

// Implementation of the KMerifier class

KMerifier::KMerifier(int Kay, vector<string> Reads)
{
    // initialize class data members k, k_minus_1 and reads
    k = Kay;
    k_minus_1 = k - 1;
    reads = Reads;
}


unordered_map<int, string> KMerifier::getKMers()
{
    // returns KMers of the reads, in order

    int ind = 0;
    unordered_map<int, string> kmers;
    
    for (int i = 0; i < reads.size(); i++)
    {
        // k-merify
        for (int j = 0; j < (reads[i].length() - k + 1); j++)
        {
            kmers[ind] = reads[i].substr(j, k);
            ind++;
        }
        
    }
    return kmers;
}
  

unordered_map<int, string> KMerifier::getKMinusOneMers()
{
    // returns (K-1)-Mers of the reads in order

    unordered_map<int, string> kmers;
    unordered_map<int, string> k_1_mers;
    kmers = getKMers();

    for (int i = 0; i < kmers.size(); i++)
    {
        // for ith kmer, its left k-1-mer is at 2*i and right k-1-mer is at 2*i + 1 index
        // of k_1_mers
        string km = kmers[i];

        k_1_mers[i*2] = km.substr(0, k-1);
        k_1_mers[i*2 + 1] = km.substr(1, k-1);
        
    }
    return k_1_mers;
}


unordered_set<string> KMerifier::getUniqueKMinusOneMers()
{
    // returns unique (k-1)-mers

    unordered_map<int, string> kmers;
    unordered_map<int, string> k_1_mers;
    unordered_set<string> k_1_mers_nodup;
    kmers = getKMers();
    k_1_mers = getKMinusOneMers();

    for (int i = 0; i < kmers.size(); i++)
    {
        k_1_mers_nodup.insert(k_1_mers[i*2]);
        k_1_mers_nodup.insert(k_1_mers[i*2 + 1]);
    }
    
    return k_1_mers_nodup;
}


int KMerifier::getK()
{
    // returns value of k
    return k;
}


void KMerifier::setK(int kay)
{
    // sets the value of k
    k = kay;
}


void KMerifier::dispKMers()
{
    // shows KMers

    unordered_map<int, string> kmers;
    kmers = getKMers();
    
    for (int i = 0; i < kmers.size(); i++)
    {
       cout << kmers[i] << endl;
    }
}


void KMerifier::dispKOneMers()
{
    // shows k-1-mers

    unordered_map<int, string> k_1_mers;
    k_1_mers = getKMinusOneMers();
    for (int i = 0; i < k_1_mers.size(); i++)
    {
       cout << k_1_mers[i] << endl;
    }
}


void KMerifier::dispUniqueKOneMers()
{
    // shows unique k-1-mers
    
    unordered_set<string> k_1_mers_nodup;
    k_1_mers_nodup = getUniqueKMinusOneMers();
    
    for (unordered_set<string>::iterator it = k_1_mers_nodup.begin(); it != k_1_mers_nodup.end(); it++)
    {
        cout << *it << endl;
    }
}
