#ifndef NETWORKACCESS_H
#define NETWORKACCESS_H
#include "network/tcpclient.h"
#include "network/tcpserver.h"
#include "konstants.h"

class networkAccess
{
public:
    networkAccess();
    networkWrite();
    networkRead();

private:
    TCPClient* client;
    TCPServer* server;
};

#endif // NETWORKACCESS_H
