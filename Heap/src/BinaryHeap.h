
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
        void clear(BinaryNode*);
        void printDOT(BinaryNode *root1,fstream& out);

	public:
		BinaryHeap();
		~BinaryHeap();
		void makeHeap();
		Location insertKey(Priority key);
		int deleteKey(Location nodeAddress);
		Priority extractMin();
		Priority findMin();
		bool increaseKey(Location nodeAddress, Priority newKey);
		bool decreaseKey(Location nodeAddress, Priority newKey);
		bool displayHeap(char const* fileName);
};

#endif
