/*
 * RandomGraph.h
 *
 *  Created on: Nov 12, 2013
 *      Author: Dipanjan
 */

#ifndef RANDOMGRAPH_H_
#define RANDOMGRAPH_H_

#include <vector>
using namespace std;

vector<bool> graph_property (bool**, int&, int);
double getProbability (int, int);
void getEdges(bool**, int, double, int&);

#endif
