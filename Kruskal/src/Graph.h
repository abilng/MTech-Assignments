
#ifndef GRAPH_H_
#define GRAPH_H_

struct GraphNode
{
	char nodeName[100];
	struct GraphNode* parent;
	int rank;
	struct GraphNode* nextNode;
};


struct GraphEdge
{
	struct GraphNode* startNode;
	struct GraphNode* endNode;
	double label;
	struct GraphEdge* nextEdge;
};

#endif
