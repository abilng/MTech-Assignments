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

	root = nill;
}

RBTree::~RBTree()
{
	clear();
	delete nill;
}


void RBTree::insert(data val)
{
	RBTreeNode *x, *y, *z;

	z = new RBTreeNode();
	z->val = val;
	z->left = this->nill;
	z->right = this->nill;
	z->colour = RED;
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
	z->colour = RED;
	insertFixup(z);
}


void RBTree::insertFixup(RBTreeNode* z)
{
	RBTreeNode *y;

	while(z->p->colour == RED)
	{
		if(z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if(y->colour == RED)
			{
				z->p->colour= BLACK;
				y->colour = BLACK;
				z->p->p->colour = RED;
				z = z->p->p;
			}
			else
			{
				if(z == z->p->right)
				{
					z = z->p;
					leftRotate(z);
				}

				z->p->colour = BLACK;
				z->p->p->colour = RED;
				rightRotate(z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if(y->colour == RED)
			{
				z->p->colour= BLACK;
				y->colour = BLACK;
				z->p->p->colour = RED;
				z = z->p->p;
			}
			else
			{
				if(z == z->p->left)
				{
					z = z->p;
					rightRotate(z);
				}

				z->p->colour = BLACK;
				z->p->p->colour = RED;
				leftRotate(z->p->p);
			}
		}
	}
	this->root->colour = BLACK;
}

bool RBTree::del(const data val)
{
	RBTreeNode * delNode = lookup(val);
	if(delNode == NULL)
		return false;
	del(delNode);
	return true;
}

bool RBTree::search(data val)
{
	if(lookup(val)==NULL)
		return false;
	else
		return true;
}

void RBTree::clear()
{
	//TODO
}

void RBTree::traverse(RBTreeNode* T)
{
	if(T == nill) return;
	if(T->left != this->nill)
		traverse(T->left);

	cout << T->val << "(";
	if(T->colour)
		cout << 'B';
	else
		cout << 'R';
	cout << ")";

	if(T->right != this->nill)
		traverse(T->right);
}

void RBTree::display()
{
	traverse(this->root);
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

void RBTree::leftRotate(RBTreeNode *x)
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
		delete delNode;
	}
	else if(delNode->right == nill)
	{
		xNode= delNode->left;
		transplant(delNode,delNode->left);
		delete delNode;
	}
	else
	{
		yNode = minimum(delNode->right); //find successor
		yOrginalColour = yNode->colour;
		xNode = yNode->right;

		if (yNode->p == delNode)
		{
			if(xNode != nill)
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
		delete delNode;
	}

	if (yOrginalColour == BLACK && xNode != nill)
		deleteFixup(xNode);
}
void RBTree::deleteFixup(RBTreeNode * x)
{
	RBTreeNode * w;//Sibling

	while(x !=root && x->colour == BLACK)
	{
		if(x->p->left == x) //x is left child
		{
			w=x->p->right;
			if(w->colour == RED)
			{
				/**
				 * CASE I:sibling is red
				 *
				 * exchange color of w and w.p;
				 * Left Rotate about parent of x (of w also )
				 * Find new Sibling
				 * Case converted to 2/3/4
				 */
				w->colour = BLACK;
				w->p->colour = RED;
				leftRotate(x->p);
				w = x->p->right;
			}
			if(w->left->colour == BLACK
					&& w->right->colour == BLACK)
			{
				/**
				 * CASE II:sibling is black and both it's
				 * children are black.
				 *
				 * Removing one black from both x and w
				 * Add extra black to x.p
				 * Continue with x.p as new x
				 */
				w->colour = RED;
				x = x->p;
			}
			else
			{
				if(w->right->colour == BLACK){
					/**
					 * CASE III:sibling is black and
					 * left child is RED and right child is BLACK
					 *
					 * switch color of w and w.left
					 * Left Rotate w.r.t w.
					 * New sibling w is black with BLACK left child and
					 * RED red right child (i.e, Converted to CASE IV)
					 */

					w->left->colour = BLACK;
					w->colour = RED;
					rightRotate(w);
					w = x->p->right;

				}
				/**
				 * CASE IV:Sibling w is black with RED red right child
				 *
				 * Exchange color of w and it's parent (also x.p)
				 * change color of right child of w to BLACK.
				 * Left Rotate about x.p and
				 * Remove Extra black on x (i.e, end Fix-up)
				 */

				w->colour = w->p->colour;
				w->p->colour = BLACK;
				w->right->colour = BLACK;
				leftRotate(x->p);
				x = root; //break while;
			}
		}
		else //x is right child
		{
			w=x->p->left;

			if(w->colour == RED)
			{
				/**
				 * CASE I:sibling is red
				 *
				 */
				w->colour = BLACK;
				w->p->colour = RED;
				rightRotate(x->p);
				w = x->p->left;
			}
			if(w->left->colour == BLACK
					&& w->right->colour == BLACK)
			{
				/**
				 * CASE II:sibling is black and both it's
				 * children are black.
				 */
				w->colour = RED;
				x = x->p;
			}
			else
			{
				if(w->left->colour == BLACK){
					/**
					 * CASE III:sibling is black and
					 * right child is RED and left child is BLACK
					 */

					w->right->colour = BLACK;
					w->colour = RED;
					leftRotate(w);
					w = x->p->left;

				}
				/**
				 * CASE IV:Sibling w is black
				 * with RED red left child
				 */

				w->colour = w->p->colour;
				w->p->colour = BLACK;
				w->left->colour = BLACK;
				rightRotate(x->p);
				x = root; //break while;
			}
		}

	}
	x->colour = BLACK;

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

