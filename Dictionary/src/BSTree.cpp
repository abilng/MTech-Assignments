/*
 * BSTree.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#include "BSTree.h"

BSTree::BSTree()
{
	root = NULL;

}

BSTree::~BSTree()
{
	clear();
}

void BSTree::insert(data val)
{
	BSTreeNode *x, *y, *z;
	z = new BSTreeNode();
	z->val = val;
	z->left = NULL;
	z->right = NULL;
	z->p = NULL;
	y = NULL;
	x = this->root;
	while(x != NULL)
	{
		y = x;
		if(z->val < x->val)
			x = x ->left;
		else
			x = x->right;
	}
	z->p = y;
	if(y == NULL)
		this->root = z;
	else
	{
		if(z->val < y->val)
			y->left = z;
		else
			y->right = z;
	}
	z->left = NULL;
	z->right = NULL;
}

inline BSTreeNode * BSTree::lookup(data val)
{
	return lookup(val,root);
}


BSTreeNode * BSTree::lookup(data val,BSTreeNode* ptr)
{
	while(ptr!= NULL)
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

void BSTree::del(BSTreeNode * z)
{
	BSTreeNode * y;
	if(z->left == NULL)
		transplant(z,z->right);
	else if(z->right == NULL)
		transplant(z,z->left);
	else
	{
		y = minimum(z->right);
		if(y->p != z)
		{
			transplant(y,y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(z,y);
		y->left = z->left;
		y->left->p = y;
	}

}

bool BSTree::del(data val)
{
	BSTreeNode * delnode = lookup(val);
	if(delnode == NULL)
		return false;
	del(delnode);
	return true;
}

bool BSTree::search(data val)
{
	if(lookup(val) != NULL)
		return true;
	return false;
}

void BSTree::clear()
{
	//TODO
}

void BSTree::display()
{
 traverse(root);
}


BSTreeNode * BSTree::minimum()
{
	return minimum(root);
}
BSTreeNode * BSTree::minimum(BSTreeNode * ptr)
{
	while(ptr->left != NULL)
		ptr = ptr->left;
	return ptr;
}

/**
 * Replaces sub tree rooted at u with sub tree
 * rooted at v
 *
 */
void BSTree::transplant(BSTreeNode * u,BSTreeNode * v)
{
	if(u == root)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if(v != NULL)
		v->p = u->p;
}

void BSTree::traverse(BSTreeNode* T)
{
	if(T == NULL) return;
	traverse(T->left);
	cout << T->val << " ";
	traverse(T->right);

}
