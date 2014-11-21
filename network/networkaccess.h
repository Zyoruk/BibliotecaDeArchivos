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
    bool networkRequest(string* raidServ, std::string* data);
    string networkServer(string* raidServ, std::string* data);

private:
    TCPClient* client;
    TCPServer* server;
};

#endif // NETWORKACCESS_H
