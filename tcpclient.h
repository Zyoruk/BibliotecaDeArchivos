#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TCPClient
{
public:
    TCPClient();
    void link(int portno, const char* raidServ, char* buffer[]);
    void error(const char *msg);
};

#endif // TCPCLIENT_H
