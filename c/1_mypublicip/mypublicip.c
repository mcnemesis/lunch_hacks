/* 
 * File:   mypublicip.c
 * Authors: 
 *  mcnemesis  (current incarnation)
 *  Adam (http://cboard.cprogramming.com/c-programming/142841-sending-http-get-request-c.html#post1066357)
 * --------------------
 * Program: mypublicip
 * Usage: ./mypublicip [url]
 * Purpose: run on a machine, this program is supposed to report to the user their inferred public ip address
 * HOW: it does this by querying the online service http://canihazip.com/s and reporting the result via output 
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int DEBUG=0;
#define IFDEBUG if(DEBUG)
 
int main(int argc, char** argv) {
     
    char arg[500];
    char domain_name[500];
    char request_path[500];
    char request[1000];
    struct hostent *server;
    struct sockaddr_in serveraddr;
    int port = 80;
     
    if(strlen(arg) > 0) {// we got an alternative route to call
        strcpy(arg, argv[1]);
         
        int i;
        for (i = 0; i < strlen(arg); i++)
        {
            if (arg[i] == '/')
            {
                    strncpy(domain_name, arg, i);
                    domain_name[i] = '\0';
                    break;
            }     
        }
         
        for (i; i < strlen(arg); i++)
        {
            strcat(request_path, &arg[i]);
            break;
        }
    }else{
        strcpy(domain_name, "canihazip.com");
        strcpy(request_path, "/s");
    }
     
    
    IFDEBUG printf("\nDomain: %s", domain_name);
     
    IFDEBUG printf("\nPath: %s", request_path);
     
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
     
    if (tcpSocket < 0)
        printf("\nError opening socket");
    else
        IFDEBUG printf("\nSuccessfully opened socket");
     
    server = gethostbyname(domain_name);
     
    if (server == NULL)
    {
        printf("gethostbyname() failed\n");
    }
    else
    {
        IFDEBUG printf("\n%s = ", server->h_name);
        unsigned int j = 0;
        while (server -> h_addr_list[j] != NULL)
        {
            /*IFDEBUG printf("%s", inet_ntoa(*(struct in_addr*)(server -> h_addr_list[j])));*/
            j++;
        }
    }
     
    IFDEBUG printf("\n");
 
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
 
    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
     
    serveraddr.sin_port = htons(port);
     
    if (connect(tcpSocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
        printf("\nError Connecting");
    else
        IFDEBUG printf("\nSuccessfully Connected");
   
    bzero(request, 1000);
 
    sprintf(request, "Get %s HTTP/1.1\r\nHost: %s\r\n\r\n", request_path, domain_name);
     
    IFDEBUG printf("\n%s", request);
     
    if (send(tcpSocket, request, strlen(request), 0) < 0)
        printf("Error with send()");
    else
        IFDEBUG printf("Successfully sent html fetch request");
     
    bzero(request, 1000);
     
    recv(tcpSocket, request, 999, 0);
    
    char* line = strtok(request,"\n"), *ip;
    while(line = strtok(NULL,"\n"))
        ip = line;

    /*we have our ip :-) */
    printf("You public IP is: %s\n", ip);
     
    close(tcpSocket);
     
    return (EXIT_SUCCESS);
}
