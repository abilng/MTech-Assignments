#include<iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "RandomGraph.h"


using namespace std;


vector<bool> graph_property (bool adj[][1000], int& number_of_edges, int n) {
  vector<bool> flag(2, false); // 0 -> connectivity, 1 -> cycle
  //cout << number_of_edges << " " << n << endl;
  int i = 0;
  int nn = 0;
  int next_index = -1;
  int number_of_SCC = 1;
  int * spanning_tree = new int [n-1];		//	Auxiliary array to hold row number of adjacency matrix visited i.e. the node visited
  bool * visited = new bool [n];			//	Auxiliary array to hold truth values of visiting each node. Indexed by node number
  visited [0] = true;				//	Start algorithm from node 0. So node 0 is marked as visited

  for (int i = 0; i < n ; i++) {
    spanning_tree [i] = -1;
    visited [i] = false;
  }

  do
    {
      for (int j = 0; j < n; j++)		//	Read Adj matrix row indexed by next value in spanning_tree []
        {
	  if (adj [i][j] == true)
            {
	      if (visited [j] == false)
                {
		  spanning_tree [nn++] = j;	//	Put node number of each visited node into spanning_tree []
		  visited [j] = true;
                }
            }
        }

      next_index++;
      i = spanning_tree [next_index];

    } while (spanning_tree [next_index] != -1 && nn < n-1);	//	till no new node is accessible or all nodes have been visited

  if (i == -1)
    {
      //cout<<"\nGraph is NOT connected\n";
      flag[0] = false;
      if (number_of_edges > n - 1) {
	//cout<<"\nGraph is CYCLIC\n"<<number_of_edges;
	flag[1] = true;
      }
      else
        {						// Check for cycle in disconnected graph i.e. |E| > # SCCs
	  do
            {	int i;
	      for (i = 0; i < n; i++)
                {
		  if (visited [i] == false)
                    {
		      int temp = i;
		      number_of_SCC++;
		      visited [i] = true;
		      spanning_tree [nn++] = i;
		      do
                        {
			  for (int j = 0; j < n; j++)
                            {
			      if (adj [i][j] == true)
                                {
				  if (visited [j] == false)
                                    {
				      visited [j] = true;
				      spanning_tree [nn++] = j;
                                    }
                                }
                            }
			  next_index++;
			  i = spanning_tree [next_index];
                        } while (spanning_tree [next_index] != -1 && nn < n-1);
		      i = temp;
                    }
                }

            } while (spanning_tree [n-2] == -1);		// All nodes have been visited

	  //cout<<"SCC: "<<number_of_SCC;

	  if (number_of_edges > n - number_of_SCC) {
	    //cout<<"\nGraph is CYCLIC\n"<<number_of_edges;
	    flag[1] = true;
	  }
        }
    }

  else
    {
      //cout<<"\nGraph is connected\n";
      flag[0] = true;
      if (number_of_edges > n - 1) {
	//cout<<"\nGraph is CYCLIC\n"<<number_of_edges;
	flag[1] = true;
      }
    }
  return flag;
}

void getEdges(bool adj[][1000], int n, double p, int& number_of_edges) {
  //cout << "Getting edges with p: " << p << endl;
  //cout << "n is " << n << endl;
  for (int i = 0; i < n; i++) {
    adj[i][i] = false;
    for (int j = i + 1; j < n; j++) {
      double ep = ((double) rand() / (RAND_MAX));
      //cout << "HERE"<< ep << endl;
      if (ep <= p) {
	adj[i][j] = true;
	adj[j][i] = true;
	number_of_edges++;
      } else {
	adj[i][j] = false;
	adj[j][i] = false;
      }
    }
  }
  /* cout << n << "##\n";
     for (int i = 0; i < n; i++) {
     for (int j = 0; j < n; j++) {
     cout << adj[i][j] << " " ;
     }
     cout << endl;
     }*/
}

double getProbability (int n, int fun) {
  double p;
  switch(fun) {
  case 0: { // constant probability
    p = 0.075;
    return p;
  }
  case 1: {
    p = (double)1 / n;
    return p;
  }
  case 2: {
    p = log(n) / n;
    return p;
  }
  case 3: {
    p = (double)1/(n * n);
    return p;
  }
  case 4: {
    p = sqrt(log(n) / n);
    return p;
  }

  }
  return 0.075;
}
