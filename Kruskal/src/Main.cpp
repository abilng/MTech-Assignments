
#include "Kruskal.h"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int parseInput(char* parseFile)
{
        ifstream inputFile;
        char fileLine[50];
        short fileLineCount = 0;

        inputFile.open(parseFile, ifstream::in);
        if(!inputFile.is_open())
                cout << "Error opening " << parseFile << ".\n";

        inputFile.getline(fileLine, 50);
        fileLineCount++;
        if(strcmp(fileLine, "graph G {"))
                cout << "Expected: \"graph G {\" at line no. " << fileLineCount << endl;

        inputFile.getline(fileLine, 50);
        fileLineCount++;
        if(strcmp(fileLine, "// nodes"))
                cout << "Expected: \"// nodes\" at line no. " << fileLineCount << endl;

        do
        {
                inputFile.getline(fileLine, 50);
                fileLineCount++;
                if(fileLine[strlen(fileLine) - 1] != ';')
                {
                        cout << "Expected \';\' (semicolon) at the end of line no. " <<fileLineCount << endl;
                        return -1;
                }
                cout << "Node: " << fileLine << endl;

        }while(strcmp(fileLine, "// edges") && strcmp(fileLine, "}"));

        return 0;
}


int main()
{
	Kruskal* K = new Kruskal();

	K->addNode("A");
	K->addNode("D");
	K->addNode("B");
	K->addNode("C");
	//K->displayNodes();

	K->addEdge("C", "B", 1);
	K->addEdge("A", "B", 15);
	K->addEdge("D", "B", 5);
	K->addEdge("D", "C", 9);
	K->addEdge("D", "A", 10);
	//K->displayEdges();

	K->MST_Kruskal();

	parseInput(argv[1]);
	return 0;
}
