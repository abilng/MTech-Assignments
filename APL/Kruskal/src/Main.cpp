
#include "Kruskal.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#define INPUT_BUFFER 1000

using namespace std;


/*
 * Description: Parses GraphViz input file to extract node
 *          and edge definition of the graph to operate on.
 * Input: GraphViz input file containing node and
 *        edge definition of the graph to operate on.
 * Output: Graph to operate on in form of edge set and vertex set.
 */
int parseInput(char* parseFile, Kruskal* K)
{
	ifstream inputFile;
	char fileLine[INPUT_BUFFER];
	char* delimiter = " $[\"=];";
	char *srcNode, *destNode, *edgeWeight;
	short fileLineCount = 0;
	unsigned short charIndex;
	double weightOfEdge;

	inputFile.open(parseFile, ifstream::in);
	if(!inputFile.is_open())
	{
		perror("Error in reading:");
		return -1;
	}

	inputFile.getline(fileLine, INPUT_BUFFER);
	fileLineCount++;
	if(strcmp(fileLine, "graph G {"))
	{
		cout << "Expected: \"graph G {\" at line no. " << fileLineCount << endl;
		return -1;
	}

	inputFile.getline(fileLine, INPUT_BUFFER);
	fileLineCount++;
	if(strcmp(fileLine, "// nodes"))
	{
		cout << "Expected: \"// nodes\" at line no. " << fileLineCount << endl;
		return -1;
	}

	do
	{
			inputFile.getline(fileLine, INPUT_BUFFER);
			fileLineCount++;
			if(!(strcmp(fileLine, "// edges") && strcmp(fileLine, "}")))
				break;
			if(fileLine[strlen(fileLine) - 1] != ';')
			{
					cout << "Expected \';\' (semicolon) at the end of line no. " << fileLineCount << endl;
					return -1;
			}
			fileLine[strlen(fileLine) - 1] = '\0';
			K->addNode(fileLine);

	}
	while(!inputFile.eof());

	if(!strcmp(fileLine, "// edges"))
	{
		do
		{
				inputFile.getline(fileLine, INPUT_BUFFER);
				fileLineCount++;
				if(!strcmp(fileLine, "}"))
					break;
				if(fileLine[strlen(fileLine) - 1] != ';')
				{
						cout << "Expected \';\' (semicolon) at the end of line no. " << fileLineCount << endl;
						return -1;
				}

				for(charIndex = 0; charIndex < strlen(fileLine); charIndex++)
					if(fileLine[charIndex] == '-' && fileLine[charIndex + 1] == '-')
					{
						fileLine[charIndex] = '$';
						fileLine[charIndex + 1] = '$';
						break;
					}

				srcNode = strtok(fileLine, delimiter);
				if(!srcNode)
				{
					cout << "Can't extract source node information at line no. " << fileLineCount << endl;
					return -1;
				}

				destNode = strtok(NULL, delimiter);
				if(!destNode)
				{
					cout << "Can't extract destination node information at line no. " << fileLineCount << endl;
					return -1;
				}

				if(!strtok(NULL, delimiter))
				{
					cout << "Malformed edge pattern at line no. " << fileLineCount << endl;
					return -1;
				}

				edgeWeight = strtok(NULL, delimiter);
				if(!edgeWeight)
				{
					cout << "Can't extract edge weight information at line no. " << fileLineCount << endl;
					return -1;
				}

				weightOfEdge = strtod(edgeWeight, NULL);
				if(K->addEdge(srcNode, destNode, weightOfEdge) == -1)
				{
					cout << "Attempted to add an edge with non-existent node at line " << fileLineCount << endl;
					return -1;
				}
		}
		while(!inputFile.eof());
	}
	inputFile.close();

	return 0;
}


/*
 * Description: Driver program for Kruskal MST routine.
 * Input: GraphViz input file.
 * Output: GraphViz output file.
 */
int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cerr<<"Not enough arguments"<<endl;
		cerr<<"Usage:"<<argv[0]<<" input.gv output.gv"<<endl;
		return 1;
	}
	Kruskal* K = new Kruskal();
	parseInput(argv[1], K);
	K->MST_Kruskal(argv[2]);
	return 0;
}
