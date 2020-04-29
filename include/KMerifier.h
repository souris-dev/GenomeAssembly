// KMerifier.h
// Contains prototypes for the KMerifier class

#ifndef KMERIFIER_H
#define KMERIFIER_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;
// This is actually bad practice, but for simplicity
// and because we won't be using any other namespace for now


class KMerifier
{
private:
	int k;
	int k_minus_1;
	vector<string> reads;

public:
	KMerifier() = default; // to keep the compiler happy 
	KMerifier(int Kay, vector<string> Reads); // constructor
	
	unordered_map<int, string> getKMers(); // returns KMers of the reads, in order
	unordered_map<int, string> getKMinusOneMers(); // returns (K-1)-Mers of the reads in order
	
	// using unordered_map above instead of a vector has some benefits here

	unordered_set<string> getUniqueKMinusOneMers(); // returns unique (k-1)-mers

	int getK(); // returns value of k
	void setK(int kay); // sets the value of k
	
	//For debugging
	void dispKMers();//display k mers
	void dispKOneMers();//display (k-1)-mers
	void dispUniqueKOneMers();//display unique (k-1)-mers
};

#endif
