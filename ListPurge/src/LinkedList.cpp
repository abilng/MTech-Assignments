
#include "LinkedList.h"

namespace linkedList
{
	List::List()
	{
		index newNode;
		newNode = new Node;
		newNode->element = NA;
		newNode->next = NULL;
		head = newNode;
		lastNode = newNode;
		elementCount = 0;
	}



	List::~List()
	{
		index next,current = head;
		while( current != NULL)
		{
		  next = current->next;
		  delete current;
		  current = next;
		}
	}



	index List::firstPosition()
	{
		return head;
	}



	index List::endPosition()
	{
		return (lastNode);
	}



	index List::nextPosition(index position)
	{
		return (position->next);
	}



	data List::retrieveElement(index position)
	{
		if(position->next!=NULL)
		  return position->next->element;
		else
		  throw "Index Out of Bound Exception";
	}



	void List:: addElement(data element)
	{
		struct Node* newNode;

		newNode = new Node;
		newNode->element = element;
		newNode->next = NULL;

		lastNode->next = newNode;
		lastNode=newNode;
		elementCount++;
	}



	void List::deleteElement(index position)
	{
		index delNode;

		if(position!=NULL&&position->next!=NULL)
		{
			delNode = position->next;
			position->next=position->next->next;
			delete delNode;
			if(position->next==NULL)
				lastNode=position;
			elementCount--;
		}
		else
		  throw "Index Out of Bound Exception";
	}



	void List::displayElements(std::ostream& dataOut)
	{
		index currentNode;

		currentNode = head;
		while(currentNode->next)
		{
			dataOut << currentNode->next->element << " ";
			currentNode = currentNode->next;
		}

		return;
	}
}
