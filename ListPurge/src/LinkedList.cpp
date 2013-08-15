
#include "LinkedList.h"



List::List()
{
	firstNode = NULL;
	lastNode = NULL;
	elementCount = 0;
}



int List::firstPosition()
{
	if(elementCount)
		return 0;
	else
		return -1;
}



int List::endPosition()
{
	return (elementCount);
}



int List::nextPosition(int position)
{
	return (position + 1);
}



int List::retrieveElement(int position)
{
	struct Node* currentNode;
	int positionIndex;

	currentNode = firstNode;
	for(positionIndex = 0; positionIndex < position; positionIndex++)
	{
		if(!currentNode)
			break;
		else
			currentNode = currentNode->nextNode;
	}

	return currentNode->element;
}



void List:: addElement(int element)
{
	struct Node* newNode;

	newNode = (Node*)malloc(sizeof(struct Node));
	newNode->element = element;
	newNode->nextNode = NULL;

	if(!elementCount)
	{
		firstNode = newNode;
		lastNode = firstNode;
	}
	else
	{
		lastNode->nextNode = newNode;
		lastNode = newNode;
	}
	elementCount++;
}



void List::deleteElement(int position)
{
	struct Node* currentNode, *nextNode;
	int positionIndex;

	if(!position)
	{
		firstNode = firstNode->nextNode;
		elementCount--;
		return;
	}

	currentNode = firstNode;
	for(positionIndex = 0; positionIndex < position - 1; positionIndex++)
		if(!currentNode)
			return;
		else
			currentNode = currentNode->nextNode;

	nextNode = currentNode->nextNode;
	currentNode->nextNode = nextNode->nextNode;
	elementCount--;

	return;
}



void List::displayElements()
{
	struct Node* currentNode;

	currentNode = firstNode;
	while(currentNode)
	{
		printf("%d ", currentNode->element);
		currentNode = currentNode->nextNode;
	}

	return;
}
