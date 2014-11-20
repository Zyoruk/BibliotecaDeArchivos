#ifndef RAIDMANAGER_H
#define RAIDMANAGER_H
#include "konstants.h"
#include "fsqlserverfilesystem.h"

class raidManager
{
protected:
    raidManager();
    bool retrieveRegister(string *pFile);
    bool saveRegister(string pFile, int raidMode);
    bool dataRecovery(char* database);

private:
    char* ip1;
    char* ip2;
    char* ip3;
    char* ip4;
    FSQLServerFileSystem* FS;
};

#endif // RAIDMANAGER_H
