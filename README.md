# C-advanced
This repository hosts the primary assignments for the Advanced Programming course within the Master's program in Robotics at the Polytechnical University of Madrid, under the guidance of Professor Claudio Rossi.

## Content

1. [Pipes](#1-processes-and-communication-with-pipes)
2. [Queues](#2-processes-and-communication-with-queues)
3. [Shared Memory](#3-shared-memory-with-busy-waiting)
1. [Shemaphores](#4-shemaphores)
2. [Threads](#5-threads)
1. [Sockets](#6-sockets)
2. [Trees](#7-dynamic-structures)


## Usage

### **1.** Processes and communication with **Pipes**
```
gcc pipes.c -lm -o pipes
```
### **2.** Processes and communication with **Queues**
```
gcc process_1.c -o process_1
gcc process_2.c -lm -o process_2
./process_1 & ./process_2
```
### **3.** **Shared memory** with *busy waiting*
```
gcc process_1.c -o process_1
gcc process_2.c -lm -o process_2
./process_1 & ./process_2
```
### **4.** **Shemaphores**
```
gcc producer.c func.c -o producer
gcc consumer.c func.c -o consumer
# Better to run it on different terminals.
./producer
./consumer
# In the first half of the total number of iterations, the producer will be faster than the consumer, but in the second half the roles will be switched.
```
### **5.** **Threads**

The `wake_up.c` file contains a mutual exclusion (mutex) in threads.
```
gcc wake_up.c -o wake_up -lpthread
./wake_up
```
The `thr_sync_strict_alt_lost_wakeups.c` file contains a *strict alternation* between threads with the use of *condition variables*.
```
gcc thr_sync_strict_alt_lost_wakeups.c -o thr -lpthread
./thr
```
### **6.** **Sockets**

It is a very simple example of client-server comunnication with the TCP and UDP protocols.

```
gcc TCP_server.c -o server
gcc TCP_client.c -o client
# Better to run on different terminals. And remember to launch always the server firts.
./server
# In other terminal
./client 127.0.0.1 5000
```
the same with the UDP files.

### **7.** **Dynamic Structures**

This folder includes a simple code for the creation of random vectors between 1 and 100 and their subsequent sorting by recursion and the construction of a dynamic sorted tree.
```
gcc main.c functions.c -o sorting
./sorting
```
modify `SIZE` in `common.h` for a different vector size.

