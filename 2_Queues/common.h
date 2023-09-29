#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

/* Definition of the queue key */
#define QUEUE_KEY 1999
#define HIGH_RANGE 100.0
#define LOW_RANGE 0.0

struct msgbuf{
    long mtype;
    char mtext[100];
};



