
#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include "Heap.h"

using namespace std;

class BinomialHeap: public Heap
{
	private:
		struct BinomialNode
		{
			Priority key;
			struct BinaryNode *parent, *childList;
		};
		struct BinomialNode *rootList, *minElement;
	public:
		BinomialHeap();
		~BinomialHeap();
		void makeHeap();
		Location insertKey(Priority key);
		int deleteKey(Location nodeAddress);
		Priority extractMin();
		Priority findMin();
		int increaseKey(Location nodeAddress, Priority newKey);
		int decreaseKey(Location nodeAddress, Priority newKey);
		void displayHeap(char* fileName);
};

#endif
