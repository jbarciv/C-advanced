# C-advanced
This repository hosts the primary assignments for the Advanced Programming course within the Master's program in Robotics at the Polytechnical University of Madrid, under the guidance of Professor Claudio Rossi.

## Content

**1.** Processes and communication with **Pipes**
```
gcc pipes.c -lm -o pipes
```
**2.** Processes and communication with **Queues**
```
gcc process_1.c -o process_1
gcc process_2.c -lm -o process_2
./process_1 & ./process_2
```
**3.** **Shared memory** with *busy waiting*
```
gcc process_1.c -o process_1
gcc process_2.c -lm -o process_2
./process_1 & ./process_2
```
**4.** **Shemaphore**
```
gcc producer.c func.c -o producer.c
gcc consumer.c func.c -o consumer.c
```
better to run it on different terminals. In the first half of the total number of iterations, the producer will be faster than the consumer, but in the second half the roles will be switched.