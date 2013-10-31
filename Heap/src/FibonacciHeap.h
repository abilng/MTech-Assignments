
#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include "Heap.h"
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <cmath>
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
		bool isEmpty();
		Location insertKey(Priority key);
		bool deleteKey(Location nodeAddress);
		Priority extractMin();
		Priority findMin();
		bool updateKey(Location nodeAddress, Priority newKey);
		bool increaseKey(Location nodeAddress, Priority newKey);
		bool decreaseKey(Location nodeAddress, Priority newKey);
		bool displayHeap(char const* fileName);
};

#endif
