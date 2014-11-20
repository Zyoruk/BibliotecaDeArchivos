#include "raidmanager.h"

raidManager::raidManager()
{
    this->ip1 = SERVER_IP1;
    this->ip2 = SERVER_IP2;
    this->ip3 = SERVER_IP3;
    this->ip4 = SERVER_IP4;
    this->FS = new FSQLServerFileSystem();
}

bool raidManager::saveRegister(string* pFile, int raidMode){
    if (!FS->fileExists(*pFile)){
        return false;
    }

    string IP = getNextRegistryLocation();


}

bool raidManager::retrieveRegister(string* pFile){
    if (!FS->fileExists(*pFile)){
        return false;
    }
}

bool raidManager::dataRecovery(char* database){
    if(getRaidMode(&database) != 05){
        cout << "*** Non recovery raid mode ***";
        return false;
    }
}

