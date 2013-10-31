
#include "FibonacciHeap.h"

using namespace std;

FibonacciHeap::FibonacciHeap()
{
  minPointer = NULL;
  nodes = 0;
}


FibonacciHeap::~FibonacciHeap()
{

}


void FibonacciHeap::addToRoot(FibonacciNode* x)
{
  if(!minPointer)
    {
      minPointer = x;
      x->leftSibling = x;
      x->rightSibling = x;
    }
  else
    {
      x->rightSibling = minPointer->rightSibling;
      x->leftSibling = minPointer;
      minPointer->rightSibling = x;
      x->rightSibling->leftSibling = x;
    }
}


void FibonacciHeap::consolidate()
{
  FibonacciNode *temp  = minPointer, *x,*y;
  bool updateRootList = true;

  while(updateRootList)
   {
      y = temp;
      temp = temp->rightSibling;
      if(rankToAddress[y->degree] == NULL)
      {
    	  rankToAddress[y->degree] = y;
      }
      else if(rankToAddress[y->degree] != y)
      {
    	  while(rankToAddress[y->degree] != NULL)
    	  {
    		  x = (FibonacciNode *)rankToAddress[y->degree];

    		  if(y->key < x->key )
    		  {
    			  rankToAddress.erase(x->degree);
    			  if(temp == x)
    				  temp=temp->rightSibling;
    			  heapLink(y,x);

    			  if (rankToAddress[y->degree] != NULL)
    				  continue;
    			  else
    			  {
    				  rankToAddress[y->degree] = y;
    			  	  break;
    			  }
    		  }
    		  else
    		  {
    			  rankToAddress.erase(x->degree);
    			  if(temp == y)
    			     temp = temp->rightSibling;
    			  heapLink(x,y);

    			  if (rankToAddress[x->degree]!= NULL)
    			  {
    				  y = x;
    				  continue;
    			  }
    			  else
    			  {
    				  rankToAddress[x->degree] = x;
       			  	  break;
    			  }
    		 }
	    }
	}
    else
    	updateRootList = false;
    }
  x = temp;
  do
  {
	  if(minPointer->key > temp->key)
		  minPointer = temp;
	  temp=temp->leftSibling;

  }while(temp!=x);

}


void FibonacciHeap::heapLink(FibonacciNode* x, FibonacciNode* y)
{
  y->leftSibling->rightSibling = y->rightSibling;
  y->rightSibling->leftSibling = y->leftSibling;
  if(x->degree == 0)
    {
      x->child = y;
      y->leftSibling = y;
      y->rightSibling = y;
    }
  else
    {
      y->leftSibling = x->child;
      y->rightSibling = x->child->rightSibling;
      x->child->rightSibling = y;
    }
  y->parent = x;
  x->degree++;
  y->mark = false;
}


void FibonacciHeap::cut(FibonacciNode* x, FibonacciNode* y)
{
  x->rightSibling->leftSibling = x->leftSibling;
  x->leftSibling->rightSibling = x->rightSibling;
  y->degree--;

  // If x is the first child, update parent's(y) child pointer
  if(y->child == x)
    y->child = x->rightSibling;

  // Add x to the root list
  addToRoot(x);

  x->parent = NULL;
  x->mark = false;
}


void FibonacciHeap::cascadingCut(FibonacciNode* y)
{
  FibonacciNode* z = y->parent;
  if(z)
    {
      if(y->mark == false)
	y->mark = true;
      else
	{
	  cut(y, z);
	  cascadingCut(z);
	}
    }
}


void FibonacciHeap :: makeHeap()
{

}


Location FibonacciHeap :: insertKey(Priority key)
{
  FibonacciNode* newNode = new FibonacciNode;
  newNode->degree = 0;
  newNode->parent = NULL;
  newNode->child = NULL;
  newNode->mark = false;
  newNode->key = key;
  setLocation(newNode, key);

  addToRoot(newNode);
  if(newNode->key < minPointer->key)
    minPointer = newNode;
  nodes++;

  return newNode;
}


int FibonacciHeap :: deleteKey(Location nodeAddress)
{
  decreaseKey(nodeAddress, -1);
  extractMin();
  return 0;
}


Priority FibonacciHeap :: extractMin()
{
	FibonacciNode* extractedNode = minPointer;
	if(extractedNode == extractedNode->rightSibling)
		minPointer = NULL;
	else
		minPointer = extractedNode->rightSibling;

	if(extractedNode)
    {
		FibonacciNode *childPointer, *nextChild;
		childPointer = extractedNode->child;
		nextChild = childPointer;

		// Cut and add the children to the root list
		if(childPointer)
		{
			childPointer->leftSibling->rightSibling = NULL;
			do
			{
				nextChild = childPointer->rightSibling;
				addToRoot(childPointer);
				childPointer->parent = NULL;
				childPointer = nextChild;
			}
			while(childPointer);
		}

		// Delete the minimum node extracted
		extractedNode->leftSibling->rightSibling = extractedNode->rightSibling;
		extractedNode->rightSibling->leftSibling = extractedNode->leftSibling;

		consolidate();
		nodes--;

		return extractedNode->key;
		delete extractedNode;
    }

	return 0;
}


Priority FibonacciHeap :: findMin()
{
  return minPointer->key;
}


bool FibonacciHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
  return true;
}


bool FibonacciHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
  FibonacciNode* x = (FibonacciNode*)nodeAddress;
  FibonacciNode* y;

  if(newKey > x->key)
    return -1;
  x->key = newKey;
  y = x->parent;

  if((y != NULL) && (x->key < y->key))
    {
      cut(x, y);
      cascadingCut(y);
    }

  if(x->key < minPointer->key)
    minPointer = x;

  return true;
}


bool FibonacciHeap :: displayHeap(char const* fileName)
{
  fstream outFile;
  char errorMsg[100];
  outFile.open(fileName,fstream::out);
  if (!outFile.is_open())
    {
      sprintf(errorMsg,"Error while opening %s:",fileName);
      perror(errorMsg);
      return false;
    }

  FibonacciNode *root = minPointer;

  outFile<<"/* Generated by Heap Program */"<<endl;
  outFile<<"graph FibonacciHeap {"<<endl;

  do
    {
      printDOT(root,outFile);
      //if(root->leftSibling !=NULL)
      outFile << root->key <<" -- " <<root->leftSibling->key <<" [color=red];" << endl;
      root=root->leftSibling;
    }
  while(root != minPointer);

  outFile<<"}"<<endl;

  outFile.close();
  return true;
}


void FibonacciHeap :: printDOT(FibonacciNode *root, fstream& out)
{
  FibonacciNode *ptr,*temp;
  if(root == NULL)
    return;
  ptr = root->child;
  if(ptr == NULL)
    return;
  //printing children
  out<<" "<<root->key<<" -- {";
  temp = ptr;
  do{
    out<<ptr->key<<" ; ";
    ptr = ptr->leftSibling;
  }while(ptr!=temp);
  out<<"}"<<endl;

  ptr = root->child;
  temp =ptr;
  do{
    printDOT(ptr,out);
    ptr = ptr->leftSibling;
  }while(ptr!=temp);
}

/*
int main()
{
	Heap* heap = new FibonacciHeap();
	Location nodeAddress;

	heap->insertKey(5);
	nodeAddress = heap->insertKey(15);
	heap->insertKey(2);
	heap->insertKey(20);
	heap->insertKey(60);
	heap->insertKey(1);
	heap->insertKey(10);
	heap->decreaseKey(nodeAddress, 14);
	//heap->deleteKey(nodeAddress);
	cout<< "The extracted node is "<< heap->extractMin() <<endl;
	cout << "Minimum: " << heap->findMin() << endl;
	heap->displayHeap("out.gv");
	system("dot -Tpng out.gv > out.png");
	system("display out.png");
	return 0;
  }
*/
