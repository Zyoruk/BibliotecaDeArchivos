#ifndef RAIDMANAGER_H
#define RAIDMANAGER_H
#include "konstants.h"
#include "fsqlserverfilesystem.h"
#include "network/networkaccess.h"

class raidManager
{
public:
    raidManager();

    string retrieveRegister(string* pFileName, int pRow);
    bool dataRecovery(string* database);

    bool createNewFile(int* pRegisterSize, array<int>* pColumnSizes,
                       array<char*>* pColumnNames, string* pFile, int* raidMode);

    bool storeRegister(string* pFileName ,array<char*>* pWhatToWrite,
                       array<char*>* pColumnNam);
<<<<<<< HEAD

=======
    bool dataRecovery(string* database);
    string getLatestRegistryLocation(string* pFile);
>>>>>>> f8b036d595a52d01f6a0039da8fd27bc54f1c6bb
private:
    string getLatestRegistryLocation(string* pFile);
    string getOnRegFormat(string* pWhatToWrite);
    FSQLServerFileSystem* FS;
    networkAccess* net;
};

#endif // RAIDMANAGER_H
