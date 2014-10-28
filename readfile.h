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
    //konstants* K;
    //fstream file;
    //fstream file_COL;
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

#endif // READFILE_H
