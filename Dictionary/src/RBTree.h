/*
 * RBTree.h
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#ifndef RBTREE_H_
#define RBTREE_H_

#include "Dictionary.h"

class RBTree: public Dictionary
{
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
