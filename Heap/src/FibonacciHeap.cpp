
#include "FibonacciHeap.h"

using namespace std;

FibonacciHeap::FibonacciHeap()
{
	minPointer = NULL;
	nodes = 0;
}


FibonacciHeap::~FibonacciHeap()
{

}


void FibonacciHeap::addToRoot(FibonacciNode* x)
{
	if(!minPointer)
	{
		minPointer = x;
		x->leftSibling = x;
		x->rightSibling = x;
	}
	else
	{
		x->rightSibling = minPointer->rightSibling;
		x->leftSibling = minPointer;
		minPointer->rightSibling = x;
		x->rightSibling->leftSibling = x;
	}
}


void FibonacciHeap::consolidate()
{

}


void FibonacciHeap::heapLink(FibonacciNode* x, FibonacciNode* y)
{
	y->leftSibling->rightSibling = y->rightSibling;
	y->leftSibling = x->child;
	y->rightSibling = x->child->rightSibling;
	x->child->rightSibling = y;
	x->degree++;
	y->mark = false;
}


void FibonacciHeap::cut(FibonacciNode* x, FibonacciNode* y)
{
	x->rightSibling->leftSibling = x->leftSibling;
	x->leftSibling->rightSibling = x->rightSibling;
	y->degree--;

	// If x is the first child, update parent's(y) child pointer
	if(y->child == x)
		y->child = x->rightSibling;

	// Add x to the root list
	addToRoot(x);

	x->parent = NULL;
	x->mark = false;
}


void FibonacciHeap::cascadingCut(FibonacciNode* y)
{
	FibonacciNode* z = y->parent;
	if(z)
	{
		if(y->mark == false)
			y->mark = true;
		else
		{
			cut(y, z);
			cascadingCut(z);
		}
	}
}


void FibonacciHeap :: makeHeap()
{

}


Location FibonacciHeap :: insertKey(Priority key)
{
	FibonacciNode* newNode = new FibonacciNode;
	newNode->degree = 0;
	newNode->parent = NULL;
	newNode->child = NULL;
	newNode->mark = false;
	newNode->key = key;
	setLocation(newNode, key);

	addToRoot(newNode);
	if(newNode->key < minPointer->key)
		minPointer = newNode;
	nodes++;

	return newNode;
}


int FibonacciHeap :: deleteKey(Location nodeAddress)
{
	decreaseKey(nodeAddress, -1);
	extractMin();
	return 0;
}


Priority FibonacciHeap :: extractMin()
{
	FibonacciNode* extractedNode = minPointer;

	if(!extractedNode)
	{
		FibonacciNode *childPointer = extractedNode->child, *nextChild;
		while(childPointer)
		{
			nextChild = childPointer->rightSibling;
			childPointer->rightSibling = minPointer->rightSibling;
			childPointer->leftSibling = minPointer;
			minPointer->rightSibling = childPointer;
			childPointer->parent = NULL;
			childPointer = nextChild;
		}

		extractedNode->leftSibling->rightSibling = extractedNode->rightSibling;
		if(extractedNode == extractedNode->rightSibling)
			minPointer = NULL;
		else
			consolidate();
		nodes--;

		return extractedNode->key;
	}
	minPointer->leftSibling->rightSibling = minPointer->rightSibling;
	delete minPointer;

	return 0;
}


Priority FibonacciHeap :: findMin()
{
	return minPointer->key;
}


bool FibonacciHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
	return true;
}


bool FibonacciHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
	FibonacciNode* x = (FibonacciNode*)nodeAddress;
	FibonacciNode* y;

	if(newKey > x->key)
		return -1;
	x->key = newKey;
	y = x->parent;

	if((y != NULL) && (x->key < y->key))
	{
		cut(x, y);
		cascadingCut(y);
	}

	if(x->key < minPointer->key)
		minPointer = x;

	return true;
}


bool FibonacciHeap :: displayHeap(char* fileName)
{
	FibonacciNode* temp = minPointer;
	do
	{
		cout << temp->key << " ";
		temp = temp->leftSibling;
	}
	while(temp != minPointer);
	return true;
}
