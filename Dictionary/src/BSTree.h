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

		BSTreeNode * lookup(data val);
		BSTreeNode * lookup(data val,BSTreeNode* ptr);

		void transplant(BSTreeNode *,BSTreeNode *);
		void del(BSTreeNode *);
		void traverse(BSTreeNode* T);

		BSTreeNode * minimum();
		BSTreeNode * minimum(BSTreeNode * ptr);

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
