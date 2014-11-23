#ifndef USEFILE_H
#define USEFILE_H
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "konstants.h"
#include "array/array.h"

using namespace std;

class useFile
{
protected:
    useFile();

    fstream file;
    fstream file_col;
    fstream file_lo;
    fstream file_userpass;
    fstream file_userpermrd;
    fstream file_userpermrw;

    string toChar(int toChar);
    string intToChar(int metadata);
    string createNewFile(string* newFileName);
    string createNewBackUp(string newFileName);
    int getRegisterSize(array<int>* columnSizes);
    int stringToInt(string* pStr);
    int getRegisterSize();
    int getMetaDataSize();
    int getRegisterQuantity();
    int columnSize(int pColumnInt);
    int sizeUntilColumn(int pColumn);
    int getColumnNumber(string* fileName ,string* columnName);
    void fillString(string* pData, int pSize);
    void fillZString(string* pData, int pSize);
    void checkString(string* pStringToCheck);
    void checkSize(string* add, int count);
    void placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn, int* pCSize);
    int getRaidMode();
};

#endif // USEFILE_H
