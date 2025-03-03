#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define PORT 5000
#define IP "127.0.0.1"
#define QSIZE 5 

int main()
{
    // create a socket 
    int sockfd = socket( AF_INET , SOCK_STREAM , 0 ) ;
    if ( sockfd == -1 )
    {
        perror("Socket failed\n") ;
        return 1 ;
    }

    //  client connection request
    struct sockaddr_in sinfo ;
    sinfo.sin_family = AF_INET ;
    sinfo.sin_port = htons(PORT) ;
    sinfo.sin_addr.s_addr = inet_addr(IP) ;
    int ret = connect( sockfd , (struct sockaddr * )&sinfo , sizeof(sinfo) ) ;
    if ( ret == -1 ) 
    {
        perror("Connection failed \n") ;
        return 1 ;
    }

    char buffer[20] ;
    printf("Enter th message\n") ;
    scanf("%s" , buffer ) ;
    
    int c = send( sockfd , buffer , strlen(buffer)+1 , 0 ) ;

    if ( c )
    {
        printf("Message sent successfull\n" ) ;
    }
    else
    {
        printf("Message sending failed\n") ;
    }
    close(sockfd) ;
}