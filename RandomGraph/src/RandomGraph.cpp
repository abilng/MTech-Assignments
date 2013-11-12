#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "RandomGraph.h"


using namespace std;


int main ()
{
    int n;
    int numVertices[] = {10, 2, 5, 10, 50, 100, 200, 500, 1000, 1500};
    //int nv = 9;
    int nv = 1;
    int nc = 20;
    srand(time(NULL));
    cout<<rand ();
    int x;
    cin >> x;
  //  int np = 5;
  int np = 1;
    for (int j = 0; j < np; j++) {
        double pc[nc];
        int numConnected[nc], numCyclic[nc];
        for (double c = 0.5; c <= 10.0; c += 0.5) {
            double p = getProbability(n, j);
            int k = 0;
            pc[k] = p * c;
            if (pc[k] > 1.0) {
                pc[k] = 1.0;
            }
            for (int i = 0; i < nv; i++) {
                n = numVertices[i];
                bool ** adj;					//	Adjacency Matrix
                adj = new bool * [n];
                for (int i = 0; i < n; i++)			//	Creating the Adj Matrix
                {
                    adj [i] = new bool [n];
                }

                int number_of_edges = 0;

                numConnected[k] = 0;
                numCyclic[k] = 0;

                getEdges(adj, n, pc[k], number_of_edges);
                vector<bool> flag = graph_property(adj, number_of_edges, n);
                if (flag[0] == true) {
                    cout << "Graph is connected" << endl;
                    numConnected[k]++;
                }
                if (flag[1] == true) {
                   cout << "Graph is cyclic" << endl;
                    numCyclic[k]++;
                }
                k++;
            }
        }
        stringstream ss;
        ss << "plot" << j;
        string filename = ss.str();
       // char* filename = strcat("plot", itoa(j));
        ofstream fout(filename.c_str());
        double connectProb[nc], cycleProb[nc];
        for (int l = 0; l < nc; l++) {
            connectProb[l] = (double)numConnected[l] / nv;
            cycleProb[l] = (double)numCyclic[l] / nv;
            fout << pc[l] << " " << connectProb[l] << " " << cycleProb[l] << endl;
        }
        fout.close();
    }
}



//
//
//
//}
//
////cout<<"\nEnter the number of nodes: ";
////cin>>n;
//
//
//
//
//cout<<"\nEnter the values in adj matrix (row wise): \n";
//
//for (int i = 0; i < n; i++)			//	Enter values in Adj Matrix
//{
//	for (int j = 0; j < n; j++)
//		{
//			cout<<"\nEnter adj ["<<i<<"] ["<<j<<"] : ";
//			cin>>adj [i][j];
//			if (adj [i][j])
//				number_of_edges++;
//		}
//}
//
//number_of_edges = number_of_edges/2;
//
//
//return 0;
//}
