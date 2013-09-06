/*
 * Dictinory.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: abil
 */

#include "Dictionary.h"
#include <ctime>
#include <fstream>

void Dictionary::populateDictionary(const char * InputFile,
		const char * TimeFile,bool timer)
{
	clock_t insTime,startTime;
	 startTime = clock();
	//TODO read input
	//TODO insert value

	 //	 insert(value);


	 insTime = clock() - startTime;

	 if(timer)
	 {
		//TODO append timing info
		//seconds  = ((float)lookupTime)/CLOCKS_PER_SEC);

	 }

}
void Dictionary::lookupDictionary(const char * InputFile,
		const char * TimeFile,bool timer)
{
	clock_t lookupTime,startTime;
	 startTime = clock();
	 	//TODO lookup
	  // search(value);
	 lookupTime = clock() - startTime;

	 if(timer)
	 	 {
	 		//TODO append timing info

	 		//seconds  = ((float)insTime)/CLOCKS_PER_SEC);
	 	 }
}



