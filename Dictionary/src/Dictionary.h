/*
 * Dictionary.h
 *
 *  Created on: Sep 5, 2013
 *      Author: abil
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

typedef int data;

class Dictionary
{
	public:
		virtual ~Dictionary() { }
		virtual void insert(data val) = 0;
		virtual bool del(data val) = 0;
		virtual bool search(data val) = 0;
		virtual void clear() = 0;
		virtual void display() = 0;
};

#endif /* DICTIONARY_H_ */
