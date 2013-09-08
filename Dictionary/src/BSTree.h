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
<<<<<<< .mine
		BSTNode *root;
		BSTNode *nill;
		void traverse(BSTNode* T);
		BSTNode * lookup(data val,BSTNode *);
		BSTNode * lookup(data val);
		void transplant(BSTNode *,BSTNode *);
		void del(BSTNode *);
		
		BSTNode * minimum();
		BSTNode * minimum(BSTNode * ptr);

=======
		BSTreeNode * root;

		BSTreeNode * lookup(data val);
		BSTreeNode * lookup(data val,BSTreeNode* ptr);

		void transplant(BSTreeNode *,BSTreeNode *);
		void del(BSTreeNode *);
		void traverse(BSTreeNode* T);

		BSTreeNode * minimum();
		BSTreeNode * minimum(BSTreeNode * ptr);

>>>>>>> .r30
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
