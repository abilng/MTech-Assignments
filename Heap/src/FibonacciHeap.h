
#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include "Heap.h"

using namespace std;

class FibonacciHeap: public Heap
{
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
