
#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;


void purgeList(List &list)
{
	index currentElement, elementToBeComparedAgainst;

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



int main(int argc, char*argv[]) {
	int element;
	List listToPurge;

	if(argc < 3)
	{
		cout << "Not enough parameters";
		return 1;
	}
	ifstream fileToRead(argv[1]);
	ofstream fileToWrite(argv[2]);

	while(fileToRead >> element)
		listToPurge.addElement(element);
	fileToRead.close();

	cout << "\n\nOriginal list:\n";
	listToPurge.displayElements(cout);

	cout << "\n\nPurged list:\n";
	purgeList(listToPurge);
	listToPurge.displayElements(cout);
	listToPurge.displayElements(fileToWrite);
	cout<<endl;
	fileToWrite.close();

	return 0;
}
