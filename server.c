#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
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

    // bind network parameter 

    struct sockaddr_in sinfo ;
    sinfo.sin_family = AF_INET ;
    sinfo.sin_port = htons(PORT) ;
    sinfo.sin_addr.s_addr = inet_addr(IP) ;

    int ret = bind( sockfd , (struct sockaddr *)&sinfo , sizeof(sinfo) ) ;
    
    if( ret == -1 )
    {
        perror( "Binding failed \n") ;
        return 1 ; 
    }

    // fix queue size 
    listen( sockfd , QSIZE ) ;

    // accept client request 
    printf("waiting for client response....\n") ;
//  accept( sockfd , NULL , NULL )  // donot collect client info 
    struct sockaddr_in cinfo ;
    socklen_t clen = sizeof( cinfo ) ;

    int datafd = accept( sockfd , (struct sockaddr *) &cinfo , &clen ) ;

    if ( datafd == -1 )
    {
        perror("Accept failed \n") ;
        return 1 ;
    }

    printf("Connection successful\n") ;
    printf("Client info \n") ;
    printf("Client port number is %d\n" , ntohs(cinfo.sin_port) ) ;
    printf("Client IP addr is %s\n" , inet_ntoa(cinfo.sin_addr) ) ;

    printf("Waiting for the client data\n") ;

    char buffer[20] ;
    recv( datafd , buffer , 19 , 0 ) ;

    printf("Client send the data : %s \nh" , buffer ) ;

    close( datafd ) ;
    close( sockfd ) ;
}