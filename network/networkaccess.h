#ifndef NETWORKACCESS_H
#define NETWORKACCESS_H
#include "network/tcpclient.h"
#include "network/tcpserver.h"
#include "konstants.h"
#include <string>

class networkAccess
{
public:
    networkAccess();
    bool networkWrite(std::string* raidServ, std::string* data);
    std::string networkRead(std::string* raidServ, std::string* data);
    TCPClient* client;
    TCPServer* server;
};

#endif // NETWORKACCESS_H
