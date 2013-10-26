
#ifndef BINARY_H_
#define BINARY_H_

#include "Heap.h"

class BinaryHeap: public Heap
{
	private:
		struct BinaryNode
		{
			priority key;
			struct BinaryNode *parent, *leftSibling, *rightSibling, *leftChild, *rightChild;
		};
		struct BinaryNode *root, *lastElement;

	public:
		BinaryHeap();
		~BinaryHeap();
		void makeHeap();
		void* insertKey(priority key);
		int deleteKey(void* nodeAddress);
		priority extractMin();
		priority findMin();
		int increaseKey(void* nodeAddress);
		int decreaseKey(void* nodeAddress);
		void displayHeap(char* fileName);
};

#endif
