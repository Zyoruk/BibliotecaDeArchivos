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
    void createNewFile(string pFileName);
    void writeNewLineToFile(string pFileName , array<char*> pWhatToWrite,
                            array<int>* columnPos);
    void removeFile(string pFileName);
    void readFromFile(string pFileName , int pColumn, int pRow);
    void backUpFile (string pFileName);
    void restoreFile(string pFileName);
private:
    array<char*> _FilesMetaData;
    bool checkIfFileExists(string pFile);
    konstants _C;
    readfile RF;
    writefile WF;
};

#endif // FSQLSERVERFILESYSTEM_H
