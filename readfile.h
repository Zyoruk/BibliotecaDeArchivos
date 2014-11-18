#ifndef READFILE_H
#define READFILE_H
#include <fstream>
#include <string.h>
#include "array/array.h"
#include "readfile.h"
#include "usefile.h"

using namespace std;

class readfile : protected useFile
{
    public:
        readfile();
        array< char* > readRegistry(string pFile , int pRegister);
        array<char*> readColumn(string pFile , string pColumnName);
        string readField(string pFile , int pRow , int pColumn);
        string getColumnName(string* fileName ,int* columnNumber);
        array< array<char*> > getRegisters(string pFile, string pColumnName,
                                                     string valueToConsult);

};

#endif // READFILE_H
