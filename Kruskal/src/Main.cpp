
#include "Kruskal.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#define INPUT_BUFFER 100

using namespace std;

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


int main(int argc, char* argv[])
{
	Kruskal* K = new Kruskal();
	parseInput(argv[1], K);
	K->MST_Kruskal(argv[2]);
	return 0;
}
