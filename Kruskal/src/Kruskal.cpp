
#include "Kruskal.h"


Kruskal::Kruskal()
{
	nodeSet = new GraphNode();
	nodeSet->nextNode = NULL;
	lastGraphNode = nodeSet;

	edgeSet = new GraphEdge();
	edgeSet->nextEdge = NULL;
	lastGraphEdge = edgeSet;

	minimumSpanningTree = new GraphEdge();
	minimumSpanningTree->nextEdge = NULL;
	lastMSTEdge = minimumSpanningTree;
}


GraphNode* Kruskal::searchNode(char nodeName[])
{
	struct GraphNode* nodePtr = nodeSet;

	while(nodePtr)
	{
		if(!strcmp(nodePtr->nodeName, nodeName))
			return nodePtr;
		else
			nodePtr = nodePtr->nextNode;
	}

	return NULL;
}


void Kruskal::addNode(char nodeName[])
{
	struct GraphNode* newNode = new GraphNode();

	strcpy(newNode->nodeName, nodeName);
	newNode->nextNode = NULL;
	lastGraphNode->nextNode = newNode;
	lastGraphNode = newNode;

	return;
}


void Kruskal::displayNodes()
{
	struct GraphNode* currentNode = nodeSet;

	while(currentNode->nextNode)
	{
		cout << currentNode->nextNode->nodeName << " " << endl;
		currentNode = currentNode->nextNode;
	}
}


void Kruskal::addEdge(char startNodeName[], char endNodeName[], int label)
{
	struct GraphEdge* newEdge = new GraphEdge();

	newEdge->startNode = searchNode(startNodeName);
	newEdge->endNode = searchNode(endNodeName);
	newEdge->label = label;
	newEdge->nextEdge = NULL;
	lastGraphEdge->nextEdge = newEdge;
	lastGraphEdge = newEdge;

	return;
}


void Kruskal::displayEdges(struct GraphEdge* graphEdge)
{
	struct GraphEdge* currentEdge = edgeSet;

	while(currentEdge->nextEdge)
	{
		cout << currentEdge->nextEdge->startNode->nodeName << "-" << currentEdge->nextEdge->endNode->nodeName << "(" << currentEdge->nextEdge->label << ")" << endl;
		currentEdge = currentEdge->nextEdge;
	}
}


void Kruskal::displayEdges()
{
	displayEdges(edgeSet);
}


void Kruskal::addEdgeToSpanningTree(struct GraphEdge* graphEdge)
{
	struct GraphEdge* newMSTEdge = new GraphEdge();

	newMSTEdge->startNode = graphEdge->startNode;
	newMSTEdge->endNode = graphEdge->endNode;
	newMSTEdge->label = graphEdge->label;
	newMSTEdge->nextEdge = NULL;
	lastMSTEdge->nextEdge = newMSTEdge;
	lastMSTEdge = newMSTEdge;

	return;
}


void Kruskal::MST_Kruskal()
{
	class UnionFind* unionFind = new UnionFind();
	class Sort* sort = new Sort();
	struct GraphNode* nodePtr = nodeSet;
	struct GraphEdge* edgePtr = edgeSet;

	while(nodePtr)
	{
		unionFind->MakeSet(nodePtr);
		nodePtr = nodePtr->nextNode;
	}

	sort->MergeSort(edgeSet);

	while(edgePtr)
	{
		if(unionFind->FindSet(edgePtr->startNode) != unionFind->FindSet(edgePtr->endNode))
		{
			addEdgeToSpanningTree(edgePtr); cout << "Edge added to MST";
			unionFind->Union(edgePtr->startNode, edgePtr->endNode);
		}
	}
}


void Kruskal::displaySpanningTree()
{
	displayEdges(minimumSpanningTree);
}

