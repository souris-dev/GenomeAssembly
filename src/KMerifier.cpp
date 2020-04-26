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
}

unordered_map<int, string> KMerifier::getKMinusOneMers()
{
    // returns (K-1)-Mers of the reads in order
}


unordered_set<string> KMerifier::getUniqueKMinusOneMers()
{
    // returns unique (k-1)-mers
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