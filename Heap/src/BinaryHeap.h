
#ifndef BINARY_H_
#define BINARY_H_

#include "Heap.h"

using namespace std;

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
		int increaseKey(void* nodeAddress, priority newKey);
		int decreaseKey(void* nodeAddress, priority newKey);
		void displayHeap(char* fileName);
};

#endif
