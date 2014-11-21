#include "networkaccess.h"

networkAccess::networkAccess()
{
}

string networkAccess::networkRequest(std::string* raidServ, std::string* data){
    this->client = new TCPClient(PORTNO);
    client->link(raidServ, data);
}

string networkAccess::networkServer(std::string* raidServ, std::string* data){
    this->server = new TCPServer(PORTNO);
    server->receive();
}
