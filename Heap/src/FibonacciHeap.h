
#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include "Heap.h"
#include <fstream>
#include <cstdlib>
#include <map>

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
		std::map<int, Location> rankToAddress;

		void consolidate();
		void addToRoot(FibonacciNode* x);
		void heapLink(FibonacciNode* x, FibonacciNode* y);
		void cut(FibonacciNode* x, FibonacciNode* y);
		void cascadingCut(FibonacciNode* y);
		void printDOT(FibonacciNode *root,fstream& out);

	public:
		FibonacciHeap();
		~FibonacciHeap();
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
