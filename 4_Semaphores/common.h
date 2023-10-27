#ifndef MY_FUNC_H
#define MY_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

/* Access key to the shared memory area */
#define KEY ((key_t) 2001)

#define SEM_0 0
#define SEM_1 1
#define SEM_2 2
#define BUFFER 5
#define ITERATIONS 20

void working(void);
void Wait(int, int, struct sembuf *);
void Signal(int, int, struct sembuf *);


#endif
