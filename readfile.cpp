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

readFile::readFile()
{
    konstants* K = new konstants();
    fstream file;
    fstream file_COL;
}

string toChar(int toChar){
    string s;
    stringstream out;
    out << toChar;
    s = out.str();
    return s;
}

void checkSize(string* add, int count){
    string tmp;

    for (int a = 1 ; a < count ; a++){
        if((tmp.length() + add->length()) == count){
            break;
        }
        tmp.push_back(K->SINGLE_NULL);
    }
    tmp.append(*add);
    *add = tmp;
}

string intToChar(int metadata){
    int ch;
    string tmp ;
    while (metadata != 0){
        ch = metadata % 10;
        metadata = metadata / 10;
        tmp.append(toChar(ch));
    }
    return tmp;
}

string createNewFile(string newFileName){
    string newFileDir ;
    newFileDir = K->DIRFILE;
    newFileDir.append(newFileName);
    return newFileDir;
}

int stringToInt(string* pStr){
    int i;
    i= atoi(pStr->c_str());
    return i;
}

string charCallocToString(char* pCharCalloc){
    string stringToReturn ;
    stringToReturn = "";
    for (int i = NULL; i <= K->DEFAULT_COLUMN_SIZE;i++){
        stringToReturn.append(((const char*)(pCharCalloc + i)));
    }
    return stringToReturn;
}

int getRegisterSize(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW);
    file.seekg(K->DEFAULT_COLUMN_SIZE);
    string regSizeString = "";
    for (int i  = 0 ; i < K->DEFAULT_REGISTER_SIZE;i++){
        regSizeString.push_back(file.get());
    }
    int regSize;
    regSize = stringToInt(&regSizeString);
    file.seekg(currSeek);
    return regSize;
}

int getMetaDataSize(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW);
    string MDSizeString = "";
    for (int i  = 0 ; i < K->METADATA_SIZE;i++){
        MDSizeString.push_back(file.get());
    }
    int MDSizeInt  = stringToInt(&MDSizeString);
    file.seekg(currSeek);
    return MDSizeInt;
}

int getRegisterQuantity(){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW, ios::end);
    int fileSize = file.tellg();
    int registerSize = getRegisterSize();
    int regQty ;
    regQty = (fileSize - (getMetaDataSize()))/registerSize;
    file.seekg(currSeek);
    return regQty;
}

int columnSize(int pColumnInt){
    int currSeek = file.tellg();
    file.seekg(K->ZE_ROW);

    //Move the seek to the beginning of the column.
    int whereToMove = K->METADATA_COLUMN_START+
                      (pColumnInt * K->DEFAULT_COLUMN_SIZE);
    file.seekg(whereToMove);
    string cSize = K->EMPTY_STRING;
    // build the string;
    for (int i = whereToMove; i < (whereToMove + K->DEFAULT_COLUMN_SIZE) ; i++){
        cSize.push_back(file.get());
    }

    int cSizeInt = stringToInt(&cSize);
    file.seekg(currSeek);
    return cSizeInt;
}

/*!
 * \brief sizeUntilColumn saber la cantidad de espacios a recorrer hasta
 * el inicio de la columna
 * \param pColumn
 * \return
 */
int sizeUntilColumn(int pColumn){
    int sizeToReturn = K->ZE_ROW;
    for (int i = K->ZE_ROW; i < pColumn -1 ; i++){
        sizeToReturn += columnSize(i);
    }
    return sizeToReturn;
}

/**
 * @brief fillString creates a string with the size of a registry
 * @param pData registry to be initialized.
 * @param pSize size of the registry.
 */
void fillString(string* pData, int pSize){
    while ( pData->length() < pSize){
        pData->push_back(K->NULL_CHAR);
    }
}

void checkString(string* pStringToCheck){
    char* tempString = new char[(*pStringToCheck).size()+1];
    strcpy(tempString, (*pStringToCheck).c_str());
    for (int i = K->ZE_ROW ; i < pStringToCheck->length(); i++){
        if (tempString[i] == ' ' ){
            tempString[i] = '_';
        }
    }
    string stringToReturn(tempString);
    *pStringToCheck = stringToReturn;
}

void placeSeekOn(int* pRow , int* pColumn, int* pSizeToColumn,
                 int* pCSize){
    //Move seek to the row
      file.seekg(  getMetaDataSize() + ( getRegisterSize() * (*pRow-1) )  );
    //move seek to the beginning of the column

    *pSizeToColumn = sizeUntilColumn(*pColumn);
    file.seekg(*pSizeToColumn , ios::cur);
   //Read the info
    *pCSize = columnSize(*pColumn-1);
}

//La variable de regreso es eliminada
int getColumnNumber(string* fileName ,string* columnName){
    string tmp = "Columns";
    string path = *fileName;
    string COLNAME;
    path.append(tmp);
    int i =K->ONE_BYTE;
    int columnNumber = -2;
    file_COL.open(path.c_str());
    while (file_COL.tellg() != -1)
    {
        getline(file_COL,COLNAME);
        if ( *columnName == COLNAME)
            columnNumber = i;
        i++;
    }
    return columnNumber;
}

//La variable de regreso es eliminada
string getColumnName(string* fileName ,int* columnNumber){
    string K = "Columns";
    string path = *fileName;
    path.append(K);
    int i = 0;

    string columnName = "NOT FOUND";
    file_COL.open(path.c_str());

    while (i != *columnNumber)
    {
        getline(file_COL, columnName);
        if(file_COL.eof())
            break;
    }
    return columnName;
}

/**
 * @brief readField returns the data readed on field of the database.
 * @param pFile is the name of the file to be readed from.
 * @param pRow is the row of the desired data.
 * @param Column is the column of the desired data.
 * @return
 */
string readField(string pFile , int pRow , int pColumn){
    int currSeek =file.tellg();
    int sizeToColumn;
    int cSize;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }
    placeSeekOn(&pRow , &pColumn, &sizeToColumn, &cSize);

    //build the stringto return
    string stringToReturn = "";

    for (int i  = 0 ; i < cSize ; i++){
        char currChar = file.get();
        if (currChar != '*'){
            stringToReturn.push_back(currChar);
        }else{
            break;
        }
    }
    file.seekg(currSeek);
    if (stringToReturn == "") stringToReturn = "404";
    return stringToReturn;
}

/**
 * @brief readColumn return all the values on a named column
 * @param pFile is the database to be readed from.
 * @param pColumnName parameter for returning a value.
 * @return
 */
array<char*> readColumn(string pFile , string pColumnName){
    string standardDir;
    if ( !(file.is_open()) ){
        string fileH = pFile;
        standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    int Column = getColumnNumber(&standardDir , &pColumnName );
    int regQty = getRegisterQuantity();
    string strToConvert = K->EMPTY_STRING;
    char * toAdd;
    array <char*> arrayToReturn (regQty);
    for (int rowCounter = K->ONE_BYTE ; rowCounter <= regQty ; rowCounter++){
        strToConvert = readField(pFile , rowCounter , Column);
        toAdd = new char[strToConvert.size()+1];
        strcpy(toAdd, strToConvert.c_str());
        arrayToReturn[rowCounter - K->ONE_BYTE] = toAdd;
    }
    return arrayToReturn;
}

/**
 * @brief readRegistry return all the values for a required registry.
 * @param pFile the database to be consulted.
 * @param pRegister the row to be consulted.
 * @return
 */
array< char* > readRegistry(string pFile , int pRegister){

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }
    //Create an array that will contain all the columns
    int columnQty = (getMetaDataSize() - K->METADATA_COLUMN_START)/K->DEFAULT_COLUMN_SIZE;

    array < char* > arrayToReturn (columnQty);
    string tempString = K->EMPTY_STRING;
    char* toAdd;
    for (int i = K->ZE_ROW; i < columnQty; i++){
        tempString = readField(pFile , pRegister , i+1);
        toAdd = new char[tempString.size()+1];
        strcpy(toAdd, tempString.c_str());
        arrayToReturn[i] = toAdd;
    }

    file.close();
    return arrayToReturn;
}
