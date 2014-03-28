#include<cstdio>
#include<cstdlib>
#include<sys/time.h>
#include<cilk/cilk.h>


/*
 *Matrix Squaring iterative
 *
 *Matrix as 1D Array:  M[i][j]=M[i*N+j]
 */

void printMatrix(double* A, int n)
{
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%f, ",A[i*n + j]);
    }
    printf("\n");
  }
}

void matrixSquare(double* A,double* Sq, unsigned int n)
{
  if (n < 1) {
    //safe
    return;
  }

  cilk_for(unsigned int i = 0; i < n; ++i) {
    int irow = i * n;
    for (unsigned int k = 0; k < n; ++k) {
      for (unsigned int j = 0; j < n; ++j) {
	int krow = k * n;
	Sq[irow + j] += A[irow + k] * A[krow + j];
      }
    }
  }
}


int main(int argc,char * argv[])
{
  unsigned int size=1024;//for try
  unsigned int time;
  double *A,*B;
  struct timeval start, end;
  
  size=atoi(argv[1]);
  //allocate and init=0
  A = (double*) calloc(size*size, sizeof(double));
  B = (double*) calloc(size*size, sizeof(double));
  if(A==NULL || B==NULL)
    {
      perror("Memory Allocation Failed\n");
      return -1;
    }
  //init A with random [0,1]

  
  cilk_for(int i=0;i< size*size;i++) {
    A[i]= (double) ((i * i) % 1024 - 512) / 512;
    //A[i]= ((double) rand() / (RAND_MAX));
  }


  //squaring Mat
  gettimeofday(&start, NULL);
  matrixSquare(A,B,size);
  gettimeofday(&end, NULL);

  time = (1000000 * end.tv_sec + end.tv_usec)-
    (1000000 * start.tv_sec + start.tv_usec);
  printf("Run Time:%d\n",time);

#ifdef PRINTMAT
  printf("Matrix A is \n");
  printMatrix(A,size);
  printf("Matrix A^2 is \n");
  printMatrix(B,size);
#endif

  free(A);
  free(B);
    
}
