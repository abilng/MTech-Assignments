
#include <iostream>
#include "LinkedList.h"

using namespace std;



void purgeList(List list)
{
	int currentElement, elementToBeComparedAgainst;

	currentElement = list.firstPosition();
	while(currentElement != list.endPosition())
	{
		elementToBeComparedAgainst = list.nextPosition(currentElement);
		while(elementToBeComparedAgainst != list.endPosition())
		{
			if(list.retrieveElement(currentElement) == list.retrieveElement(elementToBeComparedAgainst))
				list.deleteElement(elementToBeComparedAgainst);
			else
				elementToBeComparedAgainst = list.nextPosition(elementToBeComparedAgainst);
		}
		currentElement = list.nextPosition(currentElement);
	}
}



int main() {
	int numberOfElements, elementCount, element;
	List listToPurge;

	cout << "Enter the number of elements in the list: ";
	cin >> numberOfElements;

	for(elementCount = 1; elementCount <= numberOfElements; elementCount++)
	{
		cout << "\nElement(" << elementCount << "): ";
		cin >> element;
		listToPurge.addElement(element);
	}

	cout << "\n\nOriginal list:\n";
	listToPurge.displayElements();

	cout << "\n\nPurged list:\n";
	purgeList(listToPurge);
	listToPurge.displayElements();

	return 0;
}
