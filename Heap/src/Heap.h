
#ifndef HEAP_H_
#define HEAP_H_

#include "iostream"

typedef int KeyValue;

struct Key
{
	unsigned int id;
	KeyValue value;
};

class Heap
{
	private:
	virtual void searchKey(Key key) = 0;

	public:
	virtual ~Heap() {};
	virtual void makeHeap() = 0;
	virtual int insertKey(Key key) = 0;
	virtual int deleteKey(Key key) = 0;
	virtual Key extractMin() = 0;
	virtual Key findMin() = 0;
	virtual int increaseKey(Key key) = 0;
	virtual int decreaseKey(Key key) = 0;
	virtual void displayHeap(char* fileName) = 0;
};

#endif
