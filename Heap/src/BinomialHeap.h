
#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include "Heap.h"
#include <fstream>

using namespace std;

class BinomialHeap: public Heap
{
	private:
		struct BinomialNode
		{
			Priority key;
			BinomialNode *parent;
			BinomialNode *child;
			BinomialNode *sibling;
			int degree;
		};

		BinomialNode *head;

		void link(BinomialNode*, BinomialNode*);
		BinomialNode* getMin();
		BinomialNode* mergeList(BinomialNode*, BinomialNode*);
		BinomialNode* reverseList(BinomialNode *);

		BinomialNode* heapUnion(BinomialNode*, BinomialNode*);

		void printDOT(BinomialNode *root,fstream& out);

		void clear(BinomialNode*);

	public:
		BinomialHeap();
		~BinomialHeap();
		void makeHeap();
		Location insertKey(Priority key);
		int deleteKey(Location nodeAddress);
		Priority extractMin();
		Priority findMin();
		bool increaseKey(Location nodeAddress, Priority newKey);
		bool decreaseKey(Location nodeAddress, Priority newKey);
		bool displayHeap(char const* fileName);
};

#endif
