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

class writeFile
{
public:
    writeFile();
    void createTable(int* registerSize, array<int>* columnSizes ,
                     array<char*>* columnNames , string* pFile);
    void writeRegister(string pFileName, array<char*>* pColumnData ,
                       array<int>* columnPos);
    void updateField(string newData, string pFile , int pRow , int pColumn);
    void updateColumn(string newData,string pToCompare, string pFile,
                      string pCName);

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


};

#endif // WRITEFILE_H
