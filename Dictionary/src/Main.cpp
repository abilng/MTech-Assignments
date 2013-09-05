/*
 * Main.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abilng
 */

//#include "Dictionary.h"
//#include "BSTree.h"
//#include "RBTree.h"
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
	if(argc == 1) help(argv[0]);

	//TODO

	return 0;
}




