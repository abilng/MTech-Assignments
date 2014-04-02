/*
 * DTW.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: abil
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>


#define REF_LEN 3
#define MAX 20
using namespace std;

struct TestInfo
{
    int start[MAX];
    int end[MAX];
    int trueClass[MAX];
    int pClass[MAX];
    int n;
};

double DTW(vector<double> x,vector<double> y)
{
  int i,j;
  double **Dist;
  double **DTWtable;
  double distance;

  int xsize = x.size();
  int ysize = y.size();

  //allocate memory to dist
  Dist = new double *[xsize];
  for (i=0; i < xsize; i++)
    Dist[i] = new double[ysize];

  //#pragma omp parallel
  for(i=0; i<xsize;i++) {
    for(j=0;j<ysize;j++) {
      Dist[i][j] = abs(x[i]-y[j]);
    }
  }

  //allocate memory to DTWtable
  DTWtable = new double *[xsize];
  for (i=0; i < xsize; i++)
    DTWtable[i] = new double[ysize];

  DTWtable[0][0] = Dist[0][0];
  for(i=1;i<xsize;i++)
    DTWtable[i][0] = Dist[i][0] + DTWtable[i-1][0];

  for(j=1;j<ysize;j++)
    DTWtable[0][j] = Dist[0][j] + DTWtable[0][j-1];

  for(i=1;i<xsize;i++) {
   // for(j=max(1,i-w); j<min(ysize,i+w);j++){
    for(j=1; j<ysize;j++){
        DTWtable[i][j] = Dist[i][j] +
          min(DTWtable[i][j-1],min(DTWtable[i-1][j-1],DTWtable[i-1][j]));
      //    | (i,j-1)  | (i,j) |
      //    | (i-1,j-1)|  ---  |

      /*

      double minDist = DBL_MAX;
      for(int k=1; k<ysize;k++){
        minDist = min(Dist[i][k] + DTWtable[i-1][k],minDist);
      }
      DTWtable[i][j] = minDist;

      */
    }
  }

  distance = Dist[xsize-1][ysize-1];

  //Deallocating Memory
  for (i=0; i<xsize; ++i)
    delete [] Dist[i];
  delete [] Dist;
  for (i=0; i<xsize; ++i)
    delete [] DTWtable[i];
  delete [] DTWtable;

  return distance;
}


bool loadData(const string &filename,vector<double> &doubleVec)
{
  fstream fs;
  string line;
  //double fNum;
  fs.open(filename.c_str(),ios::in);
  if (!fs.is_open())
  {
    cerr<<"Error:Opening "<<filename<<" failed"<<endl;
    return false;
  }

  while(fs>>line){
    if(line.size() == 0)
      continue;
    if(line=="-Inf")
      doubleVec.push_back(-1*DBL_MAX);
    else
      doubleVec.push_back(atof(line.c_str()));
  }
  fs.close();
  return true;
}


bool readGroundTruth(TestInfo gt[],const string filename[],int nTest,
    string classNames[],int nClass)
{

  fstream fs;
  string line;
  double start;
  double end;
  string className;

  int nLine;
  for (int i = 0; i < nTest; ++i) {
    nLine = 0;
    fs.open(filename[i].c_str(),ios::in);
    if (!fs.is_open())
    {
      cerr<<"Error:Opening "<<filename[i]<<" failed"<<endl;
      return false;
    }

    while(getline(fs,line))
    {
      if(line.length()==0)
        continue;
      stringstream  linestream(line);
      linestream>>start;
      linestream>>end;
      linestream>>className;

      gt[i].start[nLine]=floor(start*100);
      gt[i].end[nLine]=floor(end*100);
      gt[i].trueClass[nLine] = -1;
      for(int j =0; j<nClass;j++) {
        if(className == classNames[j]){
          gt[i].trueClass[nLine]=j;
          break;
        }
      }
      if(gt[i].trueClass[nLine] == -1)
        cerr<<"ERROR:["<<filename[i]
            <<"] Unknown Class:"<<className<<endl;
      ++nLine;
    }
    fs.close();
    gt[i].n = nLine;
  }
  return true;
}


int getClass(vector<double> testVector,vector<double> refVectors[],int nClass,int start,int end)
{

  vector<double>::const_iterator first = testVector.begin() + start;
  vector<double>::const_iterator last = testVector.begin() + end;
  vector<double> testVectorSlice(first, last);

  double classDist[nClass];

#pragma omp parallel for shared(classDist)
  for (int j = 0; j < nClass; ++j) {
    classDist[j]=DTW(refVectors[j],testVectorSlice);
    //cout<<"("<<j<<")"<<classDist[j]<<"\t";
  }

  double minDist=DBL_MAX;
  int minIndex = -1;
  for(int i=0;i<nClass;i++){
    if(classDist[i]<minDist){
      minDist=classDist[i];
      minIndex=i;
    }
  }
  //cout<<minIndex;
  //cout<<endl;
  return minIndex;
}




int main()
{

  int nClass = 3;

  int confMat [nClass][nClass];
  vector<double> ref[nClass];

  int nTest = 16;
  vector<double> testVectors[nTest];


  string refFilename[] = {
      "Music Data/Bhairavi_Ref/Bhairavi_44100.vp1.wav.cent.spline1",
      "Music Data/Bhairavi_Ref/Bhairavi_44100.vp2.wav.cent.spline1",
      "Music Data/Bhairavi_Ref/Bhairavi_44100.vp3.wav.cent.spline1"
  };

  string classNames[] = {
      "VI_VP1",
      "VI_VP2",
      "VI_VP3"
  };

  string labelFilename[] = {
      "Music Data/Bhairavi_Test_Ground_Truth/VS_Bhairavi1_289VSKozhikode.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/TVS_Bhairavi1_Sigamani3dvd8062.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/TMK_Bhairavi3_US2002Toronto.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/TMK_Bhairavi2_NJ05.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/Sanjay_Bhairavi1_FASfeb2001.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/RK_Bhairavi1_1964jamshedpur.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/Nedanuri_Bhairavi1_concert40tmk1tb.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/Musiri_Bhairavi1_musirinew.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/MSS_Bhairavi2_MSSConcertIX.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/MSS_Bhairavi1_academy1970.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/MDR_Bhairavi1_065MDRhari101.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/KVN_Bhairavi2_NF117.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/KVN_Bhairavi1_NF598KVN.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/GNB_Bhairavi1_0641965kallidaikurichi.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/ARI_Bhairavi1_aritnkpmi1ssrk.wav.lab",
      "Music Data/Bhairavi_Test_Ground_Truth/ALB_Bhairavi1_70albmgpnganesan.wav.lab"
  };

  string testFilename[]={
      "Music Data/Bhairavi_Test/VS_Bhairavi1_289VSKozhikode.wav.cent.spline1",
      "Music Data/Bhairavi_Test/TVS_Bhairavi1_Sigamani3dvd8062.wav.cent.spline1",
      "Music Data/Bhairavi_Test/TMK_Bhairavi3_US2002Toronto.wav.cent.spline1",
      "Music Data/Bhairavi_Test/TMK_Bhairavi2_NJ05.wav.cent.spline1",
      "Music Data/Bhairavi_Test/Sanjay_Bhairavi1_FASfeb2001.wav.cent.spline1",
      "Music Data/Bhairavi_Test/RK_Bhairavi1_1964jamshedpur.wav.cent.spline1",
      "Music Data/Bhairavi_Test/Nedanuri_Bhairavi1_concert40tmk1tb.wav.cent.spline1",
      "Music Data/Bhairavi_Test/Musiri_Bhairavi1_musirinew.wav.cent.spline1",
      "Music Data/Bhairavi_Test/MSS_Bhairavi2_MSSConcertIX.wav.cent.spline1",
      "Music Data/Bhairavi_Test/MSS_Bhairavi1_academy1970.wav.cent.spline1",
      "Music Data/Bhairavi_Test/MDR_Bhairavi1_065MDRhari101.wav.cent.spline1",
      "Music Data/Bhairavi_Test/KVN_Bhairavi2_NF117.wav.cent.spline1",
      "Music Data/Bhairavi_Test/KVN_Bhairavi1_NF598KVN.wav.cent.spline1",
      "Music Data/Bhairavi_Test/GNB_Bhairavi1_0641965kallidaikurichi.wav.cent.spline1",
      "Music Data/Bhairavi_Test/ARI_Bhairavi1_aritnkpmi1ssrk.wav.cent.spline1",
      "Music Data/Bhairavi_Test/ALB_Bhairavi1_70albmgpnganesan.wav.cent.spline1"
  };

  //loading ref file
  cout<<"Loading Query Vectors"<<endl;
  for(int i=0;i<nClass;i++){
    loadData(refFilename[i],ref[i]);
#ifdef DEBUG
    cout<<"loaded "<<refFilename[i]
        <<"("<<ref[i].size()
        <<")"<<endl;
#endif
  }
  cout<<"Query Vectors:Loaded "<<endl<<endl;


  cout<<"Loading Test Vectors"<<endl;
  for(int i=0;i<nTest;i++){
    loadData(testFilename[i],testVectors[i]);
#ifdef DEBUG
    cout<<"loaded "<<testFilename[i]
        <<"("<<testVectors[i].size()
        <<")"<<endl;
#endif
  }
  cout<<"Test Vectors:Loaded "<<endl<<endl;

  TestInfo gtruth[nTest];

  readGroundTruth(gtruth,labelFilename,
      nTest,classNames,nClass);


  for(int i=0;i<nClass;i++){
    for (int j = 0; j < nClass; ++j) {
      confMat[i][j] = 0;
    }
  }

  for(int i=0;i<nClass;i++){
      for (int j = 0; j < nClass; ++j) {
        cout<<confMat[i][j]<<"\t";
      }
      cout<<endl;
    }


  for(int i=0;i<nTest;i++){
    for (int j = 0; j < gtruth[i].n; ++j) {
      gtruth[i].pClass[j] = getClass(testVectors[i],
          ref,nClass,gtruth[i].start[j],gtruth[i].end[j]);

#ifdef DEBUG
      cout<<i<<" =>"
          <<gtruth[i].start[j]<<"  "
          <<gtruth[i].end[j]<<"  "
          <<gtruth[i].end[j]-gtruth[i].start[j]<<" "
          <<gtruth[i].trueClass[j];
      cout<<"==>"<<gtruth[i].pClass[j]<<endl;
#endif
       confMat[gtruth[i].trueClass[j]][gtruth[i].pClass[j]]++;
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

}

