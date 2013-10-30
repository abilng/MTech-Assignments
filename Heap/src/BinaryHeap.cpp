
#include "BinaryHeap.h"
#include <fstream>
// initialize the variables
BinaryHeap :: BinaryHeap()
{
  root = NULL;
  lastElement = NULL;
}

// clear the memory
BinaryHeap :: ~BinaryHeap()
{
  clear(root);
}

// make a new heap
void BinaryHeap :: makeHeap()
{
  if(root!=NULL)
    clear(root);
  root = NULL;
  lastElement = NULL;
}

// insert the given key into the heap
Location BinaryHeap :: insertKey(Priority key)
{
  BinaryNode *z,*x=new BinaryNode();
  x->key=key;
  setLocation(x,x->key);
  // make the fields null of new node
  x->leftChild=x->rightChild=NULL;
  x->leftSibling=x->rightSibling=NULL;

  //check root is null or not??
  if(root==NULL){
    root=x;
    lastElement=x;
    x->parent=NULL;
  }
  else{
    if(lastElement==root) // 2nd element inserted in the heap
      {
	root->leftChild=x;
	x->parent=root;
      } //add a node in the right child of a node
    else if(lastElement->parent->leftChild==lastElement)
      {
	lastElement->parent->rightChild=x;
	x->parent=lastElement->parent;
	x->leftSibling=lastElement;
	lastElement->rightSibling=x;
      }
    //add a node in the left child of a node
    else if(lastElement->parent->rightChild==lastElement){
      if(lastElement->parent->rightSibling==NULL)
	{
	  z=lastElement;
	  while(z->leftSibling!=NULL)
	    z=z->leftSibling;
	  z->leftChild=x;
	  x->parent=z;
	}
      else
	{
	  lastElement->parent->rightSibling->leftChild=x;
	  x->parent=lastElement->parent->rightSibling;
	  x->leftSibling=lastElement;
	  lastElement->rightSibling=x;
	}
    }
  }
  lastElement=x;
  Priority data;
  //heapify the heap
  while(x!=NULL){
    if(x!=root && x->parent->key > x->key )
      {
	data=x->key;
	x->key=x->parent->key;
	setLocation(x,x->key);
	x->parent->key=data;
	setLocation(x->parent,x->parent->key);
	x=x->parent;
      }
    else
      x=NULL;
  }
  return x;
}

// delete the given node from the heap
int BinaryHeap :: deleteKey(Location nodeAddress)
{
  BinaryNode *x,*z,*y=(BinaryNode*)nodeAddress;
  Priority datakey =lastElement->key;
  x=lastElement;

  //updation of pointers
  if(root==NULL || y==NULL )
    return -1;
  else if(y==root && y->leftChild==NULL && y->rightChild==NULL)
    root=lastElement=NULL;
  else if(x->parent->rightChild==x){
    x->parent->rightChild=NULL;
    lastElement=x->parent->leftChild;
    x->leftSibling->rightSibling=NULL;
  }
  else if(x->parent->leftChild==x)
    {
      x->parent->leftChild=NULL;
      if(x->parent==root)
	lastElement=root;
      else
	{
	  if(x->parent->leftSibling==NULL)
	    {
	      z=x->parent;
	      while(z->rightSibling!=NULL)
		{
		  z=z->rightSibling;
		}
	      lastElement=z;
	    }
	  else{
	    lastElement=x->parent->leftSibling->rightChild;
	    x->parent->leftSibling->rightChild->rightSibling=NULL;
	  }
	}

    }
  keyToAddress.erase(x->key);
  delete x; //delete the node
  // heapify the given heap
  if(y->key < datakey)
    increaseKey(y,datakey);
  else if(y->key > datakey)
    decreaseKey(y,datakey);
  return 0;
}


// delete the node which contain the minimum value and return the minimum value
Priority BinaryHeap :: extractMin()
{
  Priority datakey =root->key;
  if(root==NULL)
    {
      cout<<"INVALID OPERATION\n";
      return -1;
    }
  else{
    deleteKey(root);
  }
  return datakey;
}

// return the minimum value of the heap
Priority BinaryHeap :: findMin()
{
  Priority x=0;
  if(root!=NULL) //check root is null or not ??
    x=root->key;
  return x;
}

// increase the key of given node by the given value
bool BinaryHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
  Priority data=newKey;
  BinaryNode *x,*y=(BinaryNode*)nodeAddress;
  x=y;
  if(y==NULL || (newKey <= y->key))  //check for a invalid input
    return -1;
  else{
    //update the given node by that key
    y->key=newKey;
    setLocation(y,y->key);
    //check which key has to be change right or left ??
    if(y->leftChild!=NULL && y->leftChild->key < newKey){
      data=y->leftChild->key;
      x=y->leftChild;
    }
    if(y->rightChild!=NULL && (y->rightChild->key < newKey)){
      if(data >y->rightChild->key)
	{
	  data=y->rightChild->key;
	  x=y->rightChild;
	}
    }
    //modify the heap according to respective changes
    if(y->leftChild==x){
      y->key=y->leftChild->key ;
      setLocation(y,y->key);
      increaseKey(y->leftChild,newKey);
    }
    else if(y->rightChild==x){
      y->key=y->rightChild->key ;
      setLocation(y,y->key);
      increaseKey(y->rightChild,newKey);
    }
  }
  return 0;
}

// decrease the given key by a given value
bool BinaryHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
  BinaryNode *y=(BinaryNode*)nodeAddress;
  if(y==NULL || (newKey >= y->key)) //check for a invalid input
    return false;
  else{
    y->key=newKey; //change the key in the heap
    setLocation(y,y->key);
    // update the parent if required
    if(y->parent!=NULL && y->parent->key > newKey){
      y->key=y->parent->key;
      setLocation(y,y->key);
      // recursive call on the parent to trill up the key upto the root
      decreaseKey(y->parent,newKey);
    }
  }
  return true;
}

//function to write the nodes to the output file..
bool BinaryHeap :: displayHeap(char const* fileName)
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

  outFile<<"/* Generated by Heap Program */"<<endl;
  outFile<<"digraph binaryHeap {"<<endl;
  printDOT(root,outFile);
  outFile<<"}"<<endl;

  outFile.close();
  return true;
}
void BinaryHeap::printDOT(BinaryNode *root,fstream& out)
{
  if(root == NULL)
    return;
  if(root->leftChild == NULL && root->rightChild == NULL)
    out<<" "<<root->key<<" ;"<<endl;
  if(root->leftChild != NULL)
    out<<" "<<root->key<<" -> "<<root->leftChild->key<<" ;"<<endl;
  if(root->rightChild != NULL)
    out<<" "<<root->key<<" -> "<<root->rightChild->key<<" ;"<<endl;
  printDOT(root->leftChild,out);
  printDOT(root->rightChild,out);
}

// clear all the present nodes in the tree
void BinaryHeap::clear(BinaryNode* listRoot)
{
  if(listRoot == NULL) return;
  BinaryNode* ptr = listRoot;

  clear(ptr->leftChild);     //call on the left child
  clear(ptr->rightChild);     //call on the right child
  delete ptr;

}
