
#include "Kruskal.h"


void addNode(char* nodeName)
{
	return;
}


void addEdge(char* startNodeName, char* endNodeName, int label)
{
	return;
}


void Kruskal::addEdgeToSpanningTree(struct GraphEdge* graphEdge)
{
	return;
}


void Kruskal::MST_Kruskal(struct GraphNode* nodeSet, struct GraphEdge* edgeSet)
{
	class UnionFind* unionFind = new UnionFind();
	class MergeSort* mergeSort = new MergeSort();
	struct GraphNode* nodePtr = nodeSet;
	struct GraphEdge* edgePtr = edgeSet;
	minimumSpanningTree = NULL;

	while(!nodePtr)
	{
		unionFind->MakeSet(nodePtr);
		nodePtr = nodePtr->nextNode;
	}

	mergeSort->Sort(edgeSet);

	while(!edgePtr)
	{
		if(unionFind->FindSet(edgePtr->startNode) != unionFind->FindSet(edgePtr->endNode))
		{
			addEdgeToSpanningTree(edgePtr);
			unionFind->Union(edgePtr->startNode, edgePtr->endNode);
		}
	}
}
