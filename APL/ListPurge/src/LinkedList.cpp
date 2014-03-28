
#include "LinkedList.h"

namespace linkedList
{
	/*
	 * Description: Constructor of List class for Linked List based implementation
	 * Input      : N/A
	 * Output     : The List object appropriately initialized
	 */
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



	/*
	 * Description: Destructor List class for Linked List based implementation
	 * Input      : N/A
	 * Output     : Deallocates list nodes and frees up memory acquired
	 */
	List::~List()
	{
		index next,current = head;
		while(current != NULL)
		{
		  next = current->next;
		  delete current;
		  current = next;
		}
	}



	/*
	 * Description: Returns the pointer to the first node of the linked list
	 * Input      : N/A
	 * Output     : Returns the pointer to the first node of the linked list
	 */
	index List::firstPosition()
	{
		return head;
	}



	/*
	 * Description: Returns the pointer to the last node of the linked list
	 * Input      : N/A
	 * Output     : Returns the pointer to the last node of the linked list
	 */
	index List::endPosition()
	{
		return (lastNode);
	}



	/*
	 * Description: Returns the pointer to the next node of the linked list
	 * Input      : Position of the current node
	 * Output     : Returns the pointer to the next node following the node at <position>
	 */
	index List::nextPosition(index position)
	{
		return (position->next);
	}



	/*
	 * Description: Returns the data contained in the node following the node at <position>
	 * Input      : Position of the current node
	 * Output     : Returns the data contained in the node following the node at <position>
	 */
	data List::retrieveElement(index position)
	{
		if(position->next!=NULL)
		  return position->next->element;
		else
		  throw "Index Out of Bound Exception";
	}



	/*
	 * Description: Adds a new data element at the end of the list
	 * Input      : N/A
	 * Output     : Adds a new data element at the end of the list
	 */
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



	/*
	 * Description: Deletes the next node following the one at <position>
	 * Input      : Position of the current node
	 * Output     : Deletes the next node following the one at <position>
	 */
	void List::deleteElement(index position)
	{
		index delNode;

		if(position!=NULL && position->next!=NULL)
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



	/*
	 * Description: Displays the elements of the list
	 * Input      : Stream to write to
	 * Output     : Displays the elements of the list on appropriate stream, e.g. file/console
	 */
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
