#include "tcpclient.h"

TCPClient::TCPClient()
{
}

void TCPClient::error(const char *msg)
{
    perror(msg);
    exit(0);
}

int TCPClient::link(const char* raidServ, char* data)
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        error("Invalid Socket");
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr(raidServ);
    serv_addr.sin_port = htons(PORTNO);

    if ( connect(sockfd , (struct sockaddr*) &serv_addr , sizeof(serv_addr)) < 0 ){
        error("ERROR connecting");
    }

    memset(buffer,0,sizeof(256));
    data = buffer;

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0){
         error("ERROR writing to socket");
    }
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
         error("ERROR reading from socket");

    //printf("%s\n", buffer);

    close(sockfd);
    return n;
}
