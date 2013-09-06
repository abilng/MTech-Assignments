/*
 * Main.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abilng
 */

#include "Dictionary.h"
#include "BSTree.h"
#include "RBTree.h"
#include <iostream>
#include <string>
#include <cstdlib>

#define OPTIONPREFIX '-'

using namespace std;

struct Args
{
		bool bst;
		bool timer;
		char * prgName;
		char * insertFile;
		char * lookupFile;
		char * insertTimeFile;
		char * lookupTimeFile;
}args;

void help()
{
	cout<<"Usage: "<<args.prgName<<" [-bst][-t] insertFile searchFile";
	cout<<" [ITimeFile] [STimeFile] "<<endl;

	cout<<endl;
	cout<<"-bst		Use Binary Search Tree"<<endl;
	cout<<"		  if this flag is not present,";
	cout<<" program will use Red Black Tree"<<endl;
	cout<<"-t		Calculate time for insert and lookup"<<endl;
	cout<<"		  timing in appended in `ITimeFile` `STimeFile` respectively "<<endl;
	cout<<endl;
	exit(3);
}

void parseArgs(int argc, char*argv[])
{
	int noofargs = 3;
	int fileStartIndex = 1;
	string currentArg;

	args.prgName = argv[0];

	for (int i = 1; i < argc && i<3; ++i)
	{
		currentArg = argv[i];
		if(currentArg[0] == OPTIONPREFIX)
		{
			if(currentArg=="-bst")
			{
				if(i!= 1) help();
				noofargs++;
				fileStartIndex++;
				args.bst = true;
			}
			else if(currentArg=="-t")
			{
				if( i!= 1 && i!=2 ) help();
				noofargs+=3;
				fileStartIndex++;
				args.timer = true;

			}
			else
			{
				cerr<<"Unknown Option"<<endl;
				help();
			}
		}
	}
	if(argc != noofargs) help();
	args.insertFile = argv[fileStartIndex++];
	args.lookupFile = argv[fileStartIndex++];
	if(!args.timer) return;
	args.insertTimeFile = argv[fileStartIndex++];
	args.lookupTimeFile = argv[fileStartIndex++];

}

int main(int argc, char*argv[])
{

	Dictionary * dict;
	parseArgs(argc,argv);

	if(args.bst)
		dict = new BSTree();
	else
		dict = new RBTree();

	dict->populateDictionary(args.insertFile,
			args.insertTimeFile,args.timer);
	dict->lookupDictionary(args.lookupFile,
			args.lookupTimeFile,args.timer);

	return 0;
}




