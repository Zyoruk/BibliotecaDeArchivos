#include "networkaccess.h"

networkAccess::networkAccess()
{
    this->client = new TCPClient();
    this->server = new TCPServer();
}

bool networkAccess::networkWrite(std::string* raidServ, std::string* data){
    client->link(raidServ, data);
}

std::string networkAccess::networkRead(std::string* raidServ, std::string* data){
    client->link(raidServ, data);
}
