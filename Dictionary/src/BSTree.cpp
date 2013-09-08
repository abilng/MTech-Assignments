/*
 * BSTree.cpp
 *
 *  Created on: Sep 5, 2013
 *      
 */

#include "BSTree.h"


BSTree::BSTree()
{
<<<<<<< .mine
	nill = new BSTNode();
		nill->val = -1;
		nill->left = NULL;
		nill->right= NULL;
		nill->p = NULL;
=======
	root = NULL;
>>>>>>> .r30

}

BSTree::~BSTree()
{
	clear();
}

void BSTree::insert(data val)
{
	BSTNode *x, *y, *z;
	z = new BSTNode();
<<<<<<< .mine
		z->val = val;
		z->left = this->nill;
		z->right = this->nill;
		z->p = this->nill;
		y = this->nill;
			x = this->root;
			while(x != this->nill)
			{
				y = x;
				if (z->val==x->val)
				
			
						return;
			
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
=======
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
>>>>>>> .r30
		  
		  
inline BSTNode * BSTree::lookup(data val)
{
	return lookup(val,root);
}
		  
BSTNode * BSTree::lookup(data val,BSTNode * ptr)
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

<<<<<<< .mine
 
void BSTree::transplant(BSTNode * u,BSTNode * v)
{
	if(u->p == nill)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (v != nill)
		v->p = u->p;
=======
inline BSTreeNode * BSTree::lookup(data val)
{
	return lookup(val,root);
>>>>>>> .r30
}

BSTNode * BSTree::minimum()
{
	return minimum(root);
}
BSTNode * BSTree::minimum(BSTNode * ptr)
{
	while(ptr->left != nill)
		ptr = ptr->left;
	return ptr;
}

<<<<<<< .mine
void BSTree::del(BSTNode * delNode)
{
=======
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
>>>>>>> .r30

<<<<<<< .mine
	
	BSTNode *xNode;

	
	BSTNode *yNode;

	yNode= delNode;
	

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
		
	}

	
}




bool BSTree::del(const data val)
=======
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
>>>>>>> .r30
{
<<<<<<< .mine
	BSTNode * delNode = lookup(val);
	if(delNode == NULL)
		return false;
	del(delNode);
	
=======
	BSTreeNode * delnode = lookup(val);
	if(delnode == NULL)
		return false;
	del(delnode);
>>>>>>> .r30
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
void BSTree::traverse(BSTNode* T)
{
	if(T->left != this->nill)
		traverse(T->left);

	cout << T->val ;
	

	if(T->right != this->nill)
		traverse(T->right);
}

void BSTree::display()
{
<<<<<<< .mine
	traverse(this->root);
=======
 traverse(root);
>>>>>>> .r30
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
