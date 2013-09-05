/*
 * RBTree.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abilng
 */

#include "RBTree.h"
#include <cstdlib>


RBTree::RBTree()
{
	head = NULL;
	nill = new RBTreeNode();

	nill->val = NA;
	nill->lchild = NULL;
	nill->rchild = NULL;
	nill-> c = BLACK;

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
