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
    - Dependencies: common.h, process_2.c
**************************************************************/

#include "common.h"


/* Main function */
int main(void)
{
    int shmid;
    int res;
    data *shared_memory;
    int nAttempts = 6;    /* Number of attempts */

    int possibleGuesses;
    int myGuess;
    char hisMessage[10];
    int highRange = HIGH_RANGE;
    int lowRange = LOW_RANGE;

    shmid = shmget(SHM_KEY, sizeof(data), IPC_CREAT|0666);
    if(shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    /* Attach and initialize shared memory (identical in process 2)*/
    shared_memory = (data*) shmat(shmid, 0, 0);

    do
    {
        while(shared_memory->turn != 1) {/*busy wait*/ }
        /* Beginning of Critical Section */
        /* First I read his message */
        strcpy(hisMessage, shared_memory->message);
        /* If I have won I finish and close the shared memory*/
        if (!strcmp(hisMessage,"Yes!"))
        {   
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
            /* I have not won, so I check if I have any attempts left */
            if (nAttempts == 0)
            {
                shared_memory->guess = 101;
                shared_memory->turn = 2;
                printf("Ok, I give up! You win. Please tell me the number...\n");
                shared_memory->turn = 2;
                exit(EXIT_SUCCESS);
            }
            /* I have more attempts*/
            else
            {
                if(!strcmp(hisMessage,"init"))
                {   
                    /* It is the beginning there is trash in the message buffer */
                }
                else if (!strcmp(hisMessage,"more"))
                {
                    lowRange = myGuess + 1;
                }
                else if (!strcmp(hisMessage,"less"))
                {
                    highRange = myGuess - 1;
                }
                possibleGuesses = highRange + lowRange - 1;
                myGuess = (int) ceil(possibleGuesses / 2.0);
                shared_memory->guess = myGuess;
                printf("Is your number %d?\n", myGuess);
                shared_memory->turn = 2;
            }
        }
        /* End of Critical Section */
        nAttempts--;
    } while (1);
}