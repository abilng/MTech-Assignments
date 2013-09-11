/*
 * BSTree.cpp
 *
 *  Created on: Sep 5, 2013
 *
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
    BSTNode *x, *y, *z;
    z = new BSTNode();
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


bool BSTree::del(data val)
{
    BSTNode * delnode = lookup(val);
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
    clear(root);
    root = NULL;
}

void BSTree::display()
{
 traverse(root);
}

inline BSTNode * BSTree::lookup(data val)
{
    return lookup(val,root);
}


BSTNode * BSTree::lookup(data val,BSTNode* ptr)
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

void BSTree::del(BSTNode * z)
{
    BSTNode * y;
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


BSTNode * BSTree::minimum()
{
    return minimum(root);
}
/**
 * Minimum of Tree rooted at ptr
 */
BSTNode * BSTree::minimum(BSTNode * ptr)
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
void BSTree::transplant(BSTNode * u,BSTNode * v)
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

void BSTree::traverse(BSTNode* T)
{
    if(T == NULL) return;
    traverse(T->left);
    cout << T->val << " ";
    traverse(T->right);

}

void BSTree::clear(BSTNode * root)
{
	if(root == NULL)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
}
