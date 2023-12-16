/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                      --> Practice 2 <--

    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: Create a message queue for communication 
    between two processes. One will have to guess a 
    number chosen by the other (between 0 y 100). Use the 
    "mtype" field of the msgbuf structure to identify the 
    messages.
    - Dependencies: common.h, process_1.c
    - Execute: I recommend to launch process_1 and process_2 in
    two different consoles. Or use "&"" for executing in 
    background.
**************************************************************/

#include "common.h"

/* Auxiliary function which creates the queue, returning the identifier */
int createqueue(int key)
{
    int msgqid;
    msgqid = msgget(key, IPC_CREAT|0666);
    switch(msgqid)
    {
        case -1:
            perror("msgget");
            return(-1);
        default:
            return msgqid;
    }
} /* End auxiliary function */

/* Main function */
int main(void)
{
    int nAttempts = 6;    /* Number of attempts */
    int id_queue, ret;
    struct msgbuf message;

    int possibleGuesses;
    int myGuess;
    int highRange = HIGH_RANGE;
    int lowRange = LOW_RANGE;

    /* Call to the queue creation function */
    id_queue = createqueue(QUEUE_KEY);

    if(id_queue == -1)
    {
        printf("The queue could not be created!\n");
        exit(EXIT_FAILURE);
    }

    /* Initialization of the fields of the structure */
    message.mtype = 2;

    do
    {
        possibleGuesses = highRange + lowRange -1;
        myGuess = (int) ceil(possibleGuesses / 2.0);
        
        printf("Is your number %d?\n", myGuess);
        sprintf(message.mtext, "%d", myGuess);
        message.mtype = 2;
        if(msgsnd(id_queue, &message, sizeof(message.mtext), 0) == -1)
            perror("msgsnd");
        /* Process_2 reads from queue Process_1's messages */
        ret = msgrcv(id_queue, &message, sizeof(message.mtext), 1, 0);
        if(ret == -1)
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        if (!strcmp(message.mtext,"Yes!"))
        {   
            exit(EXIT_SUCCESS);
        }
        else if (!strcmp(message.mtext,"more"))
        {
            lowRange = myGuess + 1;
        }
        else if (!strcmp(message.mtext,"less"))
        {
            highRange = myGuess - 1;
        }
        else
        {
            printf("error");
        }

        nAttempts--;

    } while (nAttempts > 0);
    
    printf("Ok, I give up! You win. Please tell me the number...\n");
    strcpy(message.mtext, "You win");
    message.mtype = 2;
    if(msgsnd(id_queue, &message, sizeof(message.mtext), 0) == -1)
        perror("msgsnd");
        
    exit(EXIT_SUCCESS);

}