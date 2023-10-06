# C-advanced
This repository hosts the primary assignments for the Advanced Programming course within the Master's program in Robotics at the Polytechnical University of Madrid, under the guidance of Professor Claudio Rossi.

## Content

**1.** Processes and communication with **Pipes**
```
gcc pipes.c -lm -o pipes
```
**2.** Processes and communication with **Queues**
```
gcc process_1.c common.h -o process_1
gcc process_2.c common.h -lm -o process_2
./process_1 & ./process_2
```
**3.** **Shared memory** with *busy waiting*
```
gcc process_1.c common.h -o process_1
gcc process_2.c common.h -lm -o process_2
./process_1 & ./process_2
```