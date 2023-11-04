/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                 --> Practice 6: Threads <--

    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: Create a program so that thread 1 is suspended
     until thread 2 has done three iterations of its loop. To do 
     this, use a condition variable, and a mutex associated with 
     it.
    - Dependencies: none
**************************************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Global variables
pthread_mutex_t mut ;
pthread_cond_t cond ;

void* wake()
{
    int i = 0;
    printf("\n Hello, I'm thread 1 and I gonna sleep...\n");
    
    pthread_mutex_lock(&mut);
    pthread_cond_wait(&cond, &mut);
    pthread_mutex_unlock(&mut);

    for (i=0; i<3; i++)
    {
        printf("\n Hello, I'm thread 1\n");
        sleep(1);  
    }
    printf("\n T1 says: bye bye !\n");
}

void* up()
{
    int i;
    for (i=0;i<10;i++)
    {   
        printf("\n Hello, soy el thread 2\n" );
        sleep(1);

        if(i==1)
        {
            pthread_mutex_lock(&mut);
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mut);
        }
    }
    printf("\n T2 says: See you later Lucas!\n");
}

int main(void)
{
    pthread_t t1_id,t2_id;
    int err;

    err = pthread_create(&t1_id, NULL, &wake, NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");
    err = pthread_create(&t2_id, NULL, &up, NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");
    sleep(15);
    return 0;
}