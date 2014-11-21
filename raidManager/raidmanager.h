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
                       array<char*>* pColumnNames, string* pFile, int raidMode);
    bool retrieveRegister(string pFileName, int pColumn, int pRow);
    bool storeRegister(string pFile, int raidMode);
    bool dataRecovery(char* database);

private:
    char* ip1;
    char* ip2;
    char* ip3;
    char* ip4;
    FSQLServerFileSystem* FS;
    networkAccess* net;
};

#endif // RAIDMANAGER_H
