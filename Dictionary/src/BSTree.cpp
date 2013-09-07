/*
 * BSTree.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#include "BSTree.h"

BSTree::BSTree()
{
	nill = new BSTreeNode();
		nill->val = NA;
		nill->left = NULL;
		nill->right= NULL;
		nill->p = NULL;

			root = nill;

}

BSTree::~BSTree()
{
	clear();
		delete nill;
}

void BSTree::insert(data val)
{
	BSTreeNode *x, *y, *z;
	z = new BSTreeNode();
		z->val = val;
		z->left = this->nill;
		z->right = this->nill;
		z->p = this->nill;
		y = this->nill;
			x = this->root;
			while(x != this->nill)
			{
				y = x;
				if(z->val < x->val)
					x = x ->left;
				else
					x = x->right;
			}
			z->p = y;
			if(y == this->nill)
					this->root = z;
				else
				{
					if(z->val < y->val)
						y->left = z;
					else
						y->right = z;
				}
				z->left = this->nill;
				z->right = this->nill;
		  }

}



bool BSTree::del(data val)
{
	//TODO
	return true;
}

bool BSTree::search(data val)
{
	//TODO
	return false;
}

void BSTree::clear()
{
	//TODO
}

void BSTree::display()
{
	//TODO
}

