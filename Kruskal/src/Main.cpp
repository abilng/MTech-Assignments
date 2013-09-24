
#include "Kruskal.h"

int main()
{
	Kruskal* K = new Kruskal();

	K->addNode("A");
	K->addNode("D");
	K->addNode("B");
	K->addNode("C");
	//K->displayNodes();

	K->addEdge("D", "B", 5);
	K->addEdge("D", "C", 15);
	K->addEdge("A", "B", 9);
	//K->displayEdges();

	K->MST_Kruskal();
	cout << "Done";

	return 0;
}
