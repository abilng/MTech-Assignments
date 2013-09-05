/*
 * BSTree.h
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#ifndef BSTREE_H_
#define BSTREE_H_

#include "Dictionary.h"

struct BSTNode
{
		data val;
		BSTNode * lchild;
		BSTNode * rchild;
};

class BSTree: public Dictionary
{
	private:
		BSTNode root;
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
