#include <iostream>
#include <cstdlib>
#include "Heap.h"
#include "BinaryHeap.h"
#include "FibonacciHeap.h"
#include "BinomialHeap.h"

#define OPTIONPREFIX '-'


using namespace std;


enum Heaptype {binary,binomial,fib};

struct Args
{
		Heaptype type;
		char * prgName;
}args;


/*
 * Input: N/A
 * Output: Displays help
 * Description: N/A
 */
void help()
{
	cout<<"Usage: "<<args.prgName<<" <heap type> "<<endl;
	cout<<endl;
	cout<<"valid `heap type` are:"<<endl;
	cout<<"\t-binary        Use Binary Heap"<<endl;
	cout<<"\t-binomial      Use Binomial Heap"<<endl;
	cout<<"\t-fib           Use Fibonacci Heap"<<endl;
	cout<<endl;
	exit(3);
}

void parseArgs(int argc, char*argv[])
{
	string option;
	args.prgName = argv[0];

	if(argc != 2)
	{
		cerr<<"Unknown Option"<<endl;
		help();
	}

	option = argv[1];
	if(option[0] == OPTIONPREFIX)
	{
		if(option=="-binary")
		{
			args.type = binary;
		}
		else if(option=="-binomial")
		{
			args.type = binomial;
		}
		else if(option=="-fib")
		{
			args.type = fib;
		}
		else
		{
			cerr<<"Unknown Option"<<endl;
			help();
		}
	}
	else
	{
		cerr<<"Unknown Option"<<endl;
		help();
	}


}



int main(int argc, char*argv[])
{

	parseArgs(argc,argv);

	char option;
	Heap * heap;
	Location loc;
	Priority key,newkey;
	char filename[100];
	char ch;

	switch (args.type) {
		case binary:
			heap = new BinaryHeap();
			break;
		case fib:
			heap = new FibonacciHeap();
			break;
		case binomial:
			heap = new BinomialHeap();
			break;
	}



	do {
		cout<<"\n===  MENU  ==="<<endl;
		cout<<"1:INSERT"<<endl;
		cout<<"2:DELETE"<<endl;
		cout<<"3:DECREASE KEY"<<endl;
		cout<<"4:INCREASE KEY"<<endl;
		cout<<"5:DISPLAY"<<endl;
		cout<<"6:EXTRACT MIN"<<endl;
		cout<<"7:FIND MIN"<<endl;
		cout<<"Any other key to exit"<<endl;
		cout<<"Enter the choice: ";
		cin>>option;
		switch(option)
		{
			case '1':
				cout<<"Enter the key to Insert:"<<flush;
				cin>>key;
				heap->insertKey(key);
				break;

			case '2':
				cout<<"Enter the key to Delete:"<<flush;
				cin>>key;
				loc = heap->getLocation(key);
				if(loc!=NULL && heap->deleteKey(loc))
					cout<<"Deleted"<<endl;
				else
					cout<<"Deleted Failed"<<endl;
				break;

			case '3':
				cout<<"Enter the key to Decrease:"<<flush;
				cin>>key;
				loc = heap->getLocation(key);
				if(loc == NULL)
				{
					cerr<<"Key Not Found"<<endl;
					break;
				}
				cout<<"Enter the new key:"<<flush;
				cin>>newkey;

				if(heap->getLocation(newkey) != NULL)
				{
					cerr<<"Key is already present"<<endl;
					break;
				}
				if(heap->decreaseKey(loc,newkey))
					cout<<"Heap Updated"<<endl;
				else
					cout<<"Updation Failed"<<endl;
				break;

			case '4':
				cout<<"Enter the key to Increase:"<<flush;
				cin>>key;
				loc = heap->getLocation(key);
				if(loc == NULL)
				{
					cerr<<"Key Not Found"<<endl;
					break;
				}
				cout<<"Enter the new key:"<<flush;
				cin>>newkey;

				if(heap->getLocation(newkey) != NULL)
				{
					cerr<<"Key is already present"<<endl;
					break;
				}
				if(heap->increaseKey(loc,newkey))
					cout<<"Heap Updated"<<endl;
				else
					cout<<"Updation Failed"<<endl;
				break;

			case '5':
				cout<<"Enter Filename [*.gv]: "<<flush;
				cin>>filename;
				heap->displayHeap(filename);
				cout<<endl;
				break;

			case '6':
				cout<<"Extracted :"<<heap->extractMin()<<endl;
				break;
			case '7':
				cout<<"Minimum is :"<<heap->findMin()<<endl;
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


	return 0;

}

