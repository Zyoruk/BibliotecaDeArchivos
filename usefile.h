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
using namespace std;

class useFile
{
protected:
    useFile();

    konstants* K;
    fstream file;
    fstream file_COL;

    string toChar(int toChar);
    string intToChar(int metadata);
    string createNewFile(string newFileName);
    string createNewBackUp(string newFileName);
    int stringToInt(string* pStr);
    int getRegisterSize();
    int getMetaDataSize();
    int getRegisterQuantity();
    int columnSize(int pColumnInt);
    int sizeUntilColumn(int pColumn);
    int getColumnNumber(string* fileName ,string* columnName);
    void fillString(string* pData, int pSize);
    void checkString(string* pStringToCheck);
    void checkSize(string* add, int count);
    void placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn, int* pCSize);
};

#endif // USEFILE_H
