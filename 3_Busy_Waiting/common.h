#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* Access key to the shared memory area */
#define SHM_KEY ((key_t) 2001)

#define HIGH_RANGE 100.0
#define LOW_RANGE 0.0

/* Data structure that is shared in the shared memory area */
typedef struct
{
    int turn;
    int guess;
    char message[10];
} data;