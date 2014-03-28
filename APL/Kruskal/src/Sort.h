
#ifndef SORT_H_
#define SORT_H_

#include <iostream>
#include "Graph.h"

using namespace std;

class Sort
{
	private:
		struct GraphEdge* SortedMerge(struct GraphEdge* a, struct GraphEdge* b);
		void FrontBackSplit(struct GraphEdge* source,struct GraphEdge** frontRef, struct GraphEdge** backRef);

	public:
		void MergeSort(struct GraphEdge** edgeSet);
};

#endif
