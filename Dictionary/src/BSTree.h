/*
 * BSTree.h
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#ifndef BSTREE_H_
#define BSTREE_H_

#include "Dictionary.h"

#define NA -1

struct BSTreeNode
{
		data val;
		BSTreeNode * left;
		BSTreeNode * right;
		BSTreeNode * p;
};

class BSTree: public Dictionary
{
	private:
		BSTreeNode * root;
		BSTreeNode * nill;
	public:
		BSTree();
		~BSTree();

		void insert(data val);
		bool del(data val);
		bool search(data val);
		void clear();
		void display();

};

#endif /* BSTREE_H_ */
