/*
 * RBTree.h
 *
 *  Created on: Sep 5, 2013
 *      Author: abilng
 */

#ifndef RBTREE_H_
#define RBTREE_H_

#include "Dictionary.h"

#define NA -1

enum colour{RED,BLACK};

struct RBTreeNode
{
		data val;
		colour c;
		RBTreeNode *p;
		RBTreeNode * left;
		RBTreeNode * right;
};

class RBTree: public Dictionary
{
	private:
		RBTreeNode * root;
		RBTreeNode * nill;

		RBTreeNode * lookup(data val,RBTreeNode *);
		RBTreeNode * lookup(data val);

		void leftRotate(RBTreeNode *);
		void rightRotate(RBTreeNode *);
		void transplant(RBTreeNode *,RBTreeNode *);

	public:
		RBTree();
		~RBTree();

		void insert(data val);
		bool del(data val);
		bool search(data val);
		void clear();
		void display();
};

#endif /* RBTREE_H_ */
