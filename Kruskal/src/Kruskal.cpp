
#include "Kruskal.h"


/* Description: Constructor of Kruskal class.
 * Input: NA
 * Output: Linked lists of edges and sets properly initialized.
 */ 
Kruskal::Kruskal()
{
	nodeSet = new GraphNode();
	nodeSet->nextNode = NULL;
	lastGraphNode = nodeSet;

	edgeSet = new GraphEdge();
	edgeSet->label = -1;
	edgeSet->nextEdge = NULL;
	lastGraphEdge = edgeSet;

	minimumSpanningTree = new GraphEdge();
	minimumSpanningTree->nextEdge = NULL;
	lastMSTEdge = minimumSpanningTree;
}


/* Description: Searches the reference of a node from the set of nodes.
 * Input: Name of graph node.
 * Output: Reference of graph node, if exists.
 */
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


/* Description: Adds a node to the list of nodes.
 * Input: Name of the graph node to be added.
 * Output: Modified linked list of graph nodes.
 */
void Kruskal::addNode(char nodeName[])
{
	struct GraphNode* newNode = new GraphNode();

	strcpy(newNode->nodeName, nodeName);
	newNode->nextNode = NULL;
	lastGraphNode->nextNode = newNode;
	lastGraphNode = newNode;

	return;
}


/* Description: Displays list of graph nodes.
 * Input: NA
 * Output: List of graph nodes.
 */ 
void Kruskal::displayNodes()
{
	struct GraphNode* currentNode = nodeSet;

	while(currentNode->nextNode)
	{
		cout << currentNode->nextNode->nodeName << " " << endl;
		currentNode = currentNode->nextNode;
	}
}


void Kruskal::addEdge(char startNodeName[], char endNodeName[], double label)
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
	struct GraphEdge* currentEdge = graphEdge;

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


int Kruskal::MST_Kruskal(char* outputFile)
{
	class UnionFind* unionFind = new UnionFind();
	class Sort* sort = new Sort();
	struct GraphNode* nodePtr = nodeSet->nextNode;
	struct GraphEdge* edgePtr;
	ofstream outFile;
	int isPrinted;

	outFile.open(outputFile, ofstream::out);
	if(!outFile.is_open())
	{
		cout << "Error writing " << outputFile << ".\n";
		return -1;
	}

	outFile << "graph G {\n";
	outFile << "// nodes\n";

	while(nodePtr)
	{
		outFile << nodePtr->nodeName << ";\n";
		unionFind->MakeSet(nodePtr);
		nodePtr = nodePtr->nextNode;
	}

	outFile << "// edges\n";
	sort->MergeSort(&(edgeSet->nextEdge));
	edgePtr = edgeSet->nextEdge;

	while(edgePtr)
	{
		isPrinted = 0;
		if(unionFind->FindSet(edgePtr->startNode) != unionFind->FindSet(edgePtr->endNode))
		{
			addEdgeToSpanningTree(edgePtr);
			unionFind->Union(edgePtr->startNode, edgePtr->endNode);
			outFile << edgePtr->startNode->nodeName << " -- " << edgePtr->endNode->nodeName << " [label=\"" << edgePtr->label << "\", color=blue];\n";
			isPrinted = 1;
		}

		if(!isPrinted)
			outFile << edgePtr->startNode->nodeName << " -- " << edgePtr->endNode->nodeName << " [label=\"" << edgePtr->label << "\", style=dotted];\n";
		edgePtr = edgePtr->nextEdge;
	}

	outFile << "}";
	outFile.close();
	return 0;
}


void Kruskal::displaySpanningTree()
{
	displayEdges(minimumSpanningTree);
}

