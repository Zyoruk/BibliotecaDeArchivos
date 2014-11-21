#include "networkaccess.h"

networkAccess::networkAccess()
{
}

int networkAccess::networkRequest(std::string raidServ, std::string* data){
    this->client = new TCPClient();
    return client->link(raidServ, *data);
}

string networkAccess::networkServer(std::string raidServ, std::string* data){
    this->server = new TCPServer();
    server->receive();
}
