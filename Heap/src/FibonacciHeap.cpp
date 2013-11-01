
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

bool FibonacciHeap::isEmpty()
{
  if (minPointer == NULL)
    return true;
  else
    return false;
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
  x->parent = NULL;
}


void FibonacciHeap::consolidate()
{
  FibonacciNode *temp  = minPointer, *x, *y;
  bool updateRootList = true;
  rankToAddress.clear();

  while(updateRootList)
  {
    y = temp;
    temp = temp->rightSibling;
    if(rankToAddress.count(y->degree) == 0)
      rankToAddress[y->degree] = y;
    else if(rankToAddress[y->degree] != y)
    {
      while(rankToAddress.count(y->degree) != 0)
      {
        x = (FibonacciNode*)rankToAddress[y->degree];

        if(y->key < x->key )
        {
          rankToAddress.erase(x->degree);
          if(temp == x)
            temp=temp->rightSibling;
          heapLink(y,x);

          if (rankToAddress.count(y->degree) != 0)
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

          if (rankToAddress.count(x->degree)!= 0)
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
  // Remove y from the root list
  y->leftSibling->rightSibling = y->rightSibling;
  y->rightSibling->leftSibling = y->leftSibling;

  // Make y a child of x
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
    x->child->rightSibling->leftSibling = y;
    x->child->rightSibling = y;
  }
  y->parent = x;
  x->degree++;

  //	cout << "Setting " << y->parent->key << " to be the parent of " << y->key << endl;
  y->mark = false;
}


void FibonacciHeap::cut(FibonacciNode* x, FibonacciNode* y)
{
  //	cout << "Inside cut()\n";
  x->rightSibling->leftSibling = x->leftSibling;
  x->leftSibling->rightSibling = x->rightSibling;
  y->degree--;

  // If x is the first child, update parent's(y) child pointer
  if(y->child == x)
    y->child = x->rightSibling;

  if(y->degree == 0)
    y->child = NULL;

  // Add x to the root list
  addToRoot(x);

  x->mark = false;
}


void FibonacciHeap::cascadingCut(FibonacciNode* y)
{
  FibonacciNode* z = y->parent;
  //	cout << "Inside cascadingCut()\n";

  if(z)
  {
    if(y->mark == false)
    {
      y->mark = true;
      //			cout<<"cascadingCut -> Mark true: "<< y->key << endl;
    }
    else
    {
      //			cout<<"cascadingCut -> Already marked true now being cut: " << y->key << endl;
      cut(y, z);
      cascadingCut(z);
    }
  }
}


void FibonacciHeap :: makeHeap()
{
  minPointer = NULL;
}


Location FibonacciHeap :: insertKey(Priority key)
{
  FibonacciNode* newNode = new FibonacciNode;

  // Duplicate key
  if(getLocation(key) != NULL)
    return NULL;

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


bool FibonacciHeap :: deleteKey(Location nodeAddress)
{
  decreaseKey(nodeAddress,MIN_PRIORITY);
  extractMin();
  return true;
}


Priority FibonacciHeap :: extractMin()
{
  FibonacciNode* extractedNode = minPointer;
  Priority retKey = 0;
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
        childPointer = nextChild;
      }
      while(childPointer);
    }

    // Delete the minimum node extracted
    extractedNode->leftSibling->rightSibling = extractedNode->rightSibling;
    extractedNode->rightSibling->leftSibling = extractedNode->leftSibling;

    if(extractedNode == extractedNode->rightSibling)
      minPointer = NULL;
    else
    {
      minPointer = extractedNode->rightSibling;
      consolidate();
    }
    nodes--;

    retKey = extractedNode->key;
    deleteLocation(extractedNode->key);
    delete extractedNode;
  }

  return retKey;
}


Priority FibonacciHeap :: findMin()
{
  return minPointer->key;
}


bool FibonacciHeap :: updateKey(Location nodeAddress, Priority newKey)
{
  FibonacciNode * node;

  if(nodeAddress == NULL)
    return false;
  node = (FibonacciNode *) nodeAddress;
  if (newKey < node->key) {
    return decreaseKey(nodeAddress,newKey);
  } else if (newKey > node->key) {
    if (node == minPointer) {
      bool val = increaseKey(nodeAddress,newKey);
      if(val) updateMin();
      return val;
    } else
      return increaseKey(nodeAddress,newKey);
  } else {
    return true;
  }
}


bool FibonacciHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
  FibonacciNode * node;
  FibonacciNode * minNode = NULL;
  FibonacciNode * x;
  Priority min = MAX_PRIORITY;
  if(nodeAddress == NULL) return false;

  node = (FibonacciNode *) nodeAddress;

  if (newKey < node->key)
  {
    std::cerr<<"new key is less than current key"<<endl;
    return false;
  }
  deleteLocation(node->key);
  node->key = newKey;

  x = node->child;
  if(x != NULL)
  {
    do
    {
      if(x->key<min)
      {
        min = x->key;
        minNode = x;
      }
      x = x->rightSibling;
    }while(x != node->child);

    if(min<newKey)
    {
      node->key = minNode->key;
      //recursive call
      increaseKey(minNode,newKey);
    }
  }
  setLocation(node,node->key);
  return true;
}


bool FibonacciHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
  FibonacciNode* x = (FibonacciNode*)nodeAddress;
  FibonacciNode* y;

  if(newKey > x->key)
  {
    std::cerr << "New key is greater than current key" << endl;
    return false;
  }

  if (getLocation(newKey)!= NULL)
  {
    std::cerr << "New key is already present" << endl;
    return false;
  }

  deleteLocation(x->key);
  x->key = newKey;
  setLocation(x, x->key);
  y = x->parent;

  if((y != NULL) && (x->key < y->key))
  {
    //	  cout << "decreaseKey -> B4: Value of mark(" << y->key << "): " << y->mark << endl;
    cut(x, y);
    cascadingCut(y);
    //    cout << "decreaseKey -> AR: Value of mark(" << y->key << "): " << y->mark << endl;
  }

  if(x->key < minPointer->key)
    minPointer = x;

  return true;
}

void FibonacciHeap::updateMin()
{
  FibonacciNode * minNode = NULL;
  FibonacciNode * x = minPointer;
  Priority min =MAX_PRIORITY;
  do
  {
    if (x->key < min)
    {
      min = x->key;
      minNode=x;
    }
    x = x->leftSibling;
  }while (x != minPointer);
  minPointer = minNode;
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
  outFile<<"digraph FibonacciHeap {"<<endl;
  if(root)
  {
    do
    {
      do
      {
        printDOT(root,outFile);
        outFile << root->key <<" -> " <<root->leftSibling->key
            <<" [color=red,dir=both];"
            << endl;
        root=root->leftSibling;
      }
      while(root != minPointer);
    }
    while(root != minPointer);
  }
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
  out<<" "<<root->key<<" -> {";
  temp = ptr;

  do{
    out<<ptr->key<<" ; ";
    ptr = ptr->rightSibling;
  }while(ptr!=temp);
  out<<"}"<<endl;

  ptr = root->child;
  temp =ptr;
  do{
    printDOT(ptr,out);
    ptr = ptr->rightSibling;
  }while(ptr!=temp);
}
