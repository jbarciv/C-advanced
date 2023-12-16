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
    - Dependencies: common.h, process_2.c
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
    int id_queue, ret;
    struct msgbuf message;

    /* Seed for the random number */
    srandom(getpid());

    int process1Guess;
    int process2Guess;


    /* Call to the queue creation function */
    id_queue = createqueue(QUEUE_KEY);

    if(id_queue == -1)
    {
        printf("The queue could not be created!\n");
        exit(EXIT_FAILURE);
    }

    /* Initialization of the fields of the structure */
    message.mtype = 1;
    strcpy(message.mtext, "hola soy proceso 1");

    /* Computes the random number */
    printf("Hey buddy! Guess what number I'm thinking of between 0 and 100\n");
    process1Guess = (int)(HIGH_RANGE*random()/RAND_MAX); /* Picks a random number */

    do
    {
        /* Process_1 reads from queue only messages from Process_2 */
        ret = msgrcv(id_queue, &message, sizeof(message.mtext), 2, 0);
        if(ret == -1)
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        } 

        if (!strcmp(message.mtext,"You win"))
        {
            printf("Ok! The number is: %d\n", process1Guess);

            /* removes the queue from the system */
            ret = msgctl(id_queue, IPC_RMID, (struct msqid_ds*) 0);
            if(ret==-1)
                perror("msgctl");
            else
                printf("The queue has been closed correctly\n");

            exit(EXIT_SUCCESS);
        }
        else
        {
            process2Guess = atoi(message.mtext);
            if (process2Guess == process1Guess)
            {
                printf("Yeah! That's it!\n");
                strcpy(message.mtext, "Yes!");
                message.mtype = 1;
                if(msgsnd(id_queue, &message, sizeof(message.mtext), 0) == -1)
                    perror("msgsnd");

                /* removes the queue from the system */
                ret = msgctl(id_queue, IPC_RMID, (struct msqid_ds*) 0);
                if(ret==-1)
                    perror("msgctl");
                else
                    printf("The queue has been closed correctly\n");

                exit(EXIT_SUCCESS);
            }
            else if (process2Guess > process1Guess)
            {
                printf("Less\n");
                strcpy(message.mtext, "less");
                message.mtype = 1;
                if(msgsnd(id_queue, &message, sizeof(message.mtext), 0) == -1)
                    perror("msgsnd");
            }
            else if (process2Guess < process1Guess)
            {
                printf("More\n");
                strcpy(message.mtext, "more");
                message.mtype = 1;
                if(msgsnd(id_queue, &message, sizeof(message.mtext), 0) == -1)
                    perror("msgsnd");
            }
            else
                printf("Error reading!");
        }
    } while (1);
}