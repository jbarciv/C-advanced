 
/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                      --> Practice 2 <--

    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: Program for the creation of two pipes, 
    one for communication from parent to child, and another from 
    child to parent (processes). The parent must guess a number 
    chosen by the child (between 0 and 256). To do so, he will 
    send his guesses to the child through the pipe. The child 
    will reply with a message to say if the number is higher, 
    lower or if he has guessed correctly. In case of success, 
    the process ends.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    int nAttempts = 7;    /* Number of father's attempts */

    /* Create field descriptor for each pipe */
    int fdFatherTC[2], fdChildTF[2];

    int status;
    
    /* Variables for both pipes */
    int nReadFatherTC;
    int nReadChildTF;
    char FatherToChild[100];
    char ChildToFather[100];

    /* Seed for the random number */
    srandom(getpid());
    int highRange = 256.0;
    int lowRange = 0.0;
    int possibleGuesses;
    int childGuess;
    int fatherGuess;
    int i=0;

    /* Creates the number of desired pipes*/
    if(pipe(fdFatherTC) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printf("Parent's pipe OK!\n");
     if(pipe(fdChildTF) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printf("Son's pipe OK!\n");

    // Creating a child process
    switch(fork())
    {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            // Child
            printf( "Hello Dady. Guess what number I'm thinking of...\n");
            childGuess = (int)(highRange*random()/RAND_MAX); /* Picks a random number */

            do
            {
                // The child processes reads from the pipe
                switch(nReadFatherTC = read(fdFatherTC[0],FatherToChild,sizeof(FatherToChild)))
                {
                    case -1:
                        perror("read");
                        break;

                    case 0:
                        perror("EOF");
                        break;

                    default:
                        if (!strcmp(FatherToChild,"You win"))
                        {
                            printf("Ok! The number is: %d\n", childGuess);

                            /* The son closes the two pipes on his side */
                            if(close(fdFatherTC[0]) == -1 || close(fdChildTF[1]) == -1)
                                perror("close");
                            exit(EXIT_SUCCESS);
                        }
                        else
                        {
                            fatherGuess = atoi(FatherToChild);
                            if (fatherGuess == childGuess)
                            {
                                printf("Yeah! That's it!\n");
                                if(write(fdChildTF[1],"Yes!",4) == -1)
                                    perror("write");

                                /* The son closes the two pipes on his side */
                                if(close(fdFatherTC[0]) == -1 || close(fdChildTF[1]) == -1)
                                    perror("close");
                                exit(EXIT_SUCCESS);

                            }
                            else if (fatherGuess > childGuess)
                            {
                                printf("Less\n");
                                if(write(fdChildTF[1],"less",4) == -1)
                                    perror("write");
                            }
                            else
                            {
                                printf("More\n");
                                if(write(fdChildTF[1],"more",4) == -1)
                                    perror("write");
                            }
                        }
                }
            } while (1);

        default:
            /* Father - Until number of attempts finish */
            sleep(1);
            do
            {
                possibleGuesses = highRange + lowRange -1;
                fatherGuess = (int) ceil(possibleGuesses / 2.0);

                /* The parent process writes to the pipe */
                printf("Is your number %d ?\n", fatherGuess);
                sprintf(FatherToChild,"%d",fatherGuess);
                if(write(fdFatherTC[1], FatherToChild, sizeof(FatherToChild)) == -1)
                    perror("write");

                /* The parent process reads from his son's pipe */ 
                switch(nReadChildTF = read(fdChildTF[0], ChildToFather, sizeof(ChildToFather)))
                {
                    case -1:
                        perror("read");
                        break;
                    case 0:
                        perror("EOF");
                        break;
                    default:
                        if (!strcmp(ChildToFather,"Yes!"))
                        {   
                            /* The father closes the two pipes on his side */
                            if(close(fdFatherTC[1]) == -1 || close(fdChildTF[0]) == -1)
                                perror("close");

                            /* Father waits son to finish */
                            wait(&status);
                            exit(EXIT_SUCCESS);
                        }
                        else if (!strcmp(ChildToFather,"more"))
                        {
                            lowRange = fatherGuess + 1;
                        }
                        else if (!strcmp(ChildToFather,"less"))
                        {
                            highRange = fatherGuess - 1;
                        }
                        else
                        {
                            printf("error");
                        }
                }
                nAttempts--;
            } while (nAttempts>0);

            printf("Ok, I give up! You win. Please tell me the number...\n");

            /* The parent process writes to the pipe */
            if(write(fdFatherTC[1],"You win", 7) == -1)
                perror("write");

            /* The father closes the two pipes on his side */
            if(close(fdFatherTC[1]) == -1 || close(fdChildTF[0]) == -1)
                perror("close");
            
            /* Father waits son to finish */
            wait(&status);
            exit(EXIT_SUCCESS);
    }  
}
