#ifndef FSQLSERVERFILESYSTEM_H
#define FSQLSERVERFILESYSTEM_H
#include "array/array.h"
#include "konstants.h"
#include "readfile.h"
#include "writefile.h"
#include <string.h>

using namespace std;

class FSQLServerFileSystem
{
public:
    FSQLServerFileSystem();
    bool createNewFile(int* pRegisterSize, array<int>* pColumnSizes,
                       array<char*>* pColumnNames, string* pFile);
    bool writeNewLineToFile(string pFileName , array<char*>* pWhatToWrite,
                            array<int>* columnPos);
    bool removeFile(string pFileName);
    array<char*> readFromFile(string pFileName , int pColumn, int pRow);
    bool backUpFile (string pFileName);
    bool restoreFile(string pFileName);
private:
//    array<char*> _FilesMetaData;
    bool fileExists(string pFile);
    konstants* _C;
    readfile* RF;
    writefile* WF;
};

#endif // FSQLSERVERFILESYSTEM_H
