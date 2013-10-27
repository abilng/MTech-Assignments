/*
 * Heap.cpp
 *
 *  Created on: Oct 27, 2013
 */

#include "Heap.h"

Location Heap::getLocation(Priority key)
{
	Location ret;
	if ( keyToAddress.count(key)>0 ) {
		// found
		ret = keyToAddress[key];
	} else {
		//not found
	  ret = NULL;
	}
	return ret;
}

bool Heap::setLocation(Location address,Priority key)
{
	if(keyToAddress.count(key)>0) {
		return false;
	} else {
		keyToAddress[key] = address;
		return true;
	}
}
