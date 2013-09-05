/*
 * BSTree.h
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#ifndef BSTREE_H_
#define BSTREE_H_

#include "Dictionary.h"

class BSTree: public Dictionary
{
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
