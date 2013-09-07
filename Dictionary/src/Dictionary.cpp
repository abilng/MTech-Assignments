/*
 * Dictionary.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: Dipanjan
 */

#include "Dictionary.h"

void Dictionary::populateDictionary(const char *InputFile, const char * TimeFile, bool timer)
{
	int element;

	ifstream fileToRead(InputFile);
	//ofstream fileToWrite(argv[2]);

	while(fileToRead >> element)
		insert(element);

	fileToRead.close();
}
