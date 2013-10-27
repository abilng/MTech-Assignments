
#ifndef BINARY_H_
#define BINARY_H_

#include "Heap.h"

using namespace std;

class BinaryHeap: public Heap
{
	private:
		struct BinaryNode
		{
			Priority key;
			struct BinaryNode *parent, *leftSibling, *rightSibling, *leftChild, *rightChild;
		};
		struct BinaryNode *root, *lastElement;

	public:
		BinaryHeap();
		~BinaryHeap();
		void makeHeap();
		void* insertKey(Priority key);
		int deleteKey(void* nodeAddress);
		Priority extractMin();
		Priority findMin();
		int increaseKey(void* nodeAddress, Priority newKey);
		int decreaseKey(void* nodeAddress, Priority newKey);
		void displayHeap(char* fileName);
};

#endif
