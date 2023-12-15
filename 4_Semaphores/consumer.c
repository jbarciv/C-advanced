/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                      --> Practice 5 <--

    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: Create a program to solve the producer/consumer 
    problem using semaphores to manage access to a shared buffer. 
    The producer adds items when there are free slots, and the 
    consumer takes items when they're available, all while ensuring 
    mutual exclusion to avoid conflicts.
    - Dependencies: common.h, func.c, producer.c
**************************************************************/

#include "common.h"

int main(void)
{
    int iterations = ITERATIONS;
    int semid;
    struct sembuf producer;
    struct sembuf consumer;
    struct sembuf mutex;
    // initializes the seed of the casual numbers
    srandom(getpid());

    // creation of the semaphores
    semid = semget(KEY, 3, IPC_CREAT|0600);

    if(semid == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    producer.sem_flg = 0; /* No option is activated */
    mutex.sem_flg = 0; /* No option is activated */
    consumer.sem_flg = 0; /* No option is activated */

    while(iterations > 0)
    {
        iterations--;
        
        Wait(SEM_1, semid, &consumer);
        Wait(SEM_2, semid, &mutex);
        /* critical section: remove item from buffer*/
        /*------------------------------------------------------*/
        printf("Consumer: items = %d\n", semctl(semid, SEM_1, GETVAL, 0));
        working(); // random sleep
        /*------------------------------------------------------*/     
        Signal(SEM_2, semid, &mutex);
        Signal(SEM_0, semid, &producer);
        if (iterations > ITERATIONS/2) working(); // John takes time to eat the item
    }
    /* Removes the Semaphore */
    semctl(semid, SEM_0, IPC_RMID, 0);  
    semctl(semid, SEM_1, IPC_RMID, 0);
    semctl(semid, SEM_2, IPC_RMID, 0);
    
    printf("The end for John (consumer)!\n");
    return 0;
}
