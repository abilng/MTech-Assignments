
#include "UnionFind.h"


void UnionFind::MakeSet(GraphNode* x)
{
	x->parent = x;
	x->rank = 0;
}


void UnionFind::Union(GraphNode* x, GraphNode* y)
{
	Link(FindSet(x), FindSet(y));
}


void UnionFind::Link(GraphNode* x, GraphNode* y)
{
	if(x->rank > y->rank)
		y->parent = x;
	else
	{
		x->parent = y;
		if(x->rank == y->rank)
			y->rank = y->rank + 1;
	}
}


GraphNode* UnionFind::FindSet(GraphNode* x)
{
	if(x != x->parent)
		x->parent = FindSet(x->parent);
	return x->parent;
}
