
#ifndef BSTREE_H_
#define BSTREE_H_

#include "Dictionary.h"
#define NA -1

#define NA -1

struct BSTNode
{
		data val;
		BSTNode * left;
		BSTNode * right;
		BSTNode * p;
};

class BSTree: public Dictionary
{
	private:
		BSTNode * root;

		BSTNode * lookup(data val);
		BSTNode * lookup(data val,BSTNode* ptr);

		void transplant(BSTNode *,BSTNode *);
		void del(BSTNode *);
		void traverse(BSTNode* T);

		BSTNode * minimum();
		BSTNode * minimum(BSTNode * ptr);

		void clear(BSTNode * root);

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
