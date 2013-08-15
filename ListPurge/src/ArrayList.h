/*
 * ArrayList.h
 *
 *  Created on: Aug 14, 2013
 *      Author: abil
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#define MAX_SIZE 100

typedef int data;
typedef int index;

class List
{
private:
	int elementCount;
	data array[MAX_SIZE];

public:
	List();
	index firstPosition();
	index endPosition();
	index nextPosition(index position);
	data retrieveElement(index position);
	void insertElement(index position,data element);
	void addElement(data element);
	void deleteElement(index position);
	void displayElements();
};


#endif /* ARRAYLIST_H_ */
