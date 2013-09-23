
#ifndef UNIONFIND_H_
#define UNIONFIND_H_

#include "Graph.h"

class UnionFind
{
	public:
		void MakeSet(GraphNode*);
		void Union(GraphNode*, GraphNode*);
		void Link(GraphNode*, GraphNode*);
		GraphNode* FindSet(GraphNode*);
};

#endif
