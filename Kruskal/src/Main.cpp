
#include "Kruskal.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#define INPUT_BUFFER 100

using namespace std;


/*
 * Description: Parses GraphViz input file to extract node and edge definition of the graph to operate on.
 * Input: GraphViz input file containing node and edge definition of the graph to operate on.
 * Output: Graph to operate on in form of edge set and vertex set.
 */
int parseInput(char* parseFile, Kruskal* K)
{
	ifstream inputFile;
	char fileLine[INPUT_BUFFER];
	char* delimiter = " -[\"=];";
	char *srcNode, *destNode, *edgeWeight;
	short fileLineCount = 0;

	inputFile.open(parseFile, ifstream::in);
	if(!inputFile.is_open())
	{
		cout << "Error reading " << parseFile << ".\n";
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

				srcNode = strtok(fileLine, delimiter);
				destNode = strtok(NULL, delimiter);
				strtok(NULL, delimiter);
				edgeWeight = strtok(NULL, delimiter);
				K->addEdge(srcNode, destNode, atoi(edgeWeight));
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
	Kruskal* K = new Kruskal();
	parseInput(argv[1], K);
	K->MST_Kruskal(argv[2]);
	return 0;
}
