
#ifndef HEAP_H_
#define HEAP_H_

#include "iostream"

typedef int Priority;

class Heap
{
	public:
	virtual ~Heap() {};
	virtual void makeHeap() = 0;
	virtual void* insertKey(Priority key) = 0;
	virtual int deleteKey(void* nodeAddress) = 0;
	virtual Priority extractMin() = 0;
	virtual Priority findMin() = 0;
	virtual int increaseKey(void* nodeAddress, Priority newKey) = 0;
	virtual int decreaseKey(void* nodeAddress, Priority newKey) = 0;
	virtual void displayHeap(char* fileName) = 0;
};

#endif
