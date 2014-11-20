#include "networkaccess.h"

networkAccess::networkAccess()
{
    this->client = new TCPClient();
}

bool networkAccess::networkWrite(const char* raidServ[], char* data[]){
    client->link(PORTNO, raidServ, data);
}

string networkAccess::networkRead(const char* raidServ[], char* data[]){
    client->link(PORTNO, raidServ, data);
}
