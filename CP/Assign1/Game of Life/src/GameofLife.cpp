#include<cstdio>
#include<cstdlib>
#include<cilk/cilk.h>


#define SIZE 10000
//#define SIZE 15
#define CELL( A,I,J)  ((A)[SIZE*(I)+(J)])
#define live 1
#define dead 0

void printMatrix(int * A, int n)
{
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d ",A[i*n + j]);
    }
    printf("\n");
  }
}

void scanMatrix(int * A, int n)
{
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d",&A[i*n + j]);
    }
  }
}

void play(int * grid,int steps,int * tmpGrid)
{

  int * tmp;
  int * newGrid=tmpGrid;

 
  for (int gen = 0; gen < steps; gen++)
    {
      cilk_for (int t = 0; t < SIZE*SIZE; t++)
	{
	  int i = t / SIZE;
	  int j = t % SIZE;
	  /*
      	  const int north = i-1<0 ? SIZE-1: i-1;
	  const int south = i+1>SIZE ? 0: i+1;
	  const int west =  j-1<0 ? SIZE-1: j-1;
	  const int east =  j+1>SIZE ? 0: j+1;
	  */
	  int liveNeighbors=0;
	  /*
	    CELL (grid, north, west) + 
	    CELL (grid, north, j) + 
	    CELL (grid, north, east) + 
	    CELL (grid, i, west) +
	    CELL (grid, i, east) + 
	    CELL (grid, south, west) +
	    CELL (grid, south, j) + 
	    CELL (grid, south, east);
	  */
	  
	  for(int i1=i-1;i1<=i+1;i1++) {
	    for(int j1=j-1;j1<=j+1;j1++) {
	      if ( i1<0 || j1<0 || i1>=SIZE || j1>=SIZE)
		{
		  continue;
		}
	      else if(i1==i && j1==j)
		continue;
	      else
		liveNeighbors += CELL (grid, i1, j1);
	    }
	  }
	  
	  
	  const int curr = CELL(grid,i,j);
	  
	  /*
	   * 1. Any live cell with fewer than two live neighbours dies,
	   * as if caused by under­population.
	   * 2. Any live cell with two or three live neighbors 
	   * lives on to the next generation.
	   * 3. Any live cell with more than three live neighbors dies,
	   * as if by overcrowding.
	   * 4. Any dead cell with exactly three live neighbors
	   * becomes a live cell, as if by reproduction.
	   *
	   */
	  if(curr==live)
	    {
	      if(liveNeighbors<2) CELL(newGrid,i,j) = dead;
	      else if(liveNeighbors==2||liveNeighbors==3) CELL(newGrid,i,j) = live;
	      else CELL(newGrid,i,j) = dead;
	    } 
	  else
	    {
	         if(liveNeighbors==3) CELL(newGrid,i,j) = live;
		 else CELL(newGrid,i,j) = dead;
	    }
	}

      
      //swap
      tmp = newGrid;
      newGrid = grid;
      grid = tmp;

#ifdef DEBUG
      printf("Grid: %d \n",gen);      
      printMatrix(grid,SIZE);
      printf("\n");
#endif
    }
}


int main()
{
  
  int * grid,* tmpGrid;
  int steps;
  
  grid = (int*) calloc(SIZE*SIZE, sizeof(int));
  if(grid==NULL)
    {
      perror("Memory Allocation Failed\n");
      return -1;
    }

  tmpGrid = (int*) calloc(SIZE*SIZE, sizeof(int));
  if(tmpGrid==NULL)
    {
      perror("Memory Allocation Failed\n");
      return -1;
    }
  

  scanMatrix(grid,SIZE);
  scanf("%d",&steps);

#ifdef TIMING

#endif
  play(grid,steps,tmpGrid);

  printMatrix(grid,SIZE);


  return 0;
}
