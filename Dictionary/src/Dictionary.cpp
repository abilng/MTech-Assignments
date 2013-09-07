/*
 * Dictinory.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: abil
 */

#include "Dictionary.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

void Dictionary::populateDictionary(const char* InputFile,	const char* TimeFile, bool timer)
{
	clock_t insTime = 0, startTime;
	int nElements=0, element;
	char errorMsg[30];

	ifstream fileToRead(InputFile);
	if (!fileToRead.is_open())
	{
			perror("Error:");
			exit(2);
	}

	while(fileToRead >> element)
	{
		startTime = clock();
		insert(element);
		insTime += (clock() - startTime);
		cout << "Inserted " << element << ": ";
		display();
		cout << endl;
	}
	fileToRead.close();

	if(timer)
	{
		float seconds  = ((float)insTime)/CLOCKS_PER_SEC;
		fstream outfp;
		outfp.open(TimeFile, fstream::app|fstream::out);
		if (!outfp.is_open())
		{
			sprintf(errorMsg,"Error while opening %s:",InputFile);
			perror(errorMsg);
		}
		outfp << nElements << "\t" << seconds << endl;
		outfp.close();
	}
}


void Dictionary::lookupDictionary(const char* InputFile, const char* TimeFile,bool timer)
{
	clock_t lookupTime = 0, startTime;
	int nElements=0, element;
	bool isFound;

	ifstream fileToRead(InputFile);
	if (!fileToRead.is_open())
	{
			perror("Error:");
			exit(2);
	}

	while(fileToRead >> element)
	{
		startTime = clock();
		isFound = search(element);
		lookupTime += (clock() - startTime);
		cout << "Searched " << element << ": ";
		if(isFound)
			cout << "Found";
		else
			cout << "Not found";
		cout << endl;
	}
	fileToRead.close();

	if(timer)
	{
		float seconds  = ((float)lookupTime)/CLOCKS_PER_SEC;
		fstream outfp;
		outfp.open(TimeFile,fstream::app|fstream::out);
		if (!outfp.is_open())
		{
			char errorMsg[30];
			sprintf(errorMsg,"Error while opening %s:",TimeFile);
			perror(errorMsg);
			exit(2);
		}
		outfp << nElements << "\t" << seconds << endl;
		outfp.close();
	}
}

