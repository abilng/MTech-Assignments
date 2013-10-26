
#ifndef HEAP_H_
#define HEAP_H_

typedef int KEY;

class Heap
{
	public:
	virtual void makeHeap() = 0;
	virtual int insertKey(KEY key) = 0;
	virtual int deleteKey(KEY key) = 0;
	virtual KEY extractMin() = 0;
	virtual KEY findMin() = 0;
	virtual int increaseKey(KEY key) = 0;
	virtual int decreaseKey(KEY key) = 0;
	virtual void displayHeap() = 0;
};

#endif
