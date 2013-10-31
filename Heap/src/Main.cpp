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

int getInt();
void help();
void parseArgs(int argc, char*argv[]);


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
    cout<<"3:UPDATE KEY"<<endl;
    cout<<"4:DISPLAY"<<endl;
    cout<<"5:EXTRACT MIN"<<endl;
    cout<<"6:FIND MIN"<<endl;
    cout<<"Any other key to exit"<<endl;
    cout<<"Enter the choice: "<<flush;
    cin>>option;
    switch(option)
    {
      case '1':
        cout<<"Enter the key to Insert:"<<flush;
        key=getInt();
        if(heap->getLocation(key) != NULL)
        {
          cerr<<"Key is already present"<<endl;
          break;
        }
        heap->insertKey(key);
        break;

      case '2':
        cout<<"Enter the key to Delete:"<<flush;
        key=getInt();
        loc = heap->getLocation(key);
        if(loc==NULL)
          cerr<<"Key Not Found"<<endl;
        else if(heap->deleteKey(loc))
          cout<<"Deleted"<<endl;
        else
          cerr<<"Delete Failed"<<endl;
        break;

      case '3':
        cout<<"Enter the key to Update:"<<flush;
        key=getInt();
        loc = heap->getLocation(key);
        if(loc == NULL)
        {
          cerr<<"Key Not Found"<<endl;
          break;
        }
        cout<<"Enter the new key:"<<flush;
        newkey=getInt();

        if(heap->getLocation(newkey) != NULL)
        {
          cerr<<"Key is already present"<<endl;
          break;
        }
        if(heap->updateKey(loc,newkey))
          cout<<"Heap Updated"<<endl;
        else
          cerr<<"Updation Failed"<<endl;
        break;

      case '4':
        cout<<"Enter Filename [*.gv]: "<<flush;
        cin>>filename;
        heap->displayHeap(filename);
        cout<<endl;
        break;

      case '5':
        if(!heap->isEmpty())
          cout<<"Extracted :"<<heap->extractMin()<<endl;
        else
          cerr<<"Heap Empty";
        break;
      case '6':
        if(!heap->isEmpty())
          cout<<"Minimum is :"<<heap->findMin()<<endl;
        else
          cerr<<"Heap Empty";
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
    //TODO for debug
    heap->displayHeap("out.gv");
    system("dot -Tpng out.gv -o out.png");

    //clear cin
    //cin.clear();
    //cin.ignore(10000,'\n');

  }while(true);
  return 0;
}



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
/*
 * Input: argc and argv
 * Output: N/A
 * Description: parse cmd line arguments and
 *        set arg structure.
 */
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

int getInt()
{
  int input;
  do
  {
    if (!(cin >> input)) {
      cout << "Please enter numbers only." << endl;
      cin.clear();
      cin.ignore(10000,'\n');
      cout << "Try Again:" << endl;
    }
    else
      break;
  }while(true);
  return input;
}
