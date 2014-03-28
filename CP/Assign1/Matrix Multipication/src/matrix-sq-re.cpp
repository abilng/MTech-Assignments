#include<cstdio>
#include<cstdlib>
#include<sys/time.h>
#include<cilk/cilk.h>

#define PRINTMAT 0
#define THRESHOLD 8
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

void matrixSq(double *A,double *Sq,int i0,int i1,
	      int j0,int j1,int k0,int k1,int n)
{
  
  int di = i1 - i0;
  int dj = j1 - j0;
  int dk = k1 - k0;
  if (di >= dj && di >= dk && di >= THRESHOLD) {
    int mi = i0 + di / 2;
    cilk_spawn matrixSq(A, Sq, i0, mi, j0, j1, k0, k1,n);
    matrixSq(A, Sq, mi, i1, j0, j1, k0, k1,n);
    cilk_sync;
  } else if (dj >= dk && dj >= THRESHOLD) {
    int mj = j0 + dj / 2;
    cilk_spawn matrixSq(A, Sq, i0, i1, j0, mj, k0, k1,n);
    matrixSq(A, Sq, i0, i1, mj, j1, k0, k1,n);
    cilk_sync;
  } else if (dk >= THRESHOLD) {
    int mk = k0 + dk / 2;
    matrixSq(A, Sq, i0, i1, j0, j1, k0, mk,n);
    matrixSq(A, Sq, i0, i1, j0, j1, mk, k1,n);
  } else {
    // The problem is now small enough - serially.
    for (int i = i0; i < i1; ++i) {
      int irow = i * n;
      for (int j = j0; j < j1; ++j) {
	for (int k = k0; k < k1; ++k){
	  int krow = k * n;
	  Sq[irow + j] += A[irow + k] * A[krow + j];
	}
      }
    }
    
  }
}


void matrixSquare(double* A,double* Sq, unsigned int n)
{
  matrixSq(A,Sq,0,n,0,n,0,n,n);
}


int main(int argc,char * argv[])
{
  unsigned int size;
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


  if(PRINTMAT)
    {
      printf("Matrix A is \n");
      printMatrix(A,size);
      printf("Matrix A^2 is \n");
      printMatrix(B,size);
    }

  free(A);
  free(B);
    
}
