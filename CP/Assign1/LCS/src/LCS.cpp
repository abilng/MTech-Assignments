#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cilk/cilk.h>

#define TOP 1
#define LEFT 2
#define DIAG 3
#define BLOCKSIZE 16


using namespace std;


void printMatrix(int *,int,int );
void LCS(int *,int *,const char *,const char * ,int,int);
string getLCS(int *,string,int,int,int,int);
inline string getLCS(int * B,string s,int length1,int length2);
void readInput(vector<string> &strVector1, vector<string> &strVector2);



void readInput(vector<string> &strVector1, vector<string> &strVector2)
{
  string curStr;
  string line ;
  while(getline(std::cin, line))
    {
      if(line[0]=='>') {
	//comment
	continue;
      } else if(line=="$$$") {
	//EOF
	break;
      } else if(line=="$$") {
	strVector2.push_back(curStr);
	curStr = "";
      } else if(line=="$") {
	strVector1.push_back(curStr);
	curStr = "";
      } else {
	curStr += line ;
      }
    }
}




void LCS(int * C,int * B,const char * s1,const char * s2 ,int length1,int length2)
{

  if(length1==0||length2==0)
    return;
  int nBlock = length1/BLOCKSIZE;
  int mBlock = length2/BLOCKSIZE;
  
  if(mBlock<1) mBlock = 1;
  if(nBlock<1) nBlock = 1;

  for (int slice = 0; slice < nBlock + mBlock - 1; ++slice) {
    //    printf("Slice %d: \n", slice);
    int z1 = slice < mBlock ? 0 : slice - mBlock + 1;
    int z2 = slice < nBlock ? 0 : slice - nBlock + 1;
    
    cilk_for (int k = slice - z2; k >= z1; --k) {
      
      int starti,endi,startj,endj;
      
      starti = k*BLOCKSIZE;
      startj = (slice - k)*BLOCKSIZE;
      endi = (k+1)*BLOCKSIZE;
      endj = (slice - k+1)*BLOCKSIZE;

      
      if(starti==0) starti=1;
      if(startj==0) startj=1;
      if(endi+BLOCKSIZE>length1) endi=length1;
      if(endj+BLOCKSIZE>length2) endj=length2;

      //cout<< starti<<"->"<<endi<<" "<<startj<<"->"<<endj<<endl;

      for(int i=starti; i<endi;i++) {
	for(int j=startj; j<endj;j++) {
	  if(s1[i-1] == s2[j-1])
	    {
	      C[i*length2+j] = C[(i-1)*length2+(j-1)] + 1;
	      B[i*length2+j] = DIAG;
	    }
	  else if(C[(i-1)*length2+j]>= C[i*length2+(j-1)])
	    {
	      C[i*length2+j] = C[(i-1)*length2+j];
	      B[i*length2+j] = TOP;
	    }
	  else
	    {
	      C[i*length2+j] = C[i*length2+(j-1)];
	      B[i*length2+j] = LEFT;
	    }
#ifdef DEBUG
      	  cout<<i<<j<<" "<<i*length2+j<<" ["<<s1[j-1]<<s2[i-1]<<"]"<<endl;
	  printMatrix(C,length1,length2);
	  cout<<endl;
#endif
	}
      }
    }
  }
  
}

string getLCS(int * B,string s,int i,int j,int length1,int length2)
{
  if(i == 0 || j == 0)
    return "";
  if(B[i*length2+j]== DIAG)
    return getLCS(B,s,i-1,j-1,length1,length2)+s[i-1];
  else if(B[i*length2+j]== LEFT)
    return  getLCS(B,s,i,j-1,length1,length2);
  else
    return  getLCS(B,s,i-1,j,length1,length2);
}
inline string getLCS(int * B,string s,int length1,int length2)
{
  return getLCS(B,s,length1-1,length2-1,length1,length2);
}


void printMatrix(int *A,int n,int m)
{
  cout<<n<<"-- "<<m<<endl;
  for(int i=0; i<n; i++)
    {
      for(int j=0; j<m; j++)
	{
	  cout << A[i*m+j]<< "  ";
	}
      cout << endl;
    }

}
 
int main()
{

  int **l,**b;
  int * strlen1;
  int * strlen2;

  int * matchlen;
  string * matchStr; 

  vector<string> strVector1;
  vector<string> strVector2;

  readInput(strVector1,strVector2);

  l = new int*[strVector1.size()];
  b = new int*[strVector1.size()];

  strlen1 = new int[strVector1.size()];
  strlen2 = new int[strVector1.size()];

  matchlen = new int[strVector1.size()];
  matchStr = new string[strVector1.size()];

  for(int i=0;i<strVector1.size();i++)
    {
      strlen1[i] = strVector1[i].length()+1;
      strlen2[i] = strVector2[i].length()+1;
    }

 for(int i=0;i<strVector1.size();i++)
   {
     l[i] = (int*) calloc(strlen1[i]*strlen2[i], sizeof(int));
     b[i] = (int*) calloc(strlen1[i]*strlen2[i], sizeof(int));
     
     if(l[i]==NULL || b[i]==NULL)
       {
	 cerr<<"Memory Allocation Failed"<<endl;
	 return -1;
       }
     
   }


 cilk_for(int i=0;i<strVector1.size();i++)
   {
     int n = strlen1[i];
     int m= strlen2[i];
     
     LCS(l[i],b[i],strVector1[i].c_str(),
	 strVector2[i].c_str(),n,m);
     
#ifdef DEBUG
     printMatrix(l,str1len,str2len);
     cout<<endl;
#endif
     matchlen[i] = l[i][n*m-1]; 
     matchStr[i] = getLCS(b[i],strVector1[i],n,m);
     
   }

 for(int i=0;i<strVector1.size();i++)
   {
     cout<<matchlen[i]<<" "<<matchStr[i]<<endl;

   }

 for(int i=0;i<strVector1.size();i++)
   {
     free(l[i]);
     free(b[i]);
   }

 delete []l;
 delete []b;
 delete []strlen1;
 delete []strlen2;
 delete []matchStr;
 delete []matchlen;
 
  return 0;
}
