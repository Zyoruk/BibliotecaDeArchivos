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

using namespace std;

class readfile
{
    public:
        readfile();
        array< char* > readRegistry(string pFile , int pRegister);
        array<char*> readColumn(string pFile , string pColumnName);
        string readField(string pFile , int pRow , int pColumn);
        string getColumnName(string* fileName ,int* columnNumber);
        array< array<char*> > getRegisters(string pFile, string pColumnName,
                                                     string valueToConsult);
    private:
        konstants* C;
        fstream file;
        fstream file_COL;
        void checkSize(string* add, int count);
        void placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn,
                         int* pCSize);
        string toChar(int toChar);
        string intToChar(int metadata);
        string createNewFile(string newFileName);
        string charCallocToString(char* pCharCalloc);
        int stringToInt(string* pStr);
        int getRegisterSize();
        int getMetaDataSize();
        int getRegisterQuantity();
        int columnSize(int pColumnInt);
        int getColumnNumber(string* fileName ,string* columnName);
        int sizeUntilColumn(int pColumn);
        void fillString(string* pData, int pSize);
        void checkString(string* pStringToCheck);

};

#endif // READFILE_H