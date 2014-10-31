#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <string.h>
#include "array/array.h"
#include "usefile.h"

using namespace std;

class writefile : protected useFile
{
public:
    writefile();
    void createTable(int* registerSize, array<int>* columnSizes ,
                     array<char*>* columnNames , string* pFile);
    bool writeRegister(string pFileName, array<char*>* pColumnData ,
                       array<int>* columnPos);
    bool updateField(string newData, string pFile , int pRow , int pColumn);
    bool updateColumn(string newData,string pToCompare, string pFile,
                      string pCName);
    void backUpFile(string fileTobackUp);
    void restoreFile(string fileToRestore);
private:
    void writeColumnNames(string* fileName, array<char*>* columnNames);
    //string charCallocToString(char* pCharCalloc);
};

#endif // WRITEFILE_H
