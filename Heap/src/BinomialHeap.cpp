
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
	return minElement->key;
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

/**
 * delete all tree rooted at list
 */
void BinomialHeap::clear(BinomialNode* listRoot)
{
	if(listRoot == NULL) return;
	BinomialNode* ptr = listRoot;
	BinomialNode * temp;
	while(ptr != NULL)
	{
		temp = ptr;
		clear(ptr->child);
		ptr=temp->sibling;
		delete temp;
	}
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
		if (x->degree < min)
		{
			min = x->degree;
			y=x;
		}
		x = x->sibling;
	}
	minElement = y;
}

/**
 *
 * returns a root list H that is sorted by
 *  monotonically increasing degree
 */
BinomialHeap::BinomialNode* BinomialHeap::mergeList(
		BinomialNode* head1, BinomialNode* head2)
{
	if (head1 == NULL) return head2;
	if (head2 == NULL) return head1;

	BinomialNode * newHead =NULL;
	BinomialNode * listEnd =NULL;

	while(head1 != NULL && head2 != NULL) {
		if (head1->degree <= head2->degree)
		{
			if(listEnd==NULL) newHead=head1;
			else listEnd->sibling = head1;
			listEnd = head1;
			head1=head1->sibling;
		}
		else
		{
			if(listEnd==NULL) newHead=head2;
			else listEnd->sibling = head2;
			listEnd = head2;
			head2 = head2->sibling;
		}
	}
	if (head1 == NULL) listEnd->sibling = head2;
	else listEnd->sibling = head1;
	return newHead;
}

BinomialHeap::BinomialNode* BinomialHeap::heapUnion(
		BinomialNode* h1, BinomialNode* h2)
{
	BinomialNode * newHead = NULL;
	BinomialNode * x = NULL;
	BinomialNode * next_x = NULL;
	BinomialNode * prev_x = NULL;


	newHead = mergeList(h1,h2);

	if(newHead == NULL)
		return newHead;

	x=newHead;
	next_x = x->sibling;
	while(next_x !=NULL)
	{
		/*
		 * Case1: degree[x] ≠ degree[next-x]
		 *          :-  do nothing,just increment
		 *
		 * Case2: degree[x] = degree[next-x] = degree[sibling[next-x]].
		 *          :- do nothing,just increment
		 *
		 * Case3: degree[x] = degree[next-x] ≠ degree[sibling[next-x]]
		 *       and  key[x] ≤ key[next-x]
		 *          :- removes next-x from the root list,
		 *             and make next-x the leftmost child of x.
		 *
		 * Case4: degree[x] = degree[next-x] ≠ degree[sibling[next-x]]
		 *       and  key[x] > key[next-x]
		 *          :- next-x has the smaller key, so x is linked to next-x.
		 *
		 */

		if((x->degree != next_x->degree)//Case 1
				||((next_x->sibling != NULL)&& //Case 2
						(x->degree == next_x->sibling->degree)))
		{
			prev_x=x;
			x = next_x;
		}
		else if (x->key <= next_x->key)//case2
		{
			x->sibling = next_x->sibling;
			link(next_x, x);
		}
		else{ //Case 4
			if (prev_x == NULL) newHead = next_x;
			else prev_x->sibling = next_x;
			link(x, next_x);
			x = next_x;
		}
		next_x = x->sibling;
	}
	return newHead;
}

