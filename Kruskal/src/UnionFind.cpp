/**
 *Implements standard Disjoint Set (Union Find) data structure
 *
 */

#include "UnionFind.h"


/**
 * Description: Add a set to disjoint-set  data structure with only one element.
 *       i.e, Create new set {x} with representative x
 * Input: Element (Graph Node).
 * Output: NA.
 */
void UnionFind::MakeSet(GraphNode* x)
{
	x->parent = x;
	x->rank = 0;
}


/**
 * Description: Join two subsets (of Graph Nodes) into a single subset.
 * Input: Two elements (Graph Node).
 * Output: NA.
 */
void UnionFind::Union(GraphNode* x, GraphNode* y)
{
	if(FindSet(x) != FindSet(y))
		Link(FindSet(x), FindSet(y));
}



/**
 * Description: Link a given element (y) to another another element (x) or vice-versa
 *          and adjust rank if needed.Called by Union
 * Input: Two elements (Graph Node).
 * Output: NA.
 */
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



/**
 * Description: Get the representative of the set that given element belongs to.
 * Input: an element (Graph Node).
 * Output:Repersentative element (Graph Node).
 */
GraphNode* UnionFind::FindSet(GraphNode* x)
{
	if(x != x->parent)
		x->parent = FindSet(x->parent);
	return x->parent;
}
