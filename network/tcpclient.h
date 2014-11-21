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
#include <string>
#include "konstants.h"

using namespace std;

class TCPClient
{
public:
    TCPClient();
    int link(string*  raidServ, string* data);
    void error(string *msg);
};

#endif // TCPCLIENT_H
