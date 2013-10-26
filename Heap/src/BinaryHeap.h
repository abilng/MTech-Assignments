
#ifndef BINARY_H_
#define BINARY_H_

#include "iostream"
#include "Heap.h"

class BinaryHeap: public Heap
{
	private:
		struct BinaryNode
		{
			Key key;
			struct BinaryNode *parent, *leftSibling, *rightSibling, *leftChild, *rightChild;
		};
		struct BinaryNode *root, *lastElement;

	public:
		BinaryHeap();
		void makeHeap() = 0;
		int insertKey(Key key) = 0;
		int deleteKey(Key key) = 0;
		Key extractMin() = 0;
		Key findMin() = 0;
		int increaseKey(Key key) = 0;
		int decreaseKey(Key key) = 0;
		void displayHeap(char* fileName) = 0;
};

#endif
