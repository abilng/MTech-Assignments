
#ifndef HEAP_H_
#define HEAP_H_

#include "iostream"
#include <map>

typedef int Priority;
typedef void* Location;

class Heap
{
	protected:
		std::map<Priority, Location> keyToAddress;
	public:
		virtual ~Heap() {};
		virtual void makeHeap() = 0;
		virtual Location insertKey(Priority key) = 0;
		virtual int deleteKey(Location nodeAddress) = 0;
		virtual Priority extractMin() = 0;
		virtual Priority findMin() = 0;
		virtual int increaseKey(Location nodeAddress, Priority newKey) = 0;
		virtual int decreaseKey(Location nodeAddress, Priority newKey) = 0;
		virtual void displayHeap(char* fileName) = 0;
};

#endif
