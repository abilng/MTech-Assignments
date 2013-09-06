/*
 * RBTree.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abilng
 */

#include "RBTree.h"
#include <cstdlib>
#include <iostream>


RBTree::RBTree()
{

	nill = new RBTreeNode();
	nill->val = NA;
	nill->left = NULL;
	nill->right= NULL;
	nill-> colour = BLACK;
	nill->p = NULL;

	root = NULL;
}

RBTree::~RBTree()
{
	clear();
	delete nill;
}


void RBTree::insert(data val)
{
	//TODO
}

bool RBTree::del(data val)
{
	//TODO
	return true;
}

bool RBTree::search(data val)
{
	//TODO
	return false;
}

void RBTree::clear()
{
	//TODO
}

void RBTree::display()
{
	//TODO
}


inline RBTreeNode * RBTree::lookup(data val)
{
	return lookup(val,root);
}

RBTreeNode * RBTree::lookup(data val,RBTreeNode * ptr)
{
	if(ptr == NULL) return NULL;
	while(ptr!= this->nill)
	{
		if(ptr->val > val)
			ptr=ptr->left;
		else if(ptr->val < val)
			ptr=ptr->right;
		else
			return ptr;
	}
	return NULL;
}

void RBTree::leftRotate(RBTreeNode * x)
{
	RBTreeNode *y = x->right;
  x->right=y->left;
  if(y->left!=this->nill)
  	(y->left)->p=x;

  y->p=x->p;
  if(x->p==this->nill)
  	this->root=y;
  else if(x==(x->p)->left)
  	(x->p)->left=y;
  else
  	(x->p)->right=y;

  y->left=x;
  x->p=y;
}

void RBTree::rightRotate(RBTreeNode * y)
{
	RBTreeNode *x = y->left;

	y->left=x->right;
  if(x->right!=this->nill)
  	(x->right)->p=y;

  x->p=y->p;
  if(y->p==this->nill)
  	this->root=x;
  else if(y==(y->p)->left)
  	(y->p)->left=x;
  else
  	(y->p)->right=x;

  x->right=y;
  y->p=x;
}
/**
 * Replaces sub tree rooted at u with sub tree
 * rooted at v
 *
 */
void RBTree::transplant(RBTreeNode * u,RBTreeNode * v)
{
	if(u->p == nill)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (v != nill)
		v->p = u->p;
}

void RBTree::del(RBTreeNode * delNode)
{

	//Node which take delNode's position
	RBTreeNode *xNode;

	//Node which is deleted or moved within the tree
	RBTreeNode *yNode;

	yNode= delNode;
	colourType yOrginalColour = yNode->colour;

	if(delNode->left == nill)
	{
		xNode = delNode->right;
		transplant(delNode,delNode->right);
	}
	else if(delNode->right == nill)
	{
		xNode= delNode->left;
		transplant(delNode,delNode->left);
	}
	else
	{
		yNode = minimum(delNode->right); //find successor
		yOrginalColour = yNode->colour;
		xNode = yNode->right;

		if (yNode->p == delNode)
		{
			xNode->p = yNode;
		}
		else
		{
			transplant(yNode,yNode->right);
			yNode->right = delNode->right;
			yNode->right->p = yNode;
		}
		transplant(delNode,yNode);
		yNode->left = delNode->left;
		yNode->left->p = yNode;
		yNode->colour = delNode->colour;
	}

	if (yOrginalColour == BLACK)
		deleteFixup(xNode);
}
void RBTree::deleteFixup(RBTreeNode * x)
{

}


RBTreeNode * RBTree::minimum()
{
	return minimum(root);
}
RBTreeNode * RBTree::minimum(RBTreeNode * ptr)
{
	while(ptr->left != nill)
		ptr = ptr->left;
	return ptr;
}

