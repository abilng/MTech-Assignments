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
	if(address == NULL)
		return false;
	keyToAddress[key] = address;
	return true;
}

bool Heap::deleteLocation(Priority key)
{
	if(keyToAddress.count(key)>0)
	{
		keyToAddress.erase (key);
		return true;
	}
	else
		return false;
}
