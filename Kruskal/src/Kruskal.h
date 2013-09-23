
#ifndef KRUSKAL_H_
#define KRUSKAL_H_

#include <stddef.h>
#include "UnionFind.h"
#include "Sort.h"
#include "Graph.h"

class Kruskal
{
	private:
		struct GraphNode* nodeSet;
		struct GraphEdge* edgeSet;
		struct GraphEdge* minimumSpanningTree;

	public:
		void addNode(char* nodeName);
		void addEdge(char* startNodeName, char* endNodeName, int label);
		void addEdgeToSpanningTree(struct GraphEdge* graphEdge);
		void MST_Kruskal(struct GraphNode* nodeSet, struct GraphEdge* edgeSet);
};

#endif
