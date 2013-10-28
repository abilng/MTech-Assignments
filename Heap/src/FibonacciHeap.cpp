
#include "FibonacciHeap.h"

using namespace std;

FibonacciHeap::FibonacciHeap()
{
	minPointer = NULL;
	nodes = 0;
}

FibonacciHeap::~FibonacciHeap()
{
	// TODO Auto-generated destructor stub
}

void FibonacciHeap :: makeHeap()
{
	// TODO Auto-generated stub
}


Location FibonacciHeap :: insertKey(Priority key)
{
	FibonacciNode* newNode = new FibonacciNode;
	newNode->degree = 0;
	newNode->parent = NULL;
	newNode->child = NULL;
	newNode->mark = false;
	if(!minPointer)
		minPointer = newNode;
	else
	{
		newNode->rightSibling = minPointer->rightSibling;
		newNode->leftSibling = minPointer;
		minPointer->rightSibling = newNode;
	}

	if(newNode->key < minPointer->key)
		minPointer = newNode;
	nodes++;

	return newNode;
}


int FibonacciHeap :: deleteKey(Location nodeAddress)
{
	// TODO Auto-generated stub
	return 0;
}


Priority FibonacciHeap :: extractMin()
{
	FibonacciNode tempMinPointer = minPointer->rightSibling;
	minPointer->leftSibling->rightSibling = minPointer->rightSibling;
	delete minPointer;

	return 0;
}


Priority FibonacciHeap :: findMin()
{
	return minPointer->key;
}


int FibonacciHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
	// TODO Auto-generated stub
	return 0;
}


int FibonacciHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
	// TODO Auto-generated stub
	return 0;
}


void FibonacciHeap :: displayHeap(char* fileName)
{
	// TODO Auto-generated stub
}

