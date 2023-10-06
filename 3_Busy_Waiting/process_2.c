/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                      --> Practice 4 <--

    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: The code creates shared memory for communication 
    between two processes. Process 1 guesses a number chosen by 
    Process 2 (between 0 and 100) by writing attempts into shared 
    memory. Process 2 responds in shared memory, indicating if 
    the guess is greater, smaller, or correct. They use busy 
    waiting for synchronization.
    - Dependencies: common.h, process_1.c
**************************************************************/

#include "common.h"

/* Main function */
int main(void)
{
    int shmid;
    int res;
    data *shared_memory;

   /* Seed for the random number */
    srandom(getpid());

    int hisGuess;
    int theNumber;

    /* Computes the random number */
    printf("Hey buddy! Guess what number I'm thinking of between 0 and 100\n");
    theNumber = (int)(HIGH_RANGE*random()/RAND_MAX); /* Picks a random number */

    shmid = shmget(SHM_KEY, sizeof(data), IPC_CREAT|0666);
    if(shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    /* Attach and initialize shared memory (identical in process 2)*/
    shared_memory = (data*) shmat(shmid, 0, 0);
    /* Process 2 grants preference to process 1 */
    shared_memory->turn = 1;
    strcpy(shared_memory->message, "init");
    
    do
    {
        while(shared_memory->turn != 2) {/*busy wait*/ }

        /* Beginning of Critical Section */
        hisGuess = shared_memory->guess;
        if (hisGuess > HIGH_RANGE)
        {
            printf("Ok! The number is: %d\n", theNumber);

            /* Removing shared memory */
            shmctl(shmid, IPC_RMID,0);
            if(res == -1)
            {           
                perror("shmctl");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);   
        }
        else
        {
            if (hisGuess == theNumber)
            {
                printf("Yeah! That's it!\n");
                strcpy(shared_memory->message, "Yes!");
                shared_memory->turn = 1;
                exit(EXIT_SUCCESS);  
            }
            else if (hisGuess > theNumber)
            {
                printf("Less\n");
                strcpy(shared_memory->message, "less");
            }
            else if (hisGuess < theNumber)
            {
                printf("More\n");
                strcpy(shared_memory->message, "more");
            }
            else
                printf("Error reading!");
        }
        shared_memory->turn = 1;
        /* End of Critical Section */
        
    } while (1);
    

}