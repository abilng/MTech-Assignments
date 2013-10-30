
#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <map>
#include <climits>

#define MIN_PRIORITY INT_MIN
#define MAX_PRIORITY INT_MAX

typedef int Priority;
typedef void* Location;

class Heap
{

	protected:
		std::map<Priority, Location> keyToAddress;
		bool setLocation(Location address,Priority key);
		bool deleteLocation(Priority key);
	public:
		virtual ~Heap() {};
		virtual void makeHeap() = 0;
		virtual Location insertKey(Priority key) = 0;
		virtual int deleteKey(Location nodeAddress) = 0;
		virtual Priority extractMin() = 0;
		virtual Priority findMin() = 0;
		virtual bool increaseKey(Location nodeAddress, Priority newKey) = 0;
		virtual bool decreaseKey(Location nodeAddress, Priority newKey) = 0;
		virtual bool displayHeap(char const* fileName) = 0;
		Location getLocation(Priority key);
};

#endif

