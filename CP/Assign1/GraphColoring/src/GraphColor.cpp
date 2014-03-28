#include <iostream>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include<sys/time.h>

using namespace std;



int * readGraph(int &n,int &e)
{
  int * graph;
  int start,end;
  cin>>n;
  cin>>e;

  graph = new int[n*n]();

  for(int i=0;i<e;i++)
    {
      cin>>start; 
      cin>>end;
      if(start>n||end>n||start<1||end<1)
	cerr<<"Input Error:("<<start<<","<<end<<")"<<endl;
      else {
	graph[(start-1)*n + (end-1)]=1;
	graph[(end-1)*n + (start-1)]=1;
      }
    }

  return graph;
}

void printColour(int color[],int n)
{
  for(int i=0;i<n;i++)
    cout<<i+1<<" "<<color[i]<<endl;
}

void getDegree(int * graph,int *degree,int n)
{
  cilk_for(int i=0;i<n;i++)
    {
      int d=0;
      int base=i*n;
      for(int j=0;j<n;j++)
	{
	  if(graph[base+j]==1)
	    d++;
	}
      degree[i]=d;
    }
}

int paint(int *graph,int * degree,int * color,int * tmp,int n)
{
  cilk::reducer_opadd<int> nColored(0);
  int maxColor = 0;

  while(nColored.get_value() != n)
    {
      //Select vertex with max degrees 
      // Compared to neighbors
      cilk_for(int i = 0; i<n; i++)
	{
	  int base=i*n;
	  tmp[i]=0;
	  if(color[i]==0)
	    {
	      cilk::reducer_opadd<int> isMax(0);
	      int curdegree = degree[i];

	      /*
	       * if degree = 0
	       *  add vertex
	       * else if degree is  higer than it's neighbors
	       *  add vertex
	       * else
	       *   ignore
	       */
	      
	      cilk_for(int j=0;j<n;j++)
		{
		  if(graph[base+j]==1 && color[j]==0) {
		    if( degree[j]>curdegree) {
		      //j has higer degree
		      isMax++;
		      // break;
		    }
		    else if(degree[j]==curdegree && i<j ) {
		      //(d(j),j)>(d(i),i)
		      isMax++;
		      // break;		      
		    }
		  }
		}
	    	      
	      if(isMax.get_value()==0)
		{
		  tmp[i]++;
		}
	    }
	}

      for(int i = 0; i<n; i++)
	{
	  int base=i*n;
	  if(tmp[i]!=0)
	    {
	      for(int c=1;c<=maxColor;c++)
		{
		  cilk::reducer_opadd<int> isFound(0);
		  cilk_for(int j=0;j<n;j++)
		    {
		      if(graph[base+j]==1&&color[j]==c) {
			isFound++;
		      }
		    }
		  if(isFound.get_value()==0)
		    {
		      color[i]=c;
		      break;
		    }
		}
	      if(color[i]==0) {
		//Not colored till
		color[i]=++maxColor;
	      }
	      nColored++;

	      //update Degree
	      degree[i]=0;	     
	      cilk_for(int j=0;j<n;j++){
		if(graph[base+j]==1)
		  degree[j]--;
	      }
	    }
	}
    }
    
  return maxColor;
}

int main()
{
  int n,e;
  int * graph;
  int * degree;
  int * color;
  int * tmp;
  int maxColor;
  struct timeval start, end;
  unsigned int time;
  
  graph=readGraph(n,e);

#ifdef DEBUG 
  cerr<<"Finished Reading"<<endl;
#endif

  degree = new int[n]();  
  color = new int[n]();  
  tmp = new int[n]();  

#ifdef DEBUG 
  cerr<<"Finished Malloc"<<endl;
#endif

  getDegree(graph,degree,n);

  gettimeofday(&start, NULL);
  maxColor = paint(graph,degree,color,tmp,n);
  gettimeofday(&end, NULL);

  time = (1000000 * end.tv_sec + end.tv_usec)-
    (1000000 * start.tv_sec + start.tv_usec);

  cout<<time<<endl;
  cout<<maxColor<<endl;
  printColour(color,n);

}
