
//////////////////////////////////////////////////////////////////////////////////////
// MASTER IN ROBOTICS
//   ETSII - UPM
//
// LOST WAKEUPS EXAMPLE (Practice 6)
// Advanced Programming
// Claudio Rossi 2022
//
// Student: Josep Maria Barbera Civera (November 2023)
// ID: 17048
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t  mut;
pthread_cond_t   cond1, cond2 ;
int wakeup1 = 0;
int wakeup2 = 0;

void pausa()
{
  int pausa;
  pausa = 500 + (int)(1000*(random()/(float)RAND_MAX));  // between 1000 and 3000 microseconds
  usleep(pausa*1000);  // between 1000 and 3000 milliseconds (1 to 3 seconds)
}

void* function1(void *arg)
{
  int i = 0;
  pthread_t my_id = pthread_self();

  for (i=0; i<10; i++)
  {
	  pthread_mutex_lock(&mut);  
	  printf("\n Thread 1 (%lu) wait...\n", (unsigned long) my_id);
    while (!wakeup1)
    { 
      pthread_cond_wait(&cond1, &mut);
    }
    wakeup1--;
	  printf("\n Thread 1 (%lu) fine wait...\n",my_id);
	  pthread_mutex_unlock(&mut);
  
	  printf("\n I'm thread 1 (%lu) INSIDE my critical section...\n", (unsigned long) my_id);
	  pausa();

	  pthread_mutex_lock(&mut);
	  printf("\n Thread 1 (%lu) signal...\n", (unsigned long) my_id);
	  pthread_cond_signal(&cond2);
    wakeup2++;
	  pthread_mutex_unlock(&mut);

	  printf("\n I'm thread 1 (%lu) OUT of my critical section...\n", (unsigned long) my_id);
	  pausa();
  }

  return NULL;
}
 
void* function2(void *arg)
{
  pthread_t my_id = pthread_self();
  int i;

  // It is necessary to send a signal so that the first thread can move forward
  // and does not block in the wait.
    
  pthread_mutex_lock(&mut);
  printf("\n Thread 2 (%lu) signal...\n", my_id);
  pthread_cond_signal(&cond1);
  wakeup1++;
  pthread_mutex_unlock(&mut);
	
  for (i=0;i<10;i++)
  {
	  pthread_mutex_lock(&mut);
	  printf("\n Thread 2 (%lu) wait...\n", my_id);
    while (!wakeup2)
    {
	    pthread_cond_wait(&cond2, &mut);
    }
    wakeup2--;
	  printf("\n Thread 2 (%lu) fine wait...\n", my_id);
	  pthread_mutex_unlock(&mut);
  
	  pausa();
	  printf("\n I'm thread 2 (%lu) INSIDE my critical section...\n", (unsigned long) my_id);
  
	  pthread_mutex_lock(&mut);
	  printf("\n Thread 2 (%lu) signal...\n", (unsigned long) my_id);
	  pthread_cond_signal(&cond1);
    wakeup1++;
	  pthread_mutex_unlock(&mut);
  
	  printf("\n I'm thread 2 (%lu) OUT of my critical section...\n", (unsigned long) my_id);
	  pausa();
  }

  return NULL;
}
 

int main(void)
{
  pthread_t t1_id, t2_id;
  int i, err;
  float x = 0.123;

  pthread_mutex_init(&mut,NULL);
  pthread_cond_init(&cond1,NULL);
  pthread_cond_init(&cond2,NULL);
	 
  err = pthread_create(&t1_id, NULL, &function1, NULL);
  if (err != 0)
    printf("\ncan't create thread :[%s]", strerror(err));
  else
    printf("\n Thread created successfully\n");
  
  err = pthread_create(&t2_id, NULL, &function2, &x);
  if (err != 0)
    printf("\ncan't create thread :[%s]", strerror(err));
  else
    printf("\n Thread created successfully\n");
  
  printf("\n I'm the main process, I'm waiting for the threads to finish...\n");
  
  pthread_join(t1_id, NULL);
  printf("\n T1 has finished\n");

  pthread_join(t2_id, NULL);
  printf("\n T2 has finished\n");

  return 0;
} 