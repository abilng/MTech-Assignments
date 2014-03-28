#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define true 1
#define false 0

#define NDOORS 4
#define DOORSLEEP 10
#define ESLEEP 10
#define CHECKTIME 2000
#define KILLPERCENT 40
#define ENTERPERCENT 10
#define RUNTIME 1

void * door(void *tid);
void * elimination(void *threshold_ptr);

int zombieCount;
int totalKill;
int isOpen[NDOORS];

pthread_mutex_t count_mutex;
pthread_mutex_t door_mutex[NDOORS];
pthread_cond_t doorOpen[NDOORS];

int main(int argc, char *argv[])
{
  pthread_t doors[NDOORS];
  pthread_t etid;
  pthread_attr_t attr;
  int i,err;
  long threshold=10;
  long tids[NDOORS];


  if(argc != 2) {
    printf("Unknown Option\n");
    printf("Usage: %s <threshold> \n",argv[0]);
    exit(3);
  }  else {
    threshold=atoi(argv[1]);
  }


  /* Initialize mutex and condition variable objects */
  pthread_mutex_init(&count_mutex, NULL);
  zombieCount = 0;
  totalKill = 0;
  for(i=0;i<NDOORS;i++)
    {
      isOpen[i] = true;
      pthread_mutex_init(&door_mutex[i], NULL);
      pthread_cond_init (&doorOpen[i], NULL);
      tids[i] = i;
    }

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  err=pthread_create(&etid, &attr, elimination, (void *)threshold);
  if (err != 0)
    printf("Error:Failed to create Armed thread :[%s]", strerror(err));
  else
    printf("[ Main ] : Armed Thread created successfully\n");

  for(i=0;i<NDOORS;i++)
    {
      err=pthread_create(&doors[i], &attr, door, (void *)tids[i]);
      if (err != 0)
        printf("Error:Failed to create Door thread :[%s]", strerror(err));
      else
        printf("[ Main ] : Door(%d) Thread created successfully\n",i);
    } 

  sleep(RUNTIME*60);
  printf("[ MAIN ]:Sending Cancel Signal...\n");
  for (i = 0; i < NDOORS; i++) {
    pthread_cancel(doors[i]);
  }
  pthread_cancel(etid);
 
  for (i = 0; i < NDOORS; i++) {
    pthread_join(doors[i], NULL);
  }
  pthread_join(etid, NULL);

  printf("Total Zombies Eliminated = %d \n",totalKill);
  printf("Zombies Eliminated per sec = %f \n",
	 ((float)totalKill)/(RUNTIME*60));

  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&count_mutex);
  for(i=0;i<NDOORS;i++)
    {
      pthread_mutex_destroy(&door_mutex[i]);
      pthread_cond_destroy (&doorOpen[i]);
    }
  pthread_exit (NULL);
}


void * door(void *tid)
{
  long threadid = (long)tid;
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = DOORSLEEP*1000000L;//10ms
  char msg[100];

  sprintf(msg,"[Door %d] : Recived Cancel Signal.\n[Door %d] : Canceling Thread..\n",
	  threadid,threadid);
  pthread_setcancelstate (PTHREAD_CANCEL_ENABLE,NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
  pthread_cleanup_push(printf,msg);
  while(true)
    {
      pthread_mutex_lock(&door_mutex[threadid]);
      while(!isOpen[threadid])
	{
	  printf("Closing Door %ld..\n",threadid);
	  printf("Waiting For signal to open Door %ld..\n",threadid);
	  pthread_cond_wait(&doorOpen[threadid], &door_mutex[threadid]);
	  printf("Opening Door %ld...\n",threadid);
	}
      pthread_mutex_unlock(&door_mutex[threadid]);
      if((rand()%100) <= ENTERPERCENT) {
	pthread_mutex_lock(&count_mutex);
	zombieCount++; 
	pthread_mutex_unlock(&count_mutex);
      }      
      nanosleep(&tim,NULL);
    }
  pthread_cleanup_pop(0);
  pthread_exit(NULL);
}
void * elimination(void *threshold_ptr)
{
  long threshold = (long)threshold_ptr;
  int door = true;
  int i=0,t=0,count;
  char msg[100];
  
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = ESLEEP*1000000L;
  
  sprintf(msg,"[ Armed Thread ] : Recived Cancel Signal.\n[ Armed Thread ] : Canceling Thread..\n");
  pthread_setcancelstate (PTHREAD_CANCEL_ENABLE,NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
  pthread_cleanup_push(printf,msg);
  while(true)
    {	  
      if((rand()%100) <= KILLPERCENT) {
	pthread_mutex_lock(&count_mutex);
	if(zombieCount >0) {
	  count = --zombieCount;
	  pthread_mutex_unlock(&count_mutex);
	  totalKill++;
	  printf("[ %4d ]: Killing zombie (%d -> %d)\n",ESLEEP*t,count+1,count); 
	} else 
	  {
	    pthread_mutex_unlock(&count_mutex);
	    printf("[ %4d ]: No zombie to kill\n",ESLEEP*t);
	    pthread_testcancel();
	    count = 0; 
	  }
      }
      else {
	pthread_mutex_lock(&count_mutex);
	count = zombieCount; 
	pthread_mutex_unlock(&count_mutex);
	//printf("%4d: Failed Killing zombie (%d -> %d)\n",ESLEEP*t,count,count); 
      }

      if(!door&&(count<=threshold/2)) {
	/*
	 * if Door is closed and count is below min
	 *  Open door 
	 */
	printf("count below threshold/2\n");
	door =true;
	for(i=0;i<NDOORS;i++) {
	  pthread_mutex_lock(&door_mutex[i]);	  
	  printf("Sending signal to open Door %d\n",i);
	  isOpen[i] = door;
	  pthread_cond_signal(&doorOpen[i]);
	  pthread_mutex_unlock(&door_mutex[i]);
	  t=0;
	}
      }
      if(door && t>=CHECKTIME/ESLEEP) {
	/*
	 * ( checks the total every 2s)
	 * if Door is open and count is above max
	 *  Close door 
	 */
	printf("Checking is count above threshold ?..\n");
	if(count>=threshold) {
	  door = false;
	  for(i=0;i<NDOORS;i++) { 
	    pthread_mutex_lock(&door_mutex[i]);
	    isOpen[i] = door;
	    printf("Sending signal to close Door %d \n",i);
	    pthread_mutex_unlock(&door_mutex[i]);
	  }
	}
	t=1;
      }
      nanosleep(&tim,NULL);
      t++;  
    }
  pthread_cleanup_pop(0);
  pthread_exit(NULL);
}
