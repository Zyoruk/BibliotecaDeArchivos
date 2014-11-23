#ifndef READFILE_H
#define READFILE_H
#include <fstream>
#include <string.h>
#include "array/array.h"
#include "readfile.h"
#include "usefile.h"

using namespace std;

class readfile : public useFile
{
    public:
        readfile();
        array< char* > readRegistry(string pFile , int pRegister);
        array<char*> readColumn(string pFile , string pColumnName);
        string readField(string pFile , int pRow , string pColumn);
        string readField(string pFile , int pRow , int pColumn);
        string getColumnName(string* fileName ,int* columnNumber);
        array< array<char*> > getRegisters(string pFile, string pColumnName,
                                                     string valueToConsult);
        string readDataLocation(string *pFile);
        int getRaidMode(string *pFile);

};

#endif // READFILE_H
