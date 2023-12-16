/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                 --> Practice 6: Sockets <--

    - Credit: Professor Claudio Rossi - DISAM
    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: client-server communication via TCP protocol
    This is the client file. Should be executed secondly!
**************************************************************/

#include<sys/types.h> 
#include<sys/socket.h> 
#include<stdio.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<netdb.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
 
#define SERVPORT  5000 
#define BUFFER_SIZE  300


int main(int argc, char*argv[])
{ 
    int ID_serv, p; 
    struct sockaddr_in server_addr; 
    struct hostent  *host_name; 
    char chain[BUFFER_SIZE]; 
 
    ID_serv=socket(AF_INET,SOCK_DGRAM,0);
    
    server_addr.sin_family=AF_INET; 
    server_addr.sin_port = htons(SERVPORT); 
    inet_aton(argv[1],&server_addr.sin_addr); 
    p=sizeof(server_addr); 
       
    while (1)
    { 
        printf("type data to be sent: \n");
        fgets(chain,BUFFER_SIZE,stdin); 
        printf("data to be sent: %s\n",chain);
         
        sendto(ID_serv,(char *)chain,BUFFER_SIZE,0,(struct sockaddr *) &server_addr,p); 
        recvfrom(ID_serv,(char *)chain,BUFFER_SIZE,0,(struct sockaddr *) &server_addr, &p); 
    
        printf("\nmessage from the server: \n%s\n", chain);
    } 
    close(ID_serv); 
    return (0); 
}