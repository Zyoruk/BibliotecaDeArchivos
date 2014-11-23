#include "tcpclient.h"

TCPClient::TCPClient(int *portno)
{
    this->connectPort = *portno;
}

TCPClient::TCPClient()
{
    this->connectPort = PORTNO;
}

void TCPClient::error(string* msg)
{
    perror(msg->c_str());
    exit(0);
}

bool TCPClient::link(string raidServ, string data){

    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    bool clean = true;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        string temp = "Invalid Socket";
        error(&temp);
        clean = false;
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr(raidServ.c_str());
    serv_addr.sin_port = htons(this->connectPort);

    if ( connect(sockfd , (struct sockaddr*) &serv_addr , sizeof(serv_addr)) < 0 ){
        string temp = "ERROR connecting";
        error(&temp);
        clean = false;
    }

    int chuncks = 1;
    memset(buffer,0,sizeof(buffer));
    if (strlen(data.c_str()) > BUFFER_SIZE ){
        chuncks = (strlen(data.c_str()) / BUFFER_SIZE);
        chuncks += 1;
    }
    strcpy(buffer , data.c_str());

    /*
    for (int i = 0 ; i < chuncks ; i++){
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0){
             string temp  = "ERROR writing to socket";
             error(&temp);
        }
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        if (n < 0){
             string temp  = "ERROR writing to socket";
             error(&temp);
        }
    }
    */

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0){
         string temp  = "ERROR writing to socket";
         error(&temp);
         clean = false;
    }
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0){
         string temp  = "ERROR writing to socket";
         error(&temp);
         clean = false;
    }

    //printf("%s\n", buffer);

    close(sockfd);
    return clean;
}

int TCPClient::linkIndex(string raidServ, string data){

    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    bool clean = true;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        string temp = "Invalid Socket";
        error(&temp);
        clean = false;
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr(raidServ.c_str());
    serv_addr.sin_port = htons(this->connectPort);

    if ( connect(sockfd , (struct sockaddr*) &serv_addr , sizeof(serv_addr)) < 0 ){
        string temp = "ERROR connecting";
        error(&temp);
        clean = false;
    }

    int chuncks = 1;
    memset(buffer,0,sizeof(buffer));
    if (strlen(data.c_str()) > BUFFER_SIZE ){
        chuncks = (strlen(data.c_str()) / BUFFER_SIZE);
        chuncks += 1;
    }
    strcpy(buffer , data.c_str());

    /*
    for (int i = 0 ; i < chuncks ; i++){
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0){
             string temp  = "ERROR writing to socket";
             error(&temp);
        }
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        if (n < 0){
             string temp  = "ERROR writing to socket";
             error(&temp);
        }
    }
    */

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0){
         string temp  = "ERROR writing to socket";
         error(&temp);
         clean = false;
    }
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0){
         string temp  = "ERROR writing to socket";
         error(&temp);
         clean = false;
    }

    //printf("%s\n", buffer);
    int index = atoi(buffer.c_str());

    close(sockfd);
    return index;
}
