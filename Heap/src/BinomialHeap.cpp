
#include "BinomialHeap.h"


using namespace std;

BinomialHeap::BinomialHeap()
{
	makeHeap();
}

BinomialHeap::~BinomialHeap()
{
	clear(head);
}


void BinomialHeap :: makeHeap()
{
	minElement = NULL;
	head = NULL;
}


Location BinomialHeap :: insertKey(Priority key)
{
	BinomialNode * newNode;
	if(getLocation(key) != NULL) {
		//duplicate key
		return NULL;
	}

	newNode = new BinomialNode;
	newNode->key = key;
	newNode->parent = NULL;
	newNode->child = NULL;
	newNode->sibling = NULL;
	newNode->degree = 0;
	setLocation(newNode,key);
	head = heapUnion(head, newNode);

	if(minElement==NULL ||minElement->key > key)
	{
		minElement = newNode;
	}
	return newNode;
}


int BinomialHeap :: deleteKey(Location nodeAddress)
{
	decreaseKey(nodeAddress,MIN_PRIORITY);
	extractMin();
	return 0;
}


Priority BinomialHeap :: extractMin()
{

	if(minElement == NULL)
		return -1;


	BinomialNode * ptr = head;
	BinomialNode *chlidList;
	Priority key;

	key=minElement->key;
	chlidList =minElement->child;

	// remove element from root list
	if(ptr == minElement)
	{
		head = ptr->sibling;
	}
	else
	{
		while (ptr->sibling != minElement)
			ptr=ptr->sibling;
		ptr->sibling=minElement->sibling;
	}
	deleteLocation(key);
	delete minElement;

	//reverse child list
	chlidList = reverseList(chlidList);
	//union child list
	head = heapUnion(head,chlidList);
	setMin();

	return key;
}


Priority BinomialHeap :: findMin()
{
	return minElement->key;
}


int BinomialHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
	BinomialNode * node;
	BinomialNode * minNode = NULL;
	BinomialNode * x;
	node = (BinomialNode *) nodeAddress;
	Priority min; //= MAX_PRIORITY;

	if (newKey < node->key)
	{
		std::cerr<<"hew key is less than current key";
		return node->key;
	}
	node->key = newKey;

	x = node->child;
	while(x != NULL)
	{
		if(x->key<min)
		{
			min = x->key;
			//TODO
		}
	}
	return 0;
}


int BinomialHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
	BinomialNode * node;
	BinomialNode * y,* z;
	Priority temp;

	node = (BinomialNode *) nodeAddress;

	if (newKey > node->key)
	{
		std::cerr<<"hew key is greater than current key";
		return node->key;
	}
	deleteLocation(node->key);
	node->key = newKey;
	y = node;
	z = y->parent;
	while( z != NULL and y->key < z->key)
	{
		//do exchange key[y] and key[z]
		//   if y and z have satellite fields, exchange them, too.

		temp = y->key;
		y->key = z->key;
		z->key = temp;

		//update location
		setLocation(y,y->key);
		setLocation(z,z->key);

		y = z;
		z = y->parent;
	}
	if(minElement->key < newKey)
	{
		minElement = y;
	}
	return newKey;
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
	Priority min =MAX_PRIORITY;
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

BinomialHeap::BinomialNode* BinomialHeap::reverseList(BinomialNode *listHead)
{
	BinomialNode* prev=NULL;
	BinomialNode* next=NULL;
	BinomialNode* ptr=listHead;
	while(ptr != NULL)
	{
		next=ptr->sibling;
		ptr->sibling=prev;

		//make parent NULL

		ptr->parent = NULL;
		//TODO check working;

		prev=ptr;
		ptr=next;
	}
	return prev;
}
