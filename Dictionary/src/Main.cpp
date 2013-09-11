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
	cout<<"Usage: "<<args.prgName<<" [-bst] insertFile searchFile";
	cout<<"[-t] [ITimeFile] [STimeFile] "<<endl;

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

	for (int i = 1; i < argc && i<5; ++i)
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
				if( i!= 3 && i!=4 ) help();
				noofargs+=3;
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
	fileStartIndex++;
	args.insertTimeFile = argv[fileStartIndex++];
	args.lookupTimeFile = argv[fileStartIndex++];
}

int main(int argc, char*argv[])
{

	Dictionary *dict;
	parseArgs(argc,argv);

	if(args.bst)
		dict = new BSTree();
	else
		dict = new RBTree();

	dict->populateDictionary(args.insertFile, args.insertTimeFile,args.timer);
	/*
	cout <<"\nDeleted 2: "; dict->del(2); dict->display(); cout<< endl;
	cout <<"Deleted 5: "; dict->del(5); dict->display(); cout<< endl;
	cout <<"Deleted 3: "; dict->del(3); dict->display(); cout<< endl;
	cout <<"Deleted 7: "; dict->del(7); dict->display(); cout<< endl;
	cout <<"Deleted 8: "; dict->del(8); dict->display(); cout<< endl;
	cout <<"Deleted 9: "; dict->del(9); dict->display(); cout<< endl;
	 */
	dict->lookupDictionary(args.lookupFile, args.lookupTimeFile,args.timer);



	char option,ch;
	int element;

	do {
		cout<<"===  MENU  ==="<<endl;
		cout<<"1:INSERT"<<endl;
		cout<<"2:DELETE"<<endl;
		cout<<"3:SEARCH"<<endl;
		cout<<"4:DISPLAY"<<endl;
		cout<<"5:CLEAR"<<endl;
		cout<<"Any other key to exit"<<endl;
		cout<<"Enter the choice:";
		cin>>option;
		switch(option)
		{
			case '1':
				cout<<"Enter the element to Insert:"<<flush;
				cin>>element;
				dict->insert(element);
				break;
			case '2':
				cout<<"Enter the element to Delete:"<<flush;
				cin>>element;
				if(dict->del(element))
					cout<<"Deleted"<<endl;
				else
					cout<<"Deleted Failed"<<endl;
				break;
			case '3':
				cout<<"Enter the element to Search:"<<flush;
				cin>>element;
				if(dict->search(element))
					cout<<"Found"<<endl;
				else
					cout<<"Not Found"<<endl;
				break;
			case '4':
				cout<<"Elements are:"<<endl;
				dict->display();
				cout<<endl;
				break;
			case '5':
				dict->clear();
				cout<<"ADT Cleared"<<endl;
				break;
			default:
				cout<<"Exit program ?[Y/N]:";
				cin>>ch;
				if(ch=='Y' || ch == 'y')
				{
					cout<<"Bye.."<<endl;
					return 0;
				}
				break;
		}
	}while(true);
}




