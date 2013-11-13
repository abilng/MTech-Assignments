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
  int numVertices[] = {
    10, 20, 50, 100,150,
    200,250,300,350,400,
    500,600,700,800,900,1000
  };

  int nv = 16;
  int nc;
  int x;
  bool adj[1000][1000];

  double initC=0.25,finalC,stepC=0.25;


  cout<<"Choose the probability Function:\n";
  cout<<"1.  P(n) = 1/n"<<endl;
  cout<<"2.  P(n) = log(n)/n"<<endl;
  cout<<"3.  P(n) = 1/(n^2)"<<endl;
  cout<<"4.  P(n) = sqrt(log(n)/n)"<<endl;
  cout<<"Enter the option: ";
  cin >> x;
  
  /*
  cout<<"\nEnter the initial,max and step size for c : ";
  cin>>initC>>finalC>>stepC;
  */
  /*
  cout<<"\nEnter the initial value of C : ";
  cin>>initC;
  cout<<"\nEnter the step size of C : ";
  cin>>stepC;  
  cout<<"\nEnter the no: of values of (C) : ";
  cin>>nc;
  */
  

  //  int nc = (finalC-initC)/stepC;
  nc = 50;
  int numConnected[nc], numCyclic[nc];
 
  for(int k=0;k<nc;k++){
    numConnected[k] = 0;
    numCyclic[k] = 0;
  }

  int k = 0;


  for (int l = 0; l < nc; l++) {
    double c = stepC*l+initC;
    k=0;
    for (int i = 0; i < nv; i++) {
      n = numVertices[i];

      double p = getProbability(n,x)*c;
      if (p > 1.0) {
        p = 1.0;
      }
      int number_of_edges = 0;

      getEdges(adj, n, p, number_of_edges);
      vector<bool> flag = graph_property(adj, number_of_edges, n);
      if (flag[0] == true) {
	numConnected[l]++;
      }
      if (flag[1] == true) {
	numCyclic[l]++;
      }
      k++;
    }
  }
  stringstream ss;
  ss << "plot_" <<x<<".out";
  string filename = ss.str();

  ofstream fout(filename.c_str());

  double connectProb[nc], cycleProb[nc];
  for (int l = 0; l < nc; l++) {
    connectProb[l] = (double)numConnected[l]/nv;
    cycleProb[l] = (double)numCyclic[l]/nv;
    fout << stepC*(l)+initC<<" "<< connectProb[l] <<" "<< cycleProb[l]<< endl;
  }
  fout.close();
}

