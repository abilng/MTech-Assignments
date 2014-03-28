#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <set>

#define N 25
#define L 100000

pthread_mutex_t bakery_entry;
void *student( void *arg );
void *Professor( void *arg );
int signal_professor=0 , critical_section[1024],cs=0,token=0 ,ques_no;
void *student_scheduler(void *arg);
void Question_Start(int );
void Question_Done(int, int );
void Bakery(int i);
void set(int);
void reset(int);
void Answer_Done();
void Answer_Start();
int question_done_signal=0, answer_done_signal=0,prof_ready_signal=0,pre_ready_signal=0;


void *student_scheduler(void* arg)
{
  std::set<int> myset;
  std::set<int>::iterator it;
  pthread_t thread[N];
  int random[1024],ran,i=0;
  srand(time(NULL));
  while(i<N){
    
  int no_of_std = (rand()%N)+1;
  for(;i<no_of_std;i++){
    l: random[i] = (rand()%N);
    if((myset.insert(random[i])).second==false) goto l;
    ran=random[i];
    pthread_create(&thread[ran],NULL, student,(void *) &random[i]); 
    usleep(2*L);
  }
  }
 for(int j=0;j<i;j++)
  {
    ran=random[j];
    pthread_join(thread[ran],NULL);
  }
    
 /* for(int z=0;z<cs;z++)
    printf("\n%2d\n",critical_section[z]);
  printf("\n%d\n",i);*/
  pthread_exit(NULL);
}



main( int argc, char *argv[] )
{
     
     pthread_t     std_gen;
     pthread_t     prof_gen;
     int           arg1 = 1;
     int           arg2 = 2;
     
     //pthread_create( &thread, NULL, ( void * ) , ( void * ) &arg1 );
     pthread_create( &std_gen, NULL, student_scheduler, ( void * ) &arg1 );
     usleep(1*L);
     pthread_create(&prof_gen,NULL,Professor,(void *) &arg1);
     pthread_join( std_gen, NULL );
    // pthread_join( thread2, NULL );
     
     //return;
}

void* student(void* arg)
{
  int     i= *((int *) arg)+1;
  srand(time(NULL));
  int no_q = rand()%10+1; 
  for(int m=0;m<no_q;m++)
  {
  printf( "Student %2d is ready to ask question\n",i );
  pthread_mutex_lock(&bakery_entry);
  Bakery(i);
  pthread_mutex_unlock(&bakery_entry);
  Question_Start(i);
  ques_no=m+1;
  while(prof_ready_signal==0);
  printf("Student %2d is asking question %2d\n",i,ques_no);
  usleep(2*L);
  printf("Student %2d is done asking question %2d\n",i,ques_no);
  //signal professor
  question_done_signal=1;
  while(answer_done_signal==0);
  answer_done_signal=0;
  pre_ready_signal=1;
  //wait for professor's signal
  Question_Done(i,ques_no);
  usleep((rand()%10+1)*L);
  //sched_yield();
  }   
  //return;
}
void Question_Start(int i){
    //he should acquire lock or busy wait
   // printf( "Student %2d is ready to ask question\n",i );
    while(critical_section[token]!=i)
    {
     //sleep(rand()%8+1);
    usleep(1*L);
    }
  }
  
void Question_Done(int i,int ques_no){
  //Should release lock here
  printf("Student %2d got his answer for question %2d\n\n",i,ques_no);
  pre_ready_signal=0;
  token++;
}

void Bakery(int i){
  critical_section[cs++]=i;
}


void* Professor(void *arg)
{
  while(true)
  {
    while(pre_ready_signal!=0);
    printf("The professor is ready to answer questions\n");
    Answer_Start();
    printf("The professor is answering question %2d for student %2d\n",ques_no,critical_section[token]);
    usleep((rand()%14+2)*L);
    Answer_Done();
    if(token==cs-1) {
     // while(pre_ready_signal==0);
     usleep(L/10);
      printf("\n\nNo more questions from students\nThe professor goes to sleep\n");
      pthread_exit(NULL);
    }
  }
}

void Answer_Start(){
prof_ready_signal=1;
    while(question_done_signal==0);
    question_done_signal=0;  
}

void Answer_Done(){
  printf("The professor answered the question %2d for student %2d\n",ques_no,critical_section[token]);
    prof_ready_signal=0;
    answer_done_signal=1;
}

void set(int x)
{
  x=1;
}
void reset(int x)
{
  x=0;
}