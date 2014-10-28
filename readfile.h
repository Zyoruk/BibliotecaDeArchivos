#ifndef READFILE_H
#define READFILE_H
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "konstants.h"
#include "array/array.h"
#include "readfile.h"

class readFile
{
    public:
        readFile();
        array< char* > readRegistry(string pFile , int pRegister);
        array<char*> readColumn(string pFile , string pColumnName);
        string readField(string pFile , int pRow , int pColumn);

    private:
        konstants* K;
        fstream file;
        fstream file_COL;
        void checkSize(string* add, int count);
        string toChar(int toChar);
        string intToChar(int metadata);
        string createNewFile(string newFileName);
        string charCallocToString(char* pCharCalloc);
        int stringToInt(string* pStr);
        int getRegisterSize();
        int getMetaDataSize();
        int getRegisterQuantity();
        int columnSize(int pColumnInt);

};

#endif // READFILE_H
