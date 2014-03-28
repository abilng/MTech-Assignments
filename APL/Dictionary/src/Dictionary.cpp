
#include "Dictionary.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;



/*
 * Input: File from which data to be loaded and timimg information to be written to
 * Output: Loads ADT from the input data file and writes timing information to time file
 * Description: N/A
 */
void Dictionary::populateDictionary(const char* InputFile,	const char* TimeFile, bool timer)
{
	clock_t insTime = 0, startTime;
	int nElements=1, element;
	char errorMsg[30];

	ifstream fileToRead(InputFile);
	if (!fileToRead.is_open())
	{
			perror("Error:");
			exit(2);
	}

	while(fileToRead >> element)
	{
		nElements++; cout << element << endl;
		//if(fileToRead.bad())
			//cout << "I/O error while reading file \"" << InputFile << "\" at position " << nElements << ", skipping remaining input.\n";
		startTime = clock();
		insert(element);
		insTime += (clock() - startTime);
	}
	fileToRead.close();

	if(timer)
	{
		double seconds  = ((double)insTime)/CLOCKS_PER_SEC;
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



/*
 * Input: File from which data to be looked up and timimg information to be written to
 * Output: Searches ADT from the lookup data file and writes timing information to time file
 * Description: N/A
 */
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
		nElements++;
		if(fileToRead.bad())
			cout << "I/O error while reading file \"" << InputFile << "\" at position " << nElements << ", skipping remaining input.\n";
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
		double seconds  = ((double)lookupTime)/CLOCKS_PER_SEC;
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
