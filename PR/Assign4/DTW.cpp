//============================================================================
// Name        : DTW.cpp
// Author      : abilng
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

#ifdef _MSC_VER
#include <conio.h>
#endif

#define INF (1e30)
#define MArefSize 50
#define BUZZ_SIZE 200
#define DTW_SLOPE 0

using namespace std;

enum status{CMD,OTHER,ERROR};


struct Filelist
{
  string name;
  int n;
  vector<string> filenames;
};

struct RefVectors
{
  double ***ref;
  int *nVectors;
  int n;

  RefVectors(int n)
  {
    this->n = n;
    ref = new double**[n];
    nVectors = new int[n];
  }
};

void FatalError(const char *msg);
status readline(ifstream&,char*,int &);
Filelist* readfileList(char*,int &);
double ** loadData(const string &,int &,int &);
double dist(double *,double *,int);
double DTW(double **,double **,int,int,int);
int getClass(const string filename,RefVectors *refVectors[],int nClass);
int minIndex(double a[],int n);


int main(int argc,char * argv[])
{

  int dim=0,newdim;
  int **confMat;
  Filelist *filelist;
  int nClass;

  if(argc==2)
    filelist=readfileList(argv[1],nClass);
  else
    FatalError("Not enough arg");

  if(filelist==NULL)
    FatalError("No file found");

  RefVectors *refVectors[nClass];


  cout<<"Loading Reference Vectors"<<endl;
  for (int j = 0; j < nClass; ++j) {
    cout<<"Loading: Class "<<filelist[j].name<<endl;
    random_shuffle(filelist[j].filenames.begin(), filelist[j].filenames.end() );
    int refLen = ceil(filelist[j].n*0.25);
    refVectors[j] = new RefVectors(refLen);


#pragma omp parallel for private(newdim) shared(refVectors,filelist,j,dim)
    for(int i =0;i<refLen;i++){
      refVectors[j]->ref[i]=loadData(filelist[j].filenames[i],
        refVectors[j]->nVectors[i],newdim);
      if(dim != newdim){
        if(dim == 0){
          dim = newdim;
        } else {
          FatalError("Error dim Mismatch");
        }
      }
    }

  }
  cout<<"Reference Vectors loaded "<<endl;

  confMat = new int *[nClass];
  for (int i=0; i < nClass; i++)
    confMat[i] = new int[nClass];


  for(int i=0;i<nClass;i++){
    for (int j = 0; j < nClass; ++j) {
      confMat[i][j] = 0;
    }
  }



  cout<<"Testing ...";
  for (int j = 0; j < nClass; ++j) {
    cout<<"Testing : Class "<<filelist[j].name<<endl;
    int refLen = ceil(filelist[j].n*0.25);

#pragma omp parallel for shared(refVectors,filelist,j,dim)
    for(int i =refLen;i<filelist[j].n;i++){
      int pClass = getClass(filelist[j].filenames[i],refVectors,nClass);
#ifdef DEBUG
      cout<<j<<":"<<pClass<<endl;
#endif
      confMat[j][pClass]++;
    }
  }


  int correct=0,total=0;
  cout<<"Confusion Matrix:"<<endl;
  for(int i=0;i<nClass;i++){
    for (int j = 0; j < nClass; ++j) {
      cout<<confMat[i][j]<<"\t";
      if(i==j)
        correct+=confMat[i][j];
      total+=confMat[i][j];
    }
    cout<<endl;
  }

  cout<<endl;
  cout<<"Accuracy:"<<(double(correct)/total)<<endl;

#ifdef _MSC_VER
  _getch();
#endif

}

int minIndex(double a[],int n)
{
  double smallest = a[0];
  int index=0;
  for (int i=1; i<n; ++i) {
    if (smallest > a[i]) {
      smallest = a[i];
      index = i;
    }
  }
  return index;
}
int getClass(const string filename,RefVectors *refVectors[],int nClass)
{
  int dim, nVectors;
  double **testVector =loadData(filename,nVectors,dim);
  if(testVector == NULL)
    return -1;

  double minDist=INFINITY;
  int classNo;

#pragma omp parallel for shared(minDist,classNo)
  for (int j = 0; j < nClass; ++j) {
    double dist=INFINITY;
    int refLen = refVectors[j]->n;
    for(int i =0;i<refLen;i++){
      dist=DTW(refVectors[j]->ref[i],testVector,refVectors[j]->nVectors[i],
        nVectors,dim);

#ifdef DEBUG
        printf("ref:%d\t%f\n",j,dist);
#endif

      if(dist<minDist){
        minDist = dist;
        classNo = j;
      }
    }
  }
  return classNo;
}

double ** loadData(const string &filename,int &nVectors,int &dim)
{
  double ** doubleVec;
  fstream fs;
  string strFloat;
  fs.open(filename.c_str(),ios::in);
  if (!fs.is_open())
    {
      cerr<<"Error:Opening "<<filename<<" failed"<<endl;
      return NULL;
    }

  fs>>nVectors>>dim;

  doubleVec = new double *[nVectors];
  for ( int i=0; i<nVectors;i++)
    doubleVec[i] = new double[dim];

  for ( int i = 0; i < nVectors; i++ ) {
    for ( int j = 0; j < dim; j++ ){
      fs>> doubleVec[i][j];
    }
  }

  fs.close();
  return doubleVec;
}


double dist(double * v1,double * v2,int dim)
{
  double dist = 0;
  for(int i = 0; i<dim; i++) {
    dist = dist + (v1[i]-v2[i])*(v1[i]-v2[i]);
  }
  return sqrt(dist);
}



double DTW(double **ref,double **signal,int refSize,int signalSize,int dim)
{
  int i,j;
  double **DTWtable;
  double distance;

  int maxJ;
  int minJ;
  int tempJ;
  double tempcost;
  double temp = 0.0;
  int mink = -1;
  double minc = 1000000.0;

  int slope = DTW_SLOPE;

  //allocate memory to DTWtable
  DTWtable = new double *[signalSize];
  for (i=0; i < signalSize; i++)
    DTWtable[i] = new double[refSize];

  for (i=0; i<signalSize; i++) {
    for (j=0; j<refSize; j++) {
      DTWtable[i][j] = -1.0;
    }
  }
  
  DTWtable[0][0] = dist(ref[0], signal[0],dim);

  for (i=1; i<signalSize; i++) {
    
    if (slope == 0) {
      maxJ = refSize-1;
      minJ = 0;
    } else {
      maxJ = (int)(slope*i)+1;
      tempJ = (int)((refSize-1)*i*(1/slope)/signalSize + 
        (refSize-1)*(1-1/slope))+1;
      
      maxJ = (tempJ>=maxJ)?maxJ:tempJ;
      maxJ = (maxJ<refSize)?maxJ:refSize-1;

      minJ = (int)((refSize-1)*i/((signalSize-1)*slope))-1;
      tempJ = (int)(refSize-1-(signalSize-1-i)*slope)-1;
      
      minJ=(tempJ<=minJ)?minJ:tempJ;
      minJ= (minJ > 0)?minJ:0;
    }

    for (j=minJ; j<=maxJ; j++) {
      tempcost= dist(ref[j], signal[i],dim);
      mink = -1;
      minc = 1000000.0;
      temp = 0.0;

      for (int k=j; k>=minJ; k--) {
        if (DTWtable[i-1][k] >= 0.0) {
          if (minc >DTWtable[i-1][k]) {
            minc = DTWtable[i-1][k];
          }
        }
      }

      DTWtable[i][j] = minc + tempcost;
    }
  }
  distance = DTWtable[signalSize-1][refSize-1];

  //Deallocating Memory
  for (i=0; i < signalSize; i++)
    delete [] DTWtable[i];
  delete [] DTWtable;

  return distance;
}


void FatalError(const char *msg)
{
  cerr<<msg<<endl;
#ifdef _MSC_VER
  _exit(1);
#else
  exit(1);
#endif
}



status readline(ifstream &infile,char *buff,int &line)
{
  while(1)
    {
      //comment
      line++;
      if(!infile.getline(buff, BUZZ_SIZE))
	return ERROR;
      //cout<<line<<":"<<buff<<endl;
      if(buff[0]!='#')
	break;
    }
  if(buff[0]==';')
    {
      return CMD;
    }
  else
    {
      return OTHER;
    }

}

Filelist* readfileList(char *filename,int &n)
{
  int i,j,lineNo=0;
  int classSize,status;
  Filelist * fileList;
  char buff[BUZZ_SIZE],name[MArefSize];

  ifstream fp(filename);
  if(!fp)
    {
      perror("Error:");
      return NULL;
    }

  status = readline(fp,buff,lineNo);
  if(status != CMD)
    {
      cerr<<"Error in File:Line "<<lineNo<<endl;
      return NULL;
    }
  if(sscanf(buff,";Size %d",&n)!=1)
    {
      cerr<<"Error in File:Line "<<lineNo<<endl;
      return NULL;
    }
  fileList = new Filelist[n];

  for(i = 0; i < n;i++)
    {
      status = readline(fp,buff,lineNo);
      //  printf("%s\n",buff);
      if(status != CMD)
	{
	  cerr<<"Error in File:Line "<<lineNo<<endl;
	  return NULL;
	}
      if(sscanf(buff,";Class %s %d",name,&classSize)!=2)
	{
	  cerr<<"Error in File:Line "<<lineNo<<endl;
	  return NULL;
	}

      fileList[i].name = name;
      fileList[i].n = classSize;
      fileList[i].filenames.reserve(classSize);
      for (j = 0; j < classSize; j++)
	{
	  status = readline(fp,buff,lineNo);
	  if(status != OTHER)
	    {
	      cerr<<"[Error] in File:Line "<<lineNo<<endl;
	      cerr<<buff<<endl;
	      return NULL;
	    }
	  if(sscanf(buff,"%s",name)!=1)
	    {
	      cerr<<"[Error] in File:Line "<<lineNo<<endl;
	      return NULL;
	    }
	  fileList[i].filenames.push_back(name);
	}
    }
  fp.close();
  return fileList;
}
