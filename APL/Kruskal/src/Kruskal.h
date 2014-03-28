
#ifndef KRUSKAL_H_
#define KRUSKAL_H_

#include <stddef.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "UnionFind.h"
#include "Sort.h"
#include "Graph.h"

using namespace std;

class Kruskal
{
	private:
		struct GraphNode* nodeSet;
		struct GraphNode* lastGraphNode;
		struct GraphEdge* edgeSet;
		struct GraphEdge* lastGraphEdge;
		struct GraphEdge* minimumSpanningTree;
		struct GraphEdge* lastMSTEdge;

		GraphNode* searchNode(char nodeName[]);
		void addEdgeToSpanningTree(struct GraphEdge* graphEdge);
		void displayEdges(struct GraphEdge* graphEdge);

	public:
		Kruskal();
		void addNode(char nodeName[]);
		void displayNodes();
		int addEdge(char startNodeName[], char endNodeName[], double label);
		void displayEdges();
		int MST_Kruskal(char* outputFile);
		void displaySpanningTree();
};

#endif
