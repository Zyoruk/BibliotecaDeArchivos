#ifndef RAIDMANAGER_H
#define RAIDMANAGER_H
#include "konstants.h"
#include "fsqlserverfilesystem.h"
#include "networkaccess.h"

class raidManager : protected raidManager
{
public:
    raidManager(bool* mode);
    bool retrieveRegister(string pFileName, int pColumn, int pRow);
    bool saveRegister(string pFile, int raidMode);
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
