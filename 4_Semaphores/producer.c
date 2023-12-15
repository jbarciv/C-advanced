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
    - Dependencies: common.h, func.c, consumer.c
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

    // creation of two semaphore
    semid = semget(KEY, 3, IPC_CREAT|0600);

    if(semid == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    /* semaphore initialization: buffer is empty ready to be filled*/
    semctl(semid, SEM_0, SETVAL, BUFFER);
    printf("Semaphore %d value: %d\n", SEM_0, semctl(semid, SEM_0, GETVAL, 0));
    producer.sem_flg = 0; /* No option is activated */


    /* semaphore initialization: buffer is empty of items */
    semctl(semid, SEM_1, SETVAL, 0);
    printf("Semaphore %d value: %d\n", SEM_1, semctl(semid, SEM_1, GETVAL, 0));
    consumer.sem_flg = 0; /* No option is activated */

    /* the buffer needs a mutex between the processes */
    semctl(semid, SEM_2, SETVAL, 1);
    printf("Semaphore %d value: %d\n", SEM_2, semctl(semid, SEM_2, GETVAL, 0));
    mutex.sem_flg = 0; /* No option is activated */


    while(iterations > 0)
    {
        iterations--;

        if (iterations < ITERATIONS/2) working(); // Jerry takes time to prepare a new item
        
        Wait(SEM_0, semid, &producer);
        Wait(SEM_2, semid, &mutex);
        
        /* critical section: insert item on buffer*/
        /*------------------------------------------------------*/
        printf("Producer: slots = %d\n", BUFFER-semctl(semid, SEM_0, GETVAL, 0));
        working(); // random sleep
        /*------------------------------------------------------*/
        Signal(SEM_2, semid, &mutex);
        Signal(SEM_1, semid, &consumer);
    }
    /* Removes the Semaphores */
    semctl(semid, SEM_0, IPC_RMID, 0);
    semctl(semid, SEM_1, IPC_RMID, 0);
    semctl(semid, SEM_2, IPC_RMID, 0);
    
    printf("The end for Jerry (producer)!\n");
    return 0;
}
