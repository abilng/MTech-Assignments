/*
 * Main.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abilng
 */

#include "Dictionary.h"
#include "BSTree.h"
#include "RBTree.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;


void help(char * prgname)
{
	cout<<"Usage: "<<prgname<<" [-bst][-t] insertFile searchFile";
	cout<<" [ITimeFile] [STimeFile] "<<endl;

	cout<<endl;
	cout<<"-bst		Use Binary Search Tree"<<endl;
	cout<<"		  if this flag is not present,";
	cout<<" program will use Red Black Tree"<<endl;
	cout<<"-t		Calculate time for insert and lookup"<<endl;
	cout<<"		  timing in appended in `ITimeFile` `STimeFile` respectively "<<endl;
	cout<<endl;
}


int main(int argc, char*argv[])
{
	bool bst=false,timer=false;
	clock_t insTime,lookupTime,startTime;
	string insertFile,lookupFile;
	string insertTimeFile,lookupTimeFile;
	Dictionary * dict;
	if(argc == 1)
	{
		help(argv[0]);
		return 2;
	}

	//TODO parse arguments

	if(bst)
		dict = new BSTree();
	else
		dict = new RBTree();

	 startTime = clock();
	//TODO insert
	 insTime = clock() - startTime;

	 startTime = clock();
	 	//TODO delete
	 lookupTime = clock() - startTime;

	 if(timer)
	 {
		//TODO append timing info
		//seconds  = ((float)lookupTime)/CLOCKS_PER_SEC);
		//seconds  = ((float)insTime)/CLOCKS_PER_SEC);
	 }
	return 0;
}




