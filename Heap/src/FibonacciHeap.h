
#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include "Heap.h"

using namespace std;

class FibonacciHeap: public Heap
{
	private:
		struct FibonacciNode
		{
			Priority key;
			FibonacciNode *parent, *rightSibling, *leftSibling, *child;
			bool mark;
			unsigned short degree;
		};
		FibonacciNode *minPointer;
		unsigned short nodes;

		void consolidate();
		void addToRoot(FibonacciNode* x);
		void heapLink(FibonacciNode* x, FibonacciNode* y);
		void cut(FibonacciNode* x, FibonacciNode* y);
		void cascadingCut(FibonacciNode* y);

	public:
		FibonacciHeap();
		~FibonacciHeap();
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
