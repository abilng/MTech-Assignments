
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
		Location insertKey(Priority key);
		int deleteKey(Location nodeAddress);
		Priority extractMin();
		Priority findMin();
		int increaseKey(Location nodeAddress, Priority newKey);
		int decreaseKey(Location nodeAddress, Priority newKey);
		void displayHeap(char* fileName);
};

#endif
