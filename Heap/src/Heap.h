
#ifndef HEAP_H_
#define HEAP_H_

#include "iostream"

typedef int priority;

class Heap
{
	public:
	virtual ~Heap() {};
	virtual void makeHeap() = 0;
	virtual void* insertKey(priority key) = 0;
	virtual int deleteKey(void* nodeAddress) = 0;
	virtual priority extractMin() = 0;
	virtual priority findMin() = 0;
	virtual int increaseKey(void* nodeAddress, priority newKey) = 0;
	virtual int decreaseKey(void* nodeAddress, priority newKey) = 0;
	virtual void displayHeap(char* fileName) = 0;
};

#endif
