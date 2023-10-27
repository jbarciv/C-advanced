#include "common.h"


/* function that implements a pause of casual duration between 1 and 2 seconds */
void working()
{
    int pause;
    pause = 1000 + (int)(1000*(random()/(float)RAND_MAX));
    usleep(pause*1000); // between 1000 and 2000 miliseconds
}


void Wait (int SEM, int semid, struct sembuf *operation)
{
    operation->sem_num = SEM;       // which semaphore (there may be more than 1!)
    operation->sem_op = -1;         // which operation: +1=signal, -1=wait
    semop(semid, operation, 1);     // send the command
}

void Signal (int SEM, int semid, struct sembuf *operation)
{
    operation->sem_num = SEM;
    operation->sem_op = 1;
    semop(semid, operation, 1);
}
