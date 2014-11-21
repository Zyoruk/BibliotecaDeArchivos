#ifndef RAIDMANAGER_H
#define RAIDMANAGER_H
#include "konstants.h"
#include "fsqlserverfilesystem.h"
#include "network/networkaccess.h"

class raidManager
{
public:
    raidManager();
    bool createNewFile(int* pRegisterSize, array<int>* pColumnSizes,
                       array<char*>* pColumnNames, string* pFile, int* raidMode);
    string retrieveRegister(string* pFileName, int pRow);
    bool storeRegister(string* pFileName ,array<char*>* pWhatToWrite,
                       array<char*>* pColumnNam);
    bool dataRecovery(string* database);
    string getLatestRegistryLocation(string* pFile);
    int getRaidMode(string* pFile);
private:
    string SERVER_IP1;
    string SERVER_IP2;
    string SERVER_IP3;
    string ip4;
    FSQLServerFileSystem* FS;
    networkAccess* net;
};

#endif // RAIDMANAGER_H
