#ifndef WRITEFILE_H
#define WRITEFILE_H
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

class writefile
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
    konstants* K;
    fstream file;
    fstream file_COL;
    string toChar(int toChar);
    void checkSize(string* add, int count);
    string intToChar(int metadata);
    string createNewFile(string newFileName);
    int stringToInt(string* pStr);
    string charCallocToString(char* pCharCalloc);
    int getRegisterSize();
    int getMetaDataSize();
    int getRegisterQuantity();
    int columnSize(int pColumnInt);
    int sizeUntilColumn(int pColumn);
    void fillString(string* pData, int pSize);
    void checkString(string* pStringToCheck);
    void placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn, int* pCSize);
    void writeColumnNames(string* fileName, array<char*>* columnNames);
    int getColumnNumber(string* fileName ,string* columnName);


};

#endif // WRITEFILE_H
