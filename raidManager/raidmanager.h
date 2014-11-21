#ifndef RAIDMANAGER_H
#define RAIDMANAGER_H
#include "konstants.h"
#include "fsqlserverfilesystem.h"
#include "network/networkaccess.h"

class raidManager
{
public:
    raidManager();

    string retrieveRegister(string* pFileName , string* commandLine, int pRow);
    bool dataRecovery(string* database);

    bool createNewFile(int* pRegisterSize, array<int>* pColumnSizes,
                       array<char*>* pColumnNames, string* pFile, int* raidMode,
                       string* commandLine);

    bool storeRegister(string* pFileName ,array<char*>* pWhatToWrite,
                       array<char*>* pColumnNam , string* commandLine);

private:
    string getLatestRegistryLocation(string* pFile);
    string getOnRegFormat(string* pWhatToWrite);
    FSQLServerFileSystem* FS;
    networkAccess* net;
};

#endif // RAIDMANAGER_H
