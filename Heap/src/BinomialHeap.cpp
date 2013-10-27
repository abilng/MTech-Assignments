
#include "BinomialHeap.h"
#include <climits>

using namespace std;

BinomialHeap::BinomialHeap()
{
	minElement = NULL;
	head = NULL;

}

BinomialHeap::~BinomialHeap()
{
	// TODO Auto-generated destructor stub
}


void BinomialHeap :: makeHeap()
{
	// TODO Auto-generated stub
}


Location BinomialHeap :: insertKey(Priority key)
{
	// TODO Auto-generated stub
	return 0;
}


int BinomialHeap :: deleteKey(Location nodeAddress)
{
	// TODO Auto-generated stub
	return 0;
}


Priority BinomialHeap :: extractMin()
{
	// TODO Auto-generated stub
	return 0;
}


Priority BinomialHeap :: findMin()
{
  return 0;
}


int BinomialHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
	// TODO Auto-generated stub
	return 0;
}


int BinomialHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
	// TODO Auto-generated stub
	return 0;
}


void BinomialHeap :: displayHeap(char* fileName)
{
	// TODO Auto-generated stub
}

void BinomialHeap::link(BinomialNode *y, BinomialNode * z)
{
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree = z->degree + 1;
}

void BinomialHeap::setMin()
{
  BinomialNode * y = NULL;
  BinomialNode * x = head;
  Priority min =INT_MAX;
  while (x != NULL)
  	{
  		if (x->key < min)
  		{
  	     min = x->key;
         y=x;
  		}
         x = x->sibling;
  	}
  minElement = y;
}
