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
		RBTreeNode * lchild;
		RBTreeNode * rchild;
};

class RBTree: public Dictionary
{
	private:
		RBTreeNode * head;
		RBTreeNode * nill;
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
