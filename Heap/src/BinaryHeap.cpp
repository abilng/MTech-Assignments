
#include "BinaryHeap.h"

BinaryHeap :: BinaryHeap()
{
	root = NULL;
	lastElement = NULL;
}


BinaryHeap :: ~BinaryHeap()
{

}


void BinaryHeap :: makeHeap()
{

}


Location BinaryHeap :: insertKey(Priority key)
{
    BinaryNode *z,*x=new BinaryNode();
    x->leftChild=x->rightChild=NULL;
    x->leftSibling=x->rightSibling=NULL;
    if(root==NULL){
        root=x;
        lastElement=x;
        x->parent=NULL;
    }
    else{
        if(lastElement->parent->leftChild==lastElement)
            {
                lastElement->parent->rightChild=x;
                x->parent=lastElement->parent;
                x->leftSibling=lastElement;
                lastElement->rightSibling=x;
            }
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
	return x;
}


int BinaryHeap :: deleteKey(Location nodeAddress)
{
    BinaryNode *x,*z,*y=(BinaryNode*)nodeAddress;
    Priority datakey =lastElement->key;
    x=lastElement;
    if(root==NULL || y==NULL )
         return -1;
    else if(y==root)
        root=lastElement=NULL;
    else if(x->parent->rightChild==x){
        x->parent->rightChild=NULL;
        lastElement=x->parent->leftChild;
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
            else
              lastElement=x->parent->leftSibling->rightChild;
        }
    }
    delete x;
    if(y->key < datakey)
        increaseKey(y,datakey);
    else if(y->key > datakey)
        decreaseKey(y,datakey);
	return 0;
}



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


Priority BinaryHeap :: findMin()
{
    Priority x;
    if(root!=NULL)
    x=root->key;
	return x;
}


int BinaryHeap :: increaseKey(Location nodeAddress, Priority newKey)
{
    BinaryNode *y=(BinaryNode*)nodeAddress;
    if(y==NULL || (newKey <= y->key))
    return -1;
    else{
        y->key=newKey;
            if(y->leftChild!=NULL && y->leftChild->key < newKey){
                y->key=y->leftChild->key ;
                increaseKey(y->leftChild,newKey);
            }
            else if(y->rightChild!=NULL && (y->rightChild->key < newKey)){
                y->key=y->rightChild->key ;
                increaseKey(y->rightChild,newKey);
            }
    }
}


int BinaryHeap :: decreaseKey(Location nodeAddress, Priority newKey)
{
    BinaryNode *y=(BinaryNode*)nodeAddress;
    if(y==NULL || (newKey >= y->key))
    return -1;
    else{
        y->key=newKey;
            if(y->parent!=NULL && y->parent->key > newKey){
                y->key=y->parent->key;
                decreaseKey(y->parent,newKey);
            }
        }
}


void BinaryHeap :: displayHeap(char* fileName)
{

}
